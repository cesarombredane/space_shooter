#include "../include/gui.h"

Gui::Gui()
{
}

void Gui::load_gui()
{
	vie.setSize(Vector2f(200, 40));
	vie.setFillColor(Color(255, 0, 0));

	contourVie.setSize(Vector2f(220, 60));
	contourVie.setFillColor(Color(0, 0, 0));

	if (!font.loadFromFile("src/assets/beon.ttf"))
	{
		cerr << "erreur chargement des font" << endl;
	}
	nbPoint.setFont(font);
	nbPoint.setCharacterSize(50);
	nbPoint.setFillColor(Color(255, 255, 255));
	nbPoint.setString("0");
}

void Gui::draw_gui(RenderWindow &window, Camera &camera, Map &map, Player &player)
{
	update_score(map);
	update_vie(player);

	contourVie.setPosition(Vector2f(camera.get_pos_camera().x - (WINDOW_WIDTH / 2) + 20, camera.get_pos_camera().y - (WINDOW_HEIGTH / 2) + 20));
	vie.setPosition(Vector2f(camera.get_pos_camera().x - (WINDOW_WIDTH / 2) + 30, camera.get_pos_camera().y - (WINDOW_HEIGTH / 2) + 30));
	nbPoint.setPosition(Vector2f(camera.get_pos_camera().x + (WINDOW_WIDTH / 2) - 165, camera.get_pos_camera().y - (WINDOW_HEIGTH / 2) + 5));

	window.draw(contourVie);
	window.draw(vie);
	window.draw(nbPoint);

	for (size_t i = 0; i < vector_degas.size(); i++)
	{
		Text t;
		t.setFont(font);
		t.setCharacterSize(50);
		t.setStyle(Text::Bold);
		t.setFillColor(Color(255, 0, 0));
		t.setString(to_string(vector_degas[i].degaDega));
		t.setPosition(vector_degas[i].posDega);
		window.draw(t);
		decay_dega(i);
		if (vector_degas[i].tmpDega == 0)
		{
			vector_degas.erase(vector_degas.begin() + i);
		}
	}
}

void Gui::update_score(Map &map)
{
	nbPoint.setString(to_string(map.get_point()));
}

void Gui::update_vie(Player &player)
{
	if (player.get_viePLayer() > 0)
	{
		vie.setSize(Vector2f(player.get_viePLayer() * 2, 40));
	}
	else
		vie.setSize(Vector2f(0, 40));
}

void Gui::new_dega(Vector2f p, int d)
{
	dega dega;
	dega.posDega = p;
	dega.degaDega = d;
	dega.tmpDega = 30;
	vector_degas.push_back(dega);
}

void Gui::decay_dega(int ind)
{
	vector_degas[ind].tmpDega--;
}