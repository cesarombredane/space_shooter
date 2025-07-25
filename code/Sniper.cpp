#include "Enemy.h"

Sniper::Sniper(int vie, int vitesse, int dega, int t) : Enemy(vie, vitesse, dega, t) {
	if (!enemyTexture.loadFromFile("files/graphics/sniper.png"))
		cerr << "erreur chargement du sniper" << endl;
	else enemy.setTexture(enemyTexture);
}