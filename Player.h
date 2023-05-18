#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Player {
public:
	//自機のデータ
	int player_gpc_hdl_ = 0;
	int hp_ = 100;
	tnl::Vector3 current_player_pos_ = { 650, 600, 0 };

	/// <summary>
	/// 初期化関数
	/// </summary>
	void initialize(int gpc, int hp);

	/// <summary>
	/// 射撃用の関数
	/// </summary>
	void fire();
};
