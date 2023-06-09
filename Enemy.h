#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Enemy
{
private:
	int enemy_gpc_hdl_ = 0;
	int hp_ = 10;
	int speed_ = 10;
	int damage_ = 1;
	tnl::Vector3 pos_ = { 500, 0, 0 };

	void Death() {
		pos_ = {-1000, -1000, 0};
	}

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

	int getEnemyDamage() {
		return damage_;
	}

	tnl::Vector3 getPos() {
		return pos_;
	}

	void setPos(tnl::Vector3 pos) {
		pos_ = pos;
	}

	/// <summary>
	/// 敵の被弾時の処理
	/// </summary>
	/// <param name="damage"></param>
	void hit(int damage);

	/// <summary>
	/// 攻撃処理
	/// </summary>
	void attack();

	/// <summary>
	/// 移動処理
	/// 画面下に向かってまっすぐすすむ
	/// </summary>
	void move();
};

