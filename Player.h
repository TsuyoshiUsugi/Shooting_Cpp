#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include <tnl_vector.h>

class Player {
private:
	//���@�̃f�[�^
	int player_gpc_hdl_ = 0;
	int hp_ = 100;
	int speed_ = 10;
	bool isDeath_ = false;
	tnl::Vector3 current_player_pos_ = { 650, 550, 0 };
	
public:
	/// <summary>
	/// �v���C���[�̃R���X�g���N�^
	/// </summary>
	/// <param name="hp">HP</param>
	/// <param name="speed">Speed</param>
	/// <param name="pos">�|�W�V����</param>
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
	/// �v���C���[�̈ʒu��ݒ肷��
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void setPos(float x, float y);

	/// <summary>
	/// ���E�Ɉړ�����ׂ̊֐�
	/// </summary>
	/// <param name="isRight">�E�Ɉړ����邩</param>
	void move(bool isRight);

	/// <summary>
	/// �ˌ��p�̊֐�
	/// </summary>
	void fire();

	/// <summary>
	/// ��e���̏���
	/// </summary>
	void Hit(int damage);
};
