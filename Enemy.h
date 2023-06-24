#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Enemy
{
private:
	int enemy_gpc_hdl_ = 0;
	int hp_ = 10;
	int speed_ = 10;
	tnl::Vector3 pos_ = { 500, 0, 0 };

public:
	Enemy(int hp, int speed, tnl::Vector3 originPos) {
		hp_ = hp;
		speed_ = speed;
		pos_ = originPos;
	}
	

	void setGpcHdl() {
		enemy_gpc_hdl_ = LoadGraph("graphics/Enemy.bmp");
	}

	int getGpcHdl() {
		return enemy_gpc_hdl_;
	}


	void hit(int damage) {
		hp_ -= damage;

		if (hp_ <= 0) {
			enemy_gpc_hdl_ = 0;
		}
	}

	tnl::Vector3 getPos() {
		return pos_;
	}

	void setPos(tnl::Vector3 pos) {
		pos_ = pos;
	}

	void attack() {};

	void move();
};

