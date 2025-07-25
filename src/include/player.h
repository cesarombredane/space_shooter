#pragma once
#define PLAYER_H
#ifdef PLAYER_H

// INCLUDE
#include "jeu.h"
#include <math.h>

class Map;
class Camera;
class Bullet;
class Input;
class Gui;

class Player
{
private:
	const int SPEED_PLAYER = 8;
	const int CADENCE = 10;
	const int BULLET_SPEED = 25;

	SoundBuffer bufferPiou;
	Sound soundPiou;

	SoundBuffer bufferDeath;
	Sound soundDeath;

	SoundBuffer bufferHit;
	Sound soundHit;

	SoundBuffer bufferSpeed;
	Sound soundSpeed;
	bool soundTimer;

	Texture playerspriteTexture;
	Sprite playersprite;

	Vector2f posPlayer;
	Vector2f playerSpeed;

	float rotationPlayer;
	int cadencePlayer;
	vector<Bullet> chargeurPlayer;
	bool isFireing;
	int viePLayer;

	// colisions
	bool colDroite, colGauche, colBas, colHaut;
	bool colCorTopLeft, colCorTopRight, colCorBotLeft, colCorBotRight;
	int nbPixelColDroite, nbPixelColGauche, nbPixelColBas, nbPixelColHaut;
	bool GoDroite, GoGauche, GoHaut, GoBas;

	bool super_speed;

public:
	Player(Map &);

	// getters
	Vector2f get_posPlayer();
	Vector2f get_playerSpeed();
	float get_rotationPlayer();
	int get_cadencePlayer();
	vector<Bullet> get_chargeurPlayer();
	int get_viePLayer();

	void stop_sound_speed();

	// visuel
	void draw_player(RenderWindow &);
	void rotation_player(Input &);

	// deplacement
	void move_input(Input &input);
	void colision(Map &map, Gui &, int, Camera &);
	void move();

	void player_fire(Input &, RenderWindow &, Map &, Camera &, Gui &, int);
	void player_take_damage(int, int);

	bool test_mort(int);
};

#endif // PLAYER_H
