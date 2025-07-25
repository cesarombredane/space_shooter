#include "../include/map.h"

Map::Map(int lvl)
{
	if (!tileSetTexture.loadFromFile("src/assets/graphics/tileset.png"))
		cerr << "erreur chargement de la tileset" << endl;
	else
		tileSet.setTexture(tileSetTexture);

	if (!backgroundTexture.loadFromFile("src/assets/graphics/background.png"))
		cerr << "erreur chargement du BG" << endl;
	else
		background.setTexture(backgroundTexture);

	if (!buffer_death_enemy.loadFromFile("src/assets/sounds/death_enemy.wav"))
	{
		cerr << "erreur de chargement sound 'death_enemy'" << endl;
	}

	spawn_time = 0;
	difficulte = lvl;
}

vector<vector<int>> Map::get_map()
{
	return map;
}

int Map::get_ind_map(int x, int y)
{
	return map[y][x];
}

int Map::get_collision_block()
{
	return COLLISION_BLOCK;
}

int Map::get_difficulte()
{
	return difficulte;
}

vector<int> Map::get_active_enemy_map()
{
	return active_enemy_map;
}

vector<Spawner> Map::get_spawner_map()
{
	return spawner_map;
}

vector<Enemy> Map::get_enemy_map()
{
	return enemy_map;
}

void Map::load_map(int lvl)
{
	fstream maptxt;
	string str_ligne, str_car;
	stringstream stream;
	vector<int> ligne;

	switch (lvl)
	{
	case 1:
		maptxt.open("src/assets/maps/map1.txt");
		break;
	case 2:
		maptxt.open("src/assets/maps/map2.txt");
		break;
	case 3:
		maptxt.open("src/assets/maps/map3.txt");
		break;
	default:
		break;
	}

	if (!maptxt.is_open())
		cerr << "erreur chargement de la map" << endl;

	map.clear();

	while (!maptxt.eof())
	{
		getline(maptxt, str_ligne);

		if (!str_ligne.size())
			continue;

		stream.clear();
		stream.str(str_ligne);
		ligne.clear();

		while (true)
		{
			getline(stream, str_car, ' ');
			ligne.push_back(atoi(str_car.c_str()));

			if (!stream.good())
				break;
		}

		map.push_back(ligne);
	}

	score = 0;
	cadence_spawn = 180;
	pathfind_timer = 0;
	create_spawner();
}

void Map::draw_map(RenderWindow &window, Camera &camera)
{
	int x, y, mapX, x1, x2, mapY, y1, y2, xsource, ysource, a;
	int startX, startY;

	startX = startY = 0;

	mapX = startX / TILE_SIZE;
	x1 = (startX % TILE_SIZE) * -1;
	x2 = x1 + map[0].size() * TILE_SIZE + (x1 == 0 ? 0 : TILE_SIZE);

	mapY = startY / TILE_SIZE;
	y1 = (startY % TILE_SIZE) * -1;
	y2 = y1 + map.size() * TILE_SIZE + (y1 == 0 ? 0 : TILE_SIZE);

	for (y = y1; y < y2; y += TILE_SIZE)
	{
		mapX = startX / TILE_SIZE;

		for (x = x1; x < x2; x += TILE_SIZE)
		{
			if (!(x < camera.get_pos_camera().x - WINDOW_WIDTH / 2 - TILE_SIZE ||
						x > camera.get_pos_camera().x + WINDOW_WIDTH / 2 + TILE_SIZE ||
						y < camera.get_pos_camera().y - WINDOW_HEIGTH / 2 - TILE_SIZE ||
						y > camera.get_pos_camera().y + WINDOW_HEIGTH / 2 + TILE_SIZE))
			{
				a = map[mapY][mapX];

				ysource = a / 10 * TILE_SIZE;
				xsource = a % 10 * TILE_SIZE;

				tileSet.setTexture(tileSetTexture);
				tileSet.setPosition(Vector2f(x, y));
				tileSet.setTextureRect(IntRect(xsource, ysource, TILE_SIZE, TILE_SIZE));
				window.draw(tileSet);
			}

			mapX++;
		}
		mapY++;
	}
}

int Map::colision(int x, int y)
{
	if (y / TILE_SIZE > map.size() || x / TILE_SIZE > map[0].size())
	{
		cerr << "erreur argument de get_tile" << endl;
		system("pause");
	}
	return map[y / TILE_SIZE][x / TILE_SIZE];
}

void Map::create_spawner()
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[0].size(); j++)
		{
			if (map[i][j] == SPAWNER)
			{
				Spawner spawner(Vector2f(j * TILE_SIZE + 32, i * TILE_SIZE + 32));
				spawner_map.push_back(spawner);
			}
		}
	}
}

void Map::tick_spawner(RenderWindow &window, Map &mapclass, Camera &camera, Player &player)
{
	if (enemy_map.size() < 4 && spawn_time <= 0)
	{
		for (int i = 0; i < spawner_map.size(); i++)
		{
			spawner_map[i].spawn(difficulte, mapclass);
			Pathfinding pass;
			string s = pass.pathfinding(map, enemy_map[i].get_pos_enemy().x / TILE_SIZE, enemy_map[i].get_pos_enemy().y / TILE_SIZE,
																	player.get_posPlayer().x / TILE_SIZE, player.get_posPlayer().y / TILE_SIZE);
			pathfinder.push_back(s);
		}
		spawn_time = cadence_spawn;
	}
	else
		spawn_time--;

	draw_enemies(window);
}

void Map::draw_BG(RenderWindow &window, Player &player, Camera &camera)
{
	if (camera.get_goRight())
	{
		moveBG.x -= BG_SPEED;
	}
	if (camera.get_goLeft())
	{
		moveBG.x += BG_SPEED;
	}
	if (camera.get_goDown())
	{
		moveBG.y -= BG_SPEED;
	}
	if (camera.get_goUp())
	{
		moveBG.y += BG_SPEED;
	}

	background.setPosition(moveBG.x, moveBG.y);
	background.setTexture(backgroundTexture);
	window.draw(background);
}

void Map::load_BG(Player &player)
{
	moveBG.x = player.get_posPlayer().x;
	moveBG.y = player.get_posPlayer().y;
	background.setOrigin(3840, 2400);
	background.setPosition(moveBG.x, moveBG.y);
}

void Map::draw_enemies(RenderWindow &window)
{
	for (int i = 0; i < active_enemy_map.size(); i++)
	{
		enemy_map[active_enemy_map[i]].rotation_enemy();
		enemy_map[active_enemy_map[i]].draw_enemy(window);
	}
}

void Map::move_enemies(Player &player, Map &mapclass)
{
	Pathfinding pass;

	for (int i = 0; i < enemy_map.size(); i++)
	{
		if (pathfind_timer == i * 6)
		{
			string s = pass.pathfinding(map, enemy_map[i].get_pos_enemy().x / TILE_SIZE, enemy_map[i].get_pos_enemy().y / TILE_SIZE,
																	player.get_posPlayer().x / TILE_SIZE, player.get_posPlayer().y / TILE_SIZE);
			pathfinder[i] = s;
		}

		bool top = (colision(enemy_map[i].get_pos_enemy().x + (TILE_SIZE / 2), enemy_map[i].get_pos_enemy().y - (TILE_SIZE / 2)) > COLLISION_BLOCK ||
								colision(enemy_map[i].get_pos_enemy().x - (TILE_SIZE / 2), enemy_map[i].get_pos_enemy().y - (TILE_SIZE / 2)) > COLLISION_BLOCK);

		bool bot = (colision(enemy_map[i].get_pos_enemy().x + (TILE_SIZE / 2), enemy_map[i].get_pos_enemy().y + (TILE_SIZE / 2)) > COLLISION_BLOCK ||
								colision(enemy_map[i].get_pos_enemy().x - (TILE_SIZE / 2), enemy_map[i].get_pos_enemy().y + (TILE_SIZE / 2)) > COLLISION_BLOCK);

		bool left = (colision(enemy_map[i].get_pos_enemy().x - (TILE_SIZE / 2), enemy_map[i].get_pos_enemy().y - (TILE_SIZE / 2)) > COLLISION_BLOCK ||
								 colision(enemy_map[i].get_pos_enemy().x - (TILE_SIZE / 2), enemy_map[i].get_pos_enemy().y + (TILE_SIZE / 2)) > COLLISION_BLOCK);

		bool right = (colision(enemy_map[i].get_pos_enemy().x + (TILE_SIZE / 2), enemy_map[i].get_pos_enemy().y - (TILE_SIZE / 2)) > COLLISION_BLOCK ||
									colision(enemy_map[i].get_pos_enemy().x + (TILE_SIZE / 2), enemy_map[i].get_pos_enemy().y + (TILE_SIZE / 2)) > COLLISION_BLOCK);

		if (pathfinder[i] != "")
		{
			enemy_map[i].move_input_enemy(pathfinder[i]);
			enemy_map[i].colision_enemy(mapclass);
			enemy_map[i].move_enemy(pathfinder[i]);
		}
	}
	pathfind_timer++;

	if (pathfind_timer >= 60)
	{
		pathfind_timer = 0;
	}
}

void Map::add_enemy(Enemy &e)
{
	enemy_map.push_back(e);
}

void Map::active_enemies(Camera &camera)
{
	active_enemy_map.clear();

	for (int i = 0; i < enemy_map.size(); i++)
	{
		if (enemy_map[i].get_pos_enemy().x - (TILE_SIZE / 2) < camera.get_pos_camera().x + (WINDOW_WIDTH / 2) &&
				enemy_map[i].get_pos_enemy().x + (TILE_SIZE / 2) > camera.get_pos_camera().x - (WINDOW_WIDTH / 2) &&
				enemy_map[i].get_pos_enemy().y - (TILE_SIZE / 2) < camera.get_pos_camera().y + (WINDOW_HEIGTH / 2) &&
				enemy_map[i].get_pos_enemy().y + (TILE_SIZE / 2) > camera.get_pos_camera().y - (WINDOW_HEIGTH / 2))
		{

			active_enemy_map.push_back(i);
		}
	}
}

void Map::test_mort_enemies(int volume)
{
	for (int i = 0; i < enemy_map.size(); i++)
	{
		if (enemy_map[i].get_vie() <= 0)
		{
			sound_death_enemy.setBuffer(buffer_death_enemy);
			sound_death_enemy.setVolume(volume);
			sound_death_enemy.stop();
			sound_death_enemy.play();

			switch (difficulte)
			{
			case 1:
				if (enemy_map[i].get_type() == 0)
					add_point(50);
				else
					add_point(100);
				break;
			case 2:
				if (enemy_map[i].get_type() == 0)
					add_point(100);
				else
					add_point(200);
				break;
			case 3:
				if (enemy_map[i].get_type() == 0)
					add_point(250);
				else
					add_point(500);
				break;
			default:
				break;
			}

			enemy_map.erase(enemy_map.begin() + i);
			pathfinder.erase(pathfinder.begin() + i);
		}
	}
}

void Map::enemy_damage(int ind, int damage, int volume)
{
	enemy_map[ind].take_damage(damage, volume);
}

void Map::add_point(int point)
{
	score += point;
}

int Map::get_point()
{
	return score;
}