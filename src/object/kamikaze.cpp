#include "../include/enemy.h"

Kamikaze::Kamikaze(int vie, int vitesse, int dega, int t) : Enemy(vie, vitesse, dega, t)
{
	if (!enemyTexture.loadFromFile("src/assets/graphics/kamikaze.png"))
		cerr << "erreur chargement du kamikaze" << endl;
	else
		enemy.setTexture(enemyTexture);
}