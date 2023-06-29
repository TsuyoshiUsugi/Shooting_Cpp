#include "Player.h"

void Player::fire() {

}

void Player::move(bool isRight) {
	if (isRight) current_player_pos_.x += speed_;
	else current_player_pos_.x -= speed_;
}

void Player::setPos(float x, float y) {
	current_player_pos_.x = x;
	current_player_pos_.y = y;
}

void Player::Hit(int damage) {
	hp_ -= damage;

	if (hp_ <= 0)
	{
		hp_ = 0;
		isDeath_ = true;
	}
}