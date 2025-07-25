#include "Camera.h"

Camera::Camera(Map &map, Player &player) {
	posCamera.x = player.get_posPlayer().x;
	posCamera.y = player.get_posPlayer().y;

	
}

View Camera::set_view(Player &player, Map &map) {
	View view(Vector2f(posCamera.x, posCamera.y), Vector2f(WINDOW_WIDTH, WINDOW_HEIGTH));
	goRight = goLeft = goUp = goDown = false;

	if (player.get_posPlayer().x < posCamera.x - FREEPLACE_X) {
		if (player.get_posPlayer().x + FREEPLACE_X - (WINDOW_WIDTH / 2) > 0) {
			posCamera.x = player.get_posPlayer().x + FREEPLACE_X;
			goRight = true;
		}
	}
	else if (player.get_posPlayer().x > posCamera.x + FREEPLACE_X) {
		if (player.get_posPlayer().x - FREEPLACE_X + (WINDOW_WIDTH / 2) < map.get_map()[0].size() * TILE_SIZE) {
			posCamera.x = player.get_posPlayer().x - FREEPLACE_X;
			goLeft = true;
		}
	}

	if (player.get_posPlayer().y < posCamera.y - FREEPLACE_Y) {
		if (player.get_posPlayer().y + FREEPLACE_Y - (WINDOW_HEIGTH / 2) > 0) {
			posCamera.y = player.get_posPlayer().y + FREEPLACE_Y;
			goDown = true;
		}
	}
	else if (player.get_posPlayer().y > posCamera.y + FREEPLACE_Y) {
		if (player.get_posPlayer().y - FREEPLACE_Y + (WINDOW_HEIGTH / 2) < map.get_map().size() * TILE_SIZE) {
			posCamera.y = player.get_posPlayer().y - FREEPLACE_Y;
			goUp = true;
		}
	}
	view.setCenter(posCamera.x, posCamera.y);

	return view;
}

bool Camera::get_goRight() {
	return goRight;
}
bool Camera::get_goLeft() {
	return goLeft;
}
bool Camera::get_goUp() {
	return goUp;
}
bool Camera::get_goDown() {
	return goDown;
}
Vector2f Camera::get_pos_camera() {
	return posCamera;
}