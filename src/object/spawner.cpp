#include "../include/spawner.h"

Spawner::Spawner(Vector2f pos)
{
	posSpawner = pos;
}

Vector2f Spawner::get_pos_spawner()
{
	return posSpawner;
}

void Spawner::spawn(int difficulte, Map &map)
{
	if ((rand() % 10) < 2)
	{
		// sniper
		if (difficulte == 1)
		{
			Sniper s(20, 4, 10, 1);
			s.set_pos_enemy(posSpawner);
			map.add_enemy(s);
		}
		else if (difficulte == 2)
		{
			Sniper s(40, 6, 15, 1);
			s.set_pos_enemy(posSpawner);
			map.add_enemy(s);
		}
		else if (difficulte == 3)
		{
			Sniper s(50, 8, 20, 1);
			s.set_pos_enemy(posSpawner);
			map.add_enemy(s);
		}
		else
			cerr << "erreur difficulte" << endl;
	}
	else
	{
		// kamikaze
		if (difficulte == 1)
		{
			Kamikaze k(10, 6, 10, 0);
			k.set_pos_enemy(posSpawner);
			map.add_enemy(k);
		}
		else if (difficulte == 2)
		{
			Kamikaze k(20, 8, 25, 0);
			k.set_pos_enemy(posSpawner);
			map.add_enemy(k);
		}
		else if (difficulte == 3)
		{
			Kamikaze k(30, 10, 50, 0);
			k.set_pos_enemy(posSpawner);
			map.add_enemy(k);
		}
		else
			cerr << "erreur difficulte" << endl;
	}
}