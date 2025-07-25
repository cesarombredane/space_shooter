#pragma once
#define CAMERA_H
#ifdef CAMERA_H

// INCLUDE
#include "jeu.h"

class Player;
class Map;

class Camera
{
private:
	const int FREEPLACE_X = 200;
	const int FREEPLACE_Y = 100;
	Vector2f posCamera;

	bool goRight, goLeft, goUp, goDown;

public:
	Camera(Map &, Player &);

	bool get_goRight();
	bool get_goLeft();
	bool get_goUp();
	bool get_goDown();
	Vector2f get_pos_camera();

	View set_view(Player &, Map &);
};

#endif // CAMERA_H
