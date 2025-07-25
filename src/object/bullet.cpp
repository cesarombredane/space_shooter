#include "../include/bullet.h"

Bullet::Bullet(int dega)
{
	if (!bulletSpriteTexture.loadFromFile("src/assets/graphics/bullet.png"))
	{
		cerr << "erreur chargement des bullet" << endl;
	}
	else
	{
		bulletSprite.setTexture(bulletSpriteTexture);
	}

	bulletSprite.setOrigin(3, 0);

	degaBullet = dega;
}

Vector2f Bullet::get_pos_bullet()
{
	return posBullet;
}
Vector2f Bullet::get_dir_bullet()
{
	return directionBullet;
}

void Bullet::set_pos_bullet(Vector2f pos, float rotation)
{
	posBullet = pos;
	bulletSprite.setPosition(posBullet);
	bulletSprite.setRotation(rotation);
}
void Bullet::set_dir_bullet(Vector2f dir)
{
	directionBullet = dir;
}

void Bullet::fire_bullet()
{
	posBullet.x += directionBullet.x;
	posBullet.y += directionBullet.y;
	bulletSprite.setPosition(posBullet);
}

void Bullet::draw_bullet(RenderWindow &window)
{
	bulletSprite.setTexture(bulletSpriteTexture);
	window.draw(bulletSprite);
}

bool Bullet::colision_bullet(Map &map, Camera &camera, Gui &gui, int volume)
{
	if (posBullet.x < camera.get_pos_camera().x - (WINDOW_WIDTH / 2) ||
			posBullet.x > camera.get_pos_camera().x + (WINDOW_WIDTH / 2) ||
			posBullet.y < camera.get_pos_camera().y - (WINDOW_WIDTH / 2) ||
			posBullet.y > camera.get_pos_camera().y + (WINDOW_WIDTH / 2))
		return true;

	for (size_t i = 0; i < map.get_active_enemy_map().size(); i++)
	{
		if (posBullet.x < map.get_enemy_map()[map.get_active_enemy_map()[i]].get_pos_enemy().x + (TILE_SIZE / 2) &&
				posBullet.x > map.get_enemy_map()[map.get_active_enemy_map()[i]].get_pos_enemy().x - (TILE_SIZE / 2) &&
				posBullet.y < map.get_enemy_map()[map.get_active_enemy_map()[i]].get_pos_enemy().y + (TILE_SIZE / 2) &&
				posBullet.y > map.get_enemy_map()[map.get_active_enemy_map()[i]].get_pos_enemy().y - (TILE_SIZE / 2))
		{

			gui.new_dega(posBullet, degaBullet);
			map.enemy_damage(map.get_active_enemy_map()[i], degaBullet, volume);
			return true;
		}
	}
	return map.colision(posBullet.x, posBullet.y) > map.get_collision_block();
}