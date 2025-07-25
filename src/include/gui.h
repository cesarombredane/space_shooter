#pragma once
#define Gui_H
#ifdef Gui_H

#include "jeu.h"

class Gui
{
private:
	struct dega
	{
		Vector2f posDega;
		int degaDega;
		int tmpDega;
	};

	RectangleShape vie;
	RectangleShape contourVie;
	Font font;
	Text nbPoint;
	vector<dega> vector_degas;

public:
	Gui();

	void load_gui();
	void draw_gui(RenderWindow &, Camera &, Map &, Player &);

	void update_score(Map &);
	void update_vie(Player &player);
	void new_dega(Vector2f, int);
	void decay_dega(int);
};

#endif // Gui_H
