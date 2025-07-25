#include "jeu.h"

Jeu::Jeu()
{
	volume = 50;
	carte = 1;
	difficulte = 1;
}

void Jeu::load_jeu(int lvl, int m, int vol)
{
	difficulte = lvl;
	carte = m;
	volume = vol;

	gui.push_back(Gui());
	input.push_back(Input());
	map.push_back(Map(difficulte));
	map[0].load_map(carte);
	player.push_back(Player(map[0]));
	camera.push_back(Camera(player[0]));
	map[0].load_BG(player[0]);
	gui[0].load_gui();
}

int Jeu::open(RenderWindow &window)
{
	while (window.isOpen())
	{
		window.clear();

		input[0].gestion_input(window);
		map[0].draw_BG(window, camera[0]);
		map[0].draw_map(window, camera[0]);
		player[0].move_input(input[0]);
		player[0].colision(map[0], gui[0], volume, camera[0]);
		player[0].move();
		player[0].player_fire(input[0], window, map[0], camera[0], gui[0], volume);
		player[0].rotation_player(input[0]);
		player[0].draw_player(window);
		map[0].tick_spawner(window, map[0], player[0]);
		map[0].move_enemies(player[0], map[0]);
		window.setView(camera[0].set_view(player[0], map[0]));
		map[0].test_mort_enemies(volume);
		gui[0].draw_gui(window, camera[0], map[0], player[0]);

		if (player[0].test_mort(volume))
		{
			player[0].stop_sound_speed();
			reset_jeu();
			window.setView(View(Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGTH / 2), Vector2f(WINDOW_WIDTH, WINDOW_HEIGTH)));
			return 5;
		}
		if (input[0].get_btnB())
		{
			player[0].stop_sound_speed();
			window.setView(View(Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGTH / 2), Vector2f(WINDOW_WIDTH, WINDOW_HEIGTH)));
			return 4;
		}
		window.display();
	}

	return 0;
}

void Jeu::reset_jeu()
{
	gui.clear();
	input.clear();
	camera.clear();
	player.clear();
	map.clear();
}
