#include "Enemy.h"

Kamikaze::Kamikaze(int vie, int vitesse, int dega, int t) : Enemy(vie, vitesse, dega, t) {
	if (!enemyTexture.loadFromFile("files/graphics/kamikaze.png"))
		cerr << "erreur chargement du kamikaze" << endl;
	else enemy.setTexture(enemyTexture);
}