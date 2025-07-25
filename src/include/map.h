#pragma once
#define MAP_H
#ifdef MAP_H

// INCLUDE
#include "jeu.h"
#include <sstream>
#include <string>
#include <fstream>

class Camera;
class Player;
class Spawner;
class Enemy;

class Map
{
private:
	const int COLLISION_BLOCK = 1;
	const int SPAWNER = 2;
	const int BG_SPEED = 1;
	int cadence_spawn;
	int difficulte;
	int score;

	SoundBuffer buffer_death_enemy;
	Sound sound_death_enemy;

	vector<vector<int>> map;
	vector<Spawner> spawner_map;
	vector<Enemy> enemy_map;
	vector<int> active_enemy_map;

	Texture backgroundTexture;
	Sprite background;

	Texture tileSetTexture;
	Sprite tileSet;

	int spawn_time;
	Vector2f moveBG;

	vector<string> pathfinder;
	int pathfind_timer;

public:
	Map(int);

	vector<vector<int>> get_map();
	int get_ind_map(int, int);
	int get_collision_block();
	int get_difficulte();
	vector<Spawner> get_spawner_map();
	vector<Enemy> get_enemy_map();
	vector<int> get_active_enemy_map();
	int get_point();

	void add_enemy(Enemy &);
	void add_point(int);

	void draw_enemies(RenderWindow &);
	void move_enemies(Player &, Map &map);
	void active_enemies(Camera &);
	void enemy_damage(int, int, int);
	void test_mort_enemies(int);

	void load_map(int);
	void draw_map(RenderWindow &, Camera &camera);
	void load_BG(Player &player);
	void draw_BG(RenderWindow &, Player &, Camera &);

	int colision(int, int);

	void create_spawner();
	void tick_spawner(RenderWindow &, Map &, Camera &, Player &);
};

#endif // MAP_H
