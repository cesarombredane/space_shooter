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
			case Keyboard::A:
				directionInput.x = -100;
				break;

			case Keyboard::D:
				directionInput.x = 100;
				break;

			case Keyboard::W:
				directionInput.y = -100;
				break;

			case Keyboard::S:
				directionInput.y = 100;
				break;

			case Keyboard::Space:
				btnA = true;
				break;

			case Keyboard::LShift:
				btnB = true;
				break;

			case Keyboard::Escape:
				window.close();
				break;

			default:
				break;
			}
			break;

		case Event::KeyReleased: // gestion des la relachement des touches
			switch (event.key.code)
			{
			case Keyboard::A:
				if (directionInput.x < 0)
					directionInput.x = 0;
				break;

			case Keyboard::D:
				if (directionInput.x > 0)
					directionInput.x = 0;
				break;

			case Keyboard::W:
				if (directionInput.y < 0)
					directionInput.y = 0;
				break;

			case Keyboard::S:
				if (directionInput.y > 0)
					directionInput.y = 0;
				break;

			case Keyboard::Space:
				btnA = false;
				break;

			case Keyboard::LShift:
				btnB = false;
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}
	}
}