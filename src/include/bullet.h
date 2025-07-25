#pragma once
#define BULLET_H
#ifdef BULLET_H

// INCLUDE
#include <math.h>
#include "jeu.h"

class Jeu;
class Map;
class Camera;
class Gui;

class Bullet
{
private:
	Texture bulletSpriteTexture;
	Sprite bulletSprite;

	Vector2f posBullet;
	Vector2f directionBullet;
	int degaBullet;

public:
	Bullet(int);

	Vector2f get_pos_bullet();
	Vector2f get_dir_bullet();

	void set_pos_bullet(Vector2f, float);
	void set_dir_bullet(Vector2f);

	void fire_bullet();
	void draw_bullet(RenderWindow &);
	bool colision_bullet(Map &, Camera &, Gui &, int);
};

#endif // BULLET_H
