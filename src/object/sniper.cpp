#include "../include/enemy.h"

Sniper::Sniper(int vie, int vitesse, int dega, int t) : Enemy(vie, vitesse, dega, t)
{
	if (!enemyTexture.loadFromFile("src/assets/graphics/sniper.png"))
		cerr << "erreur chargement du sniper" << endl;
	else
		enemy.setTexture(enemyTexture);
}