#include "Enemy.h"


void Enemy::move()
{
	pos_.y += speed_;
}

void Enemy::hit(int damage) {
	hp_ -= damage;

	if (hp_ <= 0) {
		enemy_gpc_hdl_ = 0;
		Death();
	}
}

