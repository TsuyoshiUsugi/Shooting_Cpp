#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Player {
public:
	//���@�̃f�[�^
	int player_gpc_hdl_ = 0;
	int hp_ = 100;
	tnl::Vector3 current_player_pos_ = { 650, 600, 0 };

	/// <summary>
	/// �������֐�
	/// </summary>
	void initialize(int gpc, int hp);

	/// <summary>
	/// �ˌ��p�̊֐�
	/// </summary>
	void fire();
};
