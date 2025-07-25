#include "Player.h"

Player::Player(Map &map) {
	if (!playerspriteTexture.loadFromFile("files/graphics/Player.png"))
		cerr << "erreur chargement du player" << endl;
	else playersprite.setTexture(playerspriteTexture);

	if (!bufferPiou.loadFromFile("files/sons/piou.wav")) {
		cerr << "erreur de chargement sound 'piou'" << endl;
	}
	if (!bufferSpeed.loadFromFile("files/sons/speed.wav")) {
		cerr << "erreur de chargement sound 'speed'" << endl;
	}
	if (!bufferDeath.loadFromFile("files/sons/death.wav")) {
		cerr << "erreur de chargement sound 'death'" << endl;
	}
	if (!bufferHit.loadFromFile("files/sons/impact_player.wav")) {
		cerr << "erreur de chargement sound 'death'" << endl;
	}

	posPlayer.x = (map.get_map()[0].size() * TILE_SIZE) / 2 + (TILE_SIZE / 2);
	posPlayer.y = (map.get_map().size() * TILE_SIZE) / 2;
	playerSpeed.x = playerSpeed.y = 0;
	rotationPlayer = 0;
	cadencePlayer = 0;
	viePLayer = 100;
	playersprite.setOrigin(TILE_SIZE / 2, TILE_SIZE / 2);
	playersprite.setPosition(posPlayer);
}

Vector2f Player::get_posPlayer() {
	return posPlayer;
}

float Player::get_rotationPlayer() {
	return rotationPlayer;
}

int Player::get_cadencePlayer() {
	return cadencePlayer;
}

vector<Bullet> Player::get_chargeurPlayer() {
	return chargeurPlayer;
}

int Player::get_viePLayer() {
	return viePLayer;
}

Vector2f Player::get_playerSpeed() {
	return playerSpeed;
}

void Player::draw_player(RenderWindow &window) {
	playersprite.setPosition(posPlayer);
	playersprite.setTexture(playerspriteTexture);
	window.draw(playersprite);
}

void Player::rotation_player(Input &input) {
	rotationPlayer = atan2(input.get_dir().x, -input.get_dir().y);
	playersprite.setRotation(rotationPlayer * 180 / PI);
}

void Player::move_input(Input &input) {
	GoBas = false;
	GoHaut = false;
	GoDroite = false;
	GoGauche = false;
	playerSpeed.x = playerSpeed.y = 0;

	if ((int)input.get_dir().y < 0) {
		GoHaut = true;
		playerSpeed.y = SPEED_PLAYER;
	}
	else if ((int)input.get_dir().y > 0) {
		GoBas = true;
		playerSpeed.y = SPEED_PLAYER;
	}

	if ((int)input.get_dir().x < 0) {
		GoGauche = true;
		playerSpeed.x = SPEED_PLAYER;
	}
	else if ((int)input.get_dir().x > 0) {
		GoDroite = true;
		playerSpeed.x = SPEED_PLAYER;
	}
}

void Player::colision(Map &map, Gui &gui, int volume, Camera &camera) {
	for (int i = 0; i < playerSpeed.x; i++) {
		// RIGHT
		if (map.colision(posPlayer.x + (TILE_SIZE / 2) - 1 + i, posPlayer.y + (TILE_SIZE / 2) - 1) > map.get_collision_block()) {
			colDroite = true;
			nbPixelColDroite = i;
			break;
		}
		else if (map.colision(posPlayer.x + (TILE_SIZE / 2) - 1 + i, posPlayer.y - (TILE_SIZE / 2)) > map.get_collision_block()) {
			colDroite = true;
			nbPixelColDroite = i;
		}
		else colDroite = false;
		// LEFT
		if (map.colision(posPlayer.x - (TILE_SIZE / 2) - i, posPlayer.y + (TILE_SIZE / 2) - 1) > map.get_collision_block()) {
			colGauche = true;
			nbPixelColGauche = i;
			break;
		}
		else if (map.colision(posPlayer.x - (TILE_SIZE / 2) - i, posPlayer.y - (TILE_SIZE / 2)) > map.get_collision_block()) {
			colGauche = true;
			nbPixelColGauche = i;
		}
		else colGauche = false;
	}

	for (int i = 0; i < playerSpeed.y; i++) {
		// DOWN
		if (map.colision(posPlayer.x + (TILE_SIZE / 2) - 1, posPlayer.y + (TILE_SIZE / 2) - 1 + i) > map.get_collision_block()) {
			colBas = true;
			nbPixelColBas = i;
			break;
		}
		else if (map.colision(posPlayer.x - (TILE_SIZE / 2), posPlayer.y + (TILE_SIZE / 2) - 1 + i) > map.get_collision_block()) {
			colBas = true;
			nbPixelColBas = i;
		}
		else colBas = false;
		// UP
		if (map.colision(posPlayer.x + (TILE_SIZE / 2) - 1, posPlayer.y - (TILE_SIZE / 2) - i) > map.get_collision_block()) {
			colHaut = true;
			nbPixelColHaut = i;
			break;
		}
		else if (map.colision(posPlayer.x - (TILE_SIZE / 2), posPlayer.y - (TILE_SIZE / 2) - i) > map.get_collision_block()) {
			colHaut = true;
			nbPixelColHaut = i;
		}
		else colHaut = false;
	}
	// CORNER
	if (!colGauche) {
		if (map.colision(posPlayer.x - (TILE_SIZE / 2) - playerSpeed.x, posPlayer.y - (TILE_SIZE / 2) - playerSpeed.y) > map.get_collision_block()) {
			colCorTopLeft = true;
		}
		else colCorTopLeft = false;
		if (map.colision(posPlayer.x - (TILE_SIZE / 2) - playerSpeed.x, posPlayer.y + (TILE_SIZE / 2) - 1 + playerSpeed.y) > map.get_collision_block()) {
			colCorBotLeft = true;
		}
		else colCorBotLeft = false;
	}
	
	if (!colDroite) {
		if (map.colision(posPlayer.x + (TILE_SIZE / 2) - 1 + playerSpeed.x, posPlayer.y - (TILE_SIZE / 2) - playerSpeed.y) > map.get_collision_block()) {
			colCorTopRight = true;
		}
		else colCorTopRight = false;
		if (map.colision(posPlayer.x + (TILE_SIZE / 2) - 1 + playerSpeed.x, posPlayer.y + (TILE_SIZE / 2) - 1 + playerSpeed.y) > map.get_collision_block()) {
			colCorBotRight = true;
		}
		else colCorBotRight = false;
	}
	map.active_enemies(camera);
	// Enemies
	for (int i = 0; i < map.get_active_enemy_map().size(); i++) {
		
		if (!(posPlayer.x + (TILE_SIZE / 2) < map.get_enemy_map()[map.get_active_enemy_map()[i]].get_pos_enemy().x - (TILE_SIZE / 2) ||
			posPlayer.x - (TILE_SIZE / 2) > map.get_enemy_map()[map.get_active_enemy_map()[i]].get_pos_enemy().x + (TILE_SIZE / 2) ||
			posPlayer.y + (TILE_SIZE / 2) < map.get_enemy_map()[map.get_active_enemy_map()[i]].get_pos_enemy().y - (TILE_SIZE / 2) ||
			posPlayer.y - (TILE_SIZE / 2) > map.get_enemy_map()[map.get_active_enemy_map()[i]].get_pos_enemy().y + (TILE_SIZE / 2))) {


			if (map.get_enemy_map()[map.get_active_enemy_map()[i]].get_type() == 0) {
				player_take_damage(map.get_enemy_map()[map.get_active_enemy_map()[i]].get_damage_enemy(), volume);
				gui.new_dega(posPlayer, map.get_enemy_map()[map.get_active_enemy_map()[i]].get_damage_enemy());
				map.enemy_damage(map.get_active_enemy_map()[i], 100, volume);
			}
			else {
				map.enemy_damage(map.get_active_enemy_map()[i], 100, volume);
			}
		}
	}

	if (map.colision(posPlayer.x, posPlayer.y) == 1) {
		if (soundTimer == false) {
			soundSpeed.setBuffer(bufferSpeed);
			soundSpeed.setVolume(volume);
			soundSpeed.setLoop(true);
			soundSpeed.play();
			soundTimer = true;
		}
		super_speed = true;
	}
	else {
		super_speed = false;
		soundSpeed.stop();
		soundTimer = false;
	}
	
}

void Player::move() {
	// RIGHT
	if (GoDroite && !colDroite) {
		if (super_speed) posPlayer.x += SPEED_PLAYER * 2;
		else posPlayer.x += SPEED_PLAYER;
	}

	// LEFT
	if (GoGauche && !colGauche) {
		if (super_speed) posPlayer.x -= SPEED_PLAYER * 2;
		else posPlayer.x -= SPEED_PLAYER;
	}

	// DOWN
	if (GoBas && !colBas && !colCorBotLeft && !colCorBotRight) {
		if (super_speed) posPlayer.y += SPEED_PLAYER * 2;
		else posPlayer.y += SPEED_PLAYER;
	}

	// TOP
	if (GoHaut && !colHaut && !colCorTopLeft && !colCorTopRight) {
		if (super_speed) posPlayer.y -= SPEED_PLAYER * 2;
		else posPlayer.y -= SPEED_PLAYER;
	}
}

void Player::player_fire(Input &input, RenderWindow &window, Map &map, Camera &camera, Gui &gui, int volume) {
	if (input.get_btnA() && cadencePlayer == 0) {
		isFireing = true;
		soundPiou.setBuffer(bufferPiou);
		soundPiou.setVolume(volume);
		soundPiou.stop();
		soundPiou.play();
	}
	if (isFireing) {

		Bullet newBullet(10);
		newBullet.set_pos_bullet(posPlayer, rotationPlayer * 180 / PI);
		newBullet.set_dir_bullet(Vector2f(BULLET_SPEED * cos(rotationPlayer - PI / 2), BULLET_SPEED * sin(rotationPlayer - PI / 2)));
		chargeurPlayer.push_back(newBullet);
		cadencePlayer = CADENCE;
		isFireing = false;
	}

	if (cadencePlayer != 0) {
		cadencePlayer--;
	}

	for (int i = 0; i < chargeurPlayer.size(); i++) {
		chargeurPlayer[i].draw_bullet(window);
		chargeurPlayer[i].fire_bullet();

		if (chargeurPlayer[i].colision_bullet(map, camera, gui, volume)) {
			chargeurPlayer[i].draw_bullet(window);
			chargeurPlayer.erase(chargeurPlayer.begin() + i);
		} 
	}
}

void Player::player_take_damage(int dega, int volume) {
	soundHit.setBuffer(bufferHit);
	soundHit.setVolume(volume);
	soundHit.stop();
	soundHit.play();
	viePLayer -= dega;
}

bool Player::test_mort(int volume) {
	if (viePLayer <= 0) {
		soundDeath.setBuffer(bufferDeath);
		soundDeath.setVolume(volume);
		soundDeath.stop();
		soundDeath.play();
	}
	return viePLayer <= 0;
}

void Player::stop_sound_speed() {
	soundSpeed.stop();
}