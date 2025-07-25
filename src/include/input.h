#pragma once
#define INPUT_H
#ifdef INPUT_H

// INCLUDE
#include "jeu.h"

class Input
{
private:
	Vector2f directionInput;
	bool btnA;
	bool btnB;

public:
	Input();

	Vector2f get_dir();
	bool get_btnA();
	bool get_btnB();

	void gestion_input(RenderWindow &);
};

#endif // INPUT_H
