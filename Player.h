#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include <tnl_vector.h>

class Player {
private:
	//自機のデータ
	int player_gpc_hdl_ = 0;
	int hp_ = 100;
	int speed_ = 10;
	bool isDeath_ = false;
	tnl::Vector3 current_player_pos_ = { 650, 550, 0 };
	
public:
	/// <summary>
	/// プレイヤーのコンストラクタ
	/// </summary>
	/// <param name="hp">HP</param>
	/// <param name="speed">Speed</param>
	/// <param name="pos">ポジション</param>
	Player(int hp, int speed, tnl::Vector3 pos) {
		hp_ = hp;
		speed_ = speed;
		current_player_pos_ = pos;
	}

	void setPlayerGpcHdl() {
		player_gpc_hdl_ = LoadGraph("graphics/Player.png");
	}

	int getPlayerGpcHdl() {
		return player_gpc_hdl_;
	}

	tnl::Vector3 getPos() {
		return current_player_pos_;
	}

	bool getPlayerStatus() {
		return isDeath_;
	}

	/// <summary>
	/// プレイヤーの位置を設定する
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void setPos(float x, float y);

	/// <summary>
	/// 左右に移動する為の関数
	/// </summary>
	/// <param name="isRight">右に移動するか</param>
	void move(bool isRight);

	/// <summary>
	/// 射撃用の関数
	/// </summary>
	void fire();

	/// <summary>
	/// 被弾時の処理
	/// </summary>
	void Hit(int damage);
};
