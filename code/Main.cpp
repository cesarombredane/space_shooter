#include "Jeu.h"

int main() {
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGTH), "projet tutor�");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	Jeu jeu;
	jeu.load_jeu(1, 1, 50);
	jeu.open(window);

	return 0;
}