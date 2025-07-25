#include "../include/input.h"

Input::Input()
{
	directionInput.x = 0;
	directionInput.y = 0;
}

Vector2f Input::get_dir()
{
	return directionInput;
}

bool Input::get_btnA()
{
	return btnA;
}

bool Input::get_btnB()
{
	return btnB;
}

void Input::gestion_input(RenderWindow &window)
{
	btnA = btnB = false;

	if (Joystick::isConnected(0))
	{
		directionInput.x = Joystick::getAxisPosition(0, Joystick::X);
		directionInput.y = Joystick::getAxisPosition(0, Joystick::Y);
		if (Joystick::isButtonPressed(0, 0))
		{
			btnA = true;
		}
		if (Joystick::isButtonPressed(0, 1))
		{
			btnB = true;
		}
	}

	Event event;

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case Event::Closed: // gestion de crash
			window.close();
			break;
		case Event::KeyPressed: // gestion des la pression des touches
			switch (event.key.code)
			{
			case Keyboard::Escape:
				window.close();
				break;
			}
			break;
		}
	}
}