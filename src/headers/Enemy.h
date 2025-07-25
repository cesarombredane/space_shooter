#pragma once
#define ENEMY_H
#ifdef ENEMY_H

// INCLUDE
#include "Jeu.h"

class Bullet;

class Enemy{
protected:
	Sprite enemy;
	Texture enemyTexture;

	SoundBuffer bufferHit_enemy;
	Sound soundHit_enemy;

	Vector2f posEnemy;
	Vector2f speedEnemy;
	Vector2f dirEnemy;

	float rotationEnemy;
	int vieEnemy;
	int vitesseEnemy;
	int damageEnemy;
	int type;

	bool colTop, colDown, colRight, colLeft;
	bool goTop, goDown, goRight, goLeft;

public:
	Enemy(int, int, int, int);

	Vector2f get_pos_enemy();
	int get_vie();
	void set_pos_enemy(Vector2f);
	int get_type();
	int get_damage_enemy();

	void rotation_enemy();
	void draw_enemy(RenderWindow &);
	void take_damage(int, int);

	void move_input_enemy(string);
	void colision_enemy(Map &map);
	void move_enemy(string s);
};

class Sniper : public Enemy {
private:
	vector<Bullet> chargeurSniper;
	int cadenceSniper;

public:
	Sniper(int, int, int, int);
};

class Kamikaze : public Enemy {
private:

public:
	Kamikaze(int, int, int, int);
};

#endif // ENEMY_H