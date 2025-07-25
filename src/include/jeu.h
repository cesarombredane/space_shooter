#pragma once
#define JEU_H
#ifdef JEU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>

using namespace std;
using namespace sf;

// INCLUDES
#include "input.h"
#include "map.h"
#include "player.h"
#include "camera.h"
#include "bullet.h"
#include "enemy.h"
#include "spawner.h"
#include "gui.h"
#include "pathfinding.h"

#define PI 3.14159265

class Gui;

const size_t WINDOW_WIDTH = 1280;
const size_t WINDOW_HEIGTH = 720;
const size_t TILE_SIZE = 64;

class Jeu
{
private:
	int carte;
	int difficulte;
	int volume;

	vector<Gui> gui;
	vector<Camera> camera;
	vector<Input> input;
	vector<Map> map;
	vector<Player> player;

public:
	Jeu();

	void load_jeu(int, int, int);
	int open(RenderWindow &);
	void reset_jeu();
};

#endif // JEU_H
