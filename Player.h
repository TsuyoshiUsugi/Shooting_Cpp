#pragma once
#include "../dxlib_ext/dxlib_ext.h"

using namespace tnl;

class Player {
private:
	//自機のデータ
	int player_gpc_hdl_ = 0;
	int hp_ = 100;
	int speed_ = 10;
	tnl::Vector3 current_player_pos_ = { 650, 550, 0 };
	

public:
	/// <summary>
	/// プレイヤーのコンストラクタ
	/// </summary>
	/// <param name="gpcHdl">画像</param>
	/// <param name="hp">HP</param>
	/// <param name="speed">Speed</param>
	/// <param name="pos">ポジション</param>
	Player(int gpcHdl, int hp, int speed, tnl::Vector3 pos) {
		player_gpc_hdl_ = gpcHdl;
		hp_ = hp;
		speed_ = speed;
		current_player_pos_ = pos;
	}

	public Vector3 getPos() {

	}

	/// <summary>
	/// 位置を設定する
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void setPos(float x, float y) {
		current_player_pos_.x = x;
		current_player_pos_.y = y;
	}


	/// <summary>
	/// 射撃用の関数
	/// </summary>
	void fire();
};
