#include "Enemy.h"

Enemy::Enemy(int vie, int vitesse, int damage, int t)
{
	if (!bufferHit_enemy.loadFromFile("src/assets/sounds/impact_enemy.wav"))
	{
		cerr << "erreur de chargement sound 'death_enemy'" << endl;
	}

	type = t;
	damageEnemy = damage;
	vieEnemy = vie;
	vitesseEnemy = vitesse;
	enemy.setOrigin(32, 32);
}

void Enemy::set_pos_enemy(Vector2f pos)
{
	posEnemy = pos;
}

int Enemy::get_type()
{
	return type;
}

int Enemy::get_damage_enemy()
{
	return damageEnemy;
}

Vector2f Enemy::get_pos_enemy()
{
	return posEnemy;
}

int Enemy::get_vie()
{
	return vieEnemy;
}

void Enemy::rotation_enemy()
{
	rotationEnemy = atan2(dirEnemy.x, -dirEnemy.y);
	enemy.setRotation(rotationEnemy * 180 / PI);
}

void Enemy::draw_enemy(RenderWindow &window)
{
	enemy.setPosition(posEnemy);
	enemy.setTexture(enemyTexture);
	window.draw(enemy);
}

void Enemy::take_damage(int dega, int volume)
{
	soundHit_enemy.setBuffer(bufferHit_enemy);
	soundHit_enemy.setVolume(volume);
	soundHit_enemy.stop();
	soundHit_enemy.play();
	vieEnemy -= dega;
}

void Enemy::move_input_enemy(string s)
{
	goDown = goTop = goRight = goLeft = false;
	speedEnemy.x = speedEnemy.y = 0;
	dirEnemy.x = dirEnemy.y = 0;

	int move = s[0] - 48;

	switch (move)
	{
	case 0:
		speedEnemy.x += vitesseEnemy;
		dirEnemy.x = 1;
		goRight = true;
		break;
	case 1:
		speedEnemy.x += vitesseEnemy;
		speedEnemy.y += vitesseEnemy;
		dirEnemy.x = 1;
		dirEnemy.y = 1;
		goRight = goDown = true;
		break;
	case 2:
		speedEnemy.y += vitesseEnemy;
		dirEnemy.y = 1;
		goDown = true;
		break;
	case 3:
		speedEnemy.x += vitesseEnemy;
		speedEnemy.y += vitesseEnemy;
		dirEnemy.x = -1;
		dirEnemy.y = 1;
		goLeft = goDown = true;
		break;
	case 4:
		speedEnemy.x += vitesseEnemy;
		goLeft = true;
		dirEnemy.x = -1;
		break;
	case 5:
		speedEnemy.x += vitesseEnemy;
		speedEnemy.y += vitesseEnemy;
		dirEnemy.x = -1;
		dirEnemy.y = -1;
		goLeft = goTop = true;
		break;
	case 6:
		speedEnemy.y += vitesseEnemy;
		dirEnemy.y = -1;
		goTop = true;
		break;
	case 7:
		speedEnemy.x += vitesseEnemy;
		speedEnemy.y += vitesseEnemy;
		dirEnemy.x = 1;
		dirEnemy.y = -1;
		goRight = goTop = true;
		break;
	default:
		break;
	}
}

void Enemy::colision_enemy(Map &map)
{
	if (posEnemy.y > map.get_map().size() * TILE_SIZE || posEnemy.y < 0 ||
			posEnemy.x > map.get_map()[0].size() * TILE_SIZE || posEnemy.x < 0)
	{
		vieEnemy = 0;
	}
	else
	{
		for (int i = 0; i < speedEnemy.x; i++)
		{
			// RIGHT
			if (map.colision(posEnemy.x + (TILE_SIZE / 2) - 1 + i, posEnemy.y + (TILE_SIZE / 2) - 1) > map.get_collision_block())
			{
				colRight = true;
				break;
			}
			else if (map.colision(posEnemy.x + (TILE_SIZE / 2) - 1 + i, posEnemy.y - (TILE_SIZE / 2)) > map.get_collision_block())
			{
				colRight = true;
			}
			else
				colRight = false;
			// LEFT
			if (map.colision(posEnemy.x - (TILE_SIZE / 2) - i, posEnemy.y + (TILE_SIZE / 2) - 1) > map.get_collision_block())
			{
				colLeft = true;
				break;
			}
			else if (map.colision(posEnemy.x - (TILE_SIZE / 2) - i, posEnemy.y - (TILE_SIZE / 2)) > map.get_collision_block())
			{
				colLeft = true;
			}
			else
				colLeft = false;
		}

		for (int i = 0; i < speedEnemy.y; i++)
		{
			// DOWN
			if (map.colision(posEnemy.x + (TILE_SIZE / 2) - 1, posEnemy.y + (TILE_SIZE / 2) - 1 + i) > map.get_collision_block())
			{
				colDown = true;
				break;
			}
			else if (map.colision(posEnemy.x - (TILE_SIZE / 2), posEnemy.y + (TILE_SIZE / 2) - 1 + i) > map.get_collision_block())
			{
				colDown = true;
			}
			else
				colDown = false;
			// UP
			if (map.colision(posEnemy.x + (TILE_SIZE / 2) - 1, posEnemy.y - (TILE_SIZE / 2) - i) > map.get_collision_block())
			{
				colTop = true;
				break;
			}
			else if (map.colision(posEnemy.x - (TILE_SIZE / 2), posEnemy.y - (TILE_SIZE / 2) - i) > map.get_collision_block())
			{
				colTop = true;
			}
			else
				colTop = false;
		}
	}
}

void Enemy::move_enemy(string s)
{
	int move = s[0] - 48;

	switch (move)
	{
	case 0:
		// droite //////////////////////////////////////
		if (!colRight)
			posEnemy.x += vitesseEnemy;
		else
		{
			if (colDown)
				posEnemy.y -= vitesseEnemy;
			else if (colTop)
				posEnemy.y += vitesseEnemy;
		}
		break;
		////////////////////////////////////////////////
	case 1:
		// bas, droite /////////////////////////////////
		if (!colRight && !colLeft)
		{
			posEnemy.x += vitesseEnemy;
			posEnemy.y += vitesseEnemy;
		}
		else
		{
			if (colRight)
				posEnemy.y += vitesseEnemy;
			if (colLeft)
				posEnemy.x += vitesseEnemy;
		}
		break;
		////////////////////////////////////////////////
	case 2:
		// bas //////////////////////////////////////
		if (!colDown)
			posEnemy.y += vitesseEnemy;
		else
		{
			if (colRight)
				posEnemy.x -= vitesseEnemy;
			else if (colLeft)
				posEnemy.x += vitesseEnemy;
		}
		break;
		////////////////////////////////////////////////
		break;
	case 3:
		// bas, gauche /////////////////////////////////
		if (!colRight && !colLeft)
		{
			posEnemy.x -= vitesseEnemy;
			posEnemy.y += vitesseEnemy;
		}
		else
		{
			if (colRight)
				posEnemy.x -= vitesseEnemy;
			if (colLeft)
				posEnemy.y += vitesseEnemy;
		}
		break;
		////////////////////////////////////////////////
	case 4:
		// gauche //////////////////////////////////////
		if (!colLeft)
			posEnemy.x -= vitesseEnemy;
		else
		{
			if (colDown)
				posEnemy.y -= vitesseEnemy;
			else if (colTop)
				posEnemy.y += vitesseEnemy;
		}
		break;
		////////////////////////////////////////////////
	case 5:
		// haut, gauche /////////////////////////////////
		if (!colRight && !colLeft)
		{
			posEnemy.x -= vitesseEnemy;
			posEnemy.y -= vitesseEnemy;
		}
		else
		{
			if (colRight)
				posEnemy.x -= vitesseEnemy;
			if (colLeft)
				posEnemy.y -= vitesseEnemy;
		}
		break;
		////////////////////////////////////////////////
	case 6:
		// haut //////////////////////////////////////
		if (!colTop)
			posEnemy.y -= vitesseEnemy;
		else
		{
			if (colRight)
				posEnemy.x -= vitesseEnemy;
			else if (colLeft)
				posEnemy.x += vitesseEnemy;
		}
		break;
		////////////////////////////////////////////////
	case 7:
		// haut, droite /////////////////////////////////
		if (!colRight && !colLeft)
		{
			posEnemy.x += vitesseEnemy;
			posEnemy.y -= vitesseEnemy;
		}
		else
		{
			if (colRight)
				posEnemy.y -= vitesseEnemy;
			if (colLeft)
				posEnemy.x += vitesseEnemy;
		}
		break;
		////////////////////////////////////////////////
	default:
		break;
	}
}