#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Enemy
{
public:
	int enemy_gpc_hdl_ = 0;
	int hp_ = 10;
	int speed_ = 10;
	tnl::Vector3 pos_ = {500, 0, 0};

	void attack() {};

	void move();
};

