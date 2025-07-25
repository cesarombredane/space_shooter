#pragma once
#define SPAWNER_H
#ifdef SPAWNER_H

// INCLUDE
#include <cstdlib>
#include "jeu.h"

class Sniper;
class Kamikaze;
class Enemy;
class Map;

class Spawner
{
private:
	Vector2f posSpawner;

public:
	Spawner(Vector2f);

	Vector2f get_pos_spawner();

	void spawn(int, Map &map);
};

#endif // SPAWNER_H
