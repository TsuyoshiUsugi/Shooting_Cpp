#pragma once
#include "../dxlib_ext/dxlib_ext.h"

using namespace tnl;

class Player {
private:
	//���@�̃f�[�^
	int player_gpc_hdl_ = 0;
	int hp_ = 100;
	int speed_ = 10;
	tnl::Vector3 current_player_pos_ = { 650, 550, 0 };
	

public:
	/// <summary>
	/// �v���C���[�̃R���X�g���N�^
	/// </summary>
	/// <param name="gpcHdl">�摜</param>
	/// <param name="hp">HP</param>
	/// <param name="speed">Speed</param>
	/// <param name="pos">�|�W�V����</param>
	Player(int gpcHdl, int hp, int speed, tnl::Vector3 pos) {
		player_gpc_hdl_ = gpcHdl;
		hp_ = hp;
		speed_ = speed;
		current_player_pos_ = pos;
	}

	public Vector3 getPos() {

	}

	/// <summary>
	/// �ʒu��ݒ肷��
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void setPos(float x, float y) {
		current_player_pos_.x = x;
		current_player_pos_.y = y;
	}


	/// <summary>
	/// �ˌ��p�̊֐�
	/// </summary>
	void fire();
};
