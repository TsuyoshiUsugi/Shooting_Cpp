#pragma once
#include "../dxlib_ext/dxlib_ext.h"

enum class BulletState {
	FLYING,
	WAITING,
	MAX_STATUS_NUM,
};

class Bullet
{
private:
	int bullet_gpc_hdl_ = 0;
	int damage_ = 1;
	float speed_ = 10;
	tnl::Vector3 pos_ = { 10000, 0, 0 };
	BulletState current_bullet_state_ = BulletState::WAITING;

public:
	Bullet(int damage, float speed) {
		damage_ = damage;
		speed_ = speed;
	}

	void SetGpcHdl() {
		bullet_gpc_hdl_ = LoadGraph("graphics/red1.bmp");
	}

	int getGpcHdl() {
		return bullet_gpc_hdl_;
	}

	int getBulletDamage() {
		return damage_;
	}

	int getSpeed() {
		return speed_;
	}

	tnl::Vector3 getPos() {
		return pos_;
	}

	void setPos(tnl::Vector3 pos) {
		pos_ = pos;
	}

	BulletState currentState() {
		return current_bullet_state_;
	}

	/// <summary>
	/// 引き数のステートに弾の状態を変える
	/// </summary>
	/// <param name="state"></param>
	void SwitchState(BulletState state) {
		current_bullet_state_ = state;
	}

	void move() {
		pos_.y -= speed_;
	}
};

