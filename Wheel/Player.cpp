#include "Player.h"

int Player::numberPlayer = 0;
int Player::currentPlayer =0;

Player::Player() : Sprite() {
	numberPlayer++;
	stringstream ss;
	ss << numberPlayer;
	name = "Player" + ss.str();
	total_score = 0;
	score = 0;
	turn_left = 3;
	status = AWAIT;
	turn_gift = 0;
}

Player::Player(string na) : Sprite() {
	numberPlayer++;
	total_score = 0;
	score = 0;
	name = na;
	status = AWAIT;
	turn_gift = 0;
}

int Player::spin(Wheel* wheel) {
	if(wheel->spin() == Wheel::STOP) {
		int TossUp = wheel->getTossUp();
		if(keyboard!=NULL)
			keyboard->setStatus(Keyboard::AVAILABLE);
		return TossUp;
	}
	else return Wheel::SPINNING;
}


bool Player::answer() {
	if(keyboard->chose() == "A")
		return true;
	else return false;
}