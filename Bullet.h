#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Bullet
{

public:
	enum BulletState {
		FLYING,
		WAITING,
		MAX_STATUS_NUM,
	};

	int bullet_gpc_hdl_ = 0;
	int damage_ = 1;
	float speed_ = 10;
	tnl::Vector3 pos_ = {10000, 0, 0};
	BulletState current_bullet_state_ = WAITING;
};

