#include <time.h>
#include <string>
#include <vector>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "CollisionDetect.h"
#include <iostream>

//�O���̕Ǘp�̒l
RECT rect;
const tnl::Vector3 OUTER_BOX_POS = {650, 350, 0};
const tnl::Vector3 OUTER_BOX_SIZE = {900, 750, 0};

//�w�i�̏��
int back_ground_gpc_hundle[] = {0, 0};
int back_ground_speed = 10;
tnl::Vector3 back_ground_offset = { 200, 0, 0 };

//�Q�[���S�̂̏��
int score = 0;
float score_pos_x = 1150;
float score_pos_y = 0;

//Player�̈ړ��I�t�Z�b�g
const float RIGHT_OFFSET = 110;
const float LEFT_OFFSET = 10;
const float NOZLE_OFFSET = 30;

//�e�̃T�C�Y
const float BULLET_SIZE_Y = 30;

tnl::Vector3 player_origin_pos = tnl::Vector3(650, 550, 0);
Player player = Player(3, 4, player_origin_pos);
Enemy enemy = Enemy(1, 1, tnl::Vector3(500, 0, 0));
Bullet bullet = Bullet(1, 1);

//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart(){
	srand(time(0));
	
	//�摜���[�h����
	player.setPlayerGpcHdl();
	enemy.setGpcHdl();
	bullet.SetGpcHdl();

	for (int i = 0; i < sizeof(back_ground_gpc_hundle) / sizeof(back_ground_gpc_hundle[0]); i++)
	{
		back_ground_gpc_hundle[i] = LoadGraph("graphics/space_star.png");
	}
}

/// <summary>
/// ��ʂ̃I�u�W�F�N�g�̈ʒu���m�F��
/// �ʒu�ɉ����ď��������s
/// </summary>
void CheckPos()
{
	//Player�̈ʒu�C��
	if (player.getPos().x > OUTER_BOX_POS.x + OUTER_BOX_SIZE.x / 2 - RIGHT_OFFSET) {
		player.setPos(OUTER_BOX_POS.x + OUTER_BOX_SIZE.x / 2 - RIGHT_OFFSET, player.getPos().y);
	}
	if (player.getPos().x < OUTER_BOX_POS.x - OUTER_BOX_SIZE.x / 2 + LEFT_OFFSET) {
		player.setPos(OUTER_BOX_POS.x - OUTER_BOX_SIZE.x / 2 + LEFT_OFFSET, player.getPos().y);
	}

	//�e����ʊO�ɏo����
	if (bullet.getPos().y < -BULLET_SIZE_Y)
	{
		bullet.SwitchState(BulletState::WAITING);
	}

	//�w�i�摜�̗���鏈��
	back_ground_offset.y += back_ground_speed;
	if (back_ground_offset.y > OUTER_BOX_SIZE.y) back_ground_offset.y = 0;
	
}

/// <summary>
/// ��ʂɃI�u�W�F�N�g��\������֐�
/// �\�����鏈�����܂Ƃ߂Ă���
/// </summary>
void DrawOBJ()
{
	//�w�i�̕`�揈��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawRectGraph(back_ground_offset.x, back_ground_offset.y,0, 0, OUTER_BOX_SIZE.x, OUTER_BOX_SIZE.y, back_ground_gpc_hundle[0], false, false);
	DrawRectGraph(back_ground_offset.x, back_ground_offset.y - OUTER_BOX_SIZE.y,0, 0, OUTER_BOX_SIZE.x, OUTER_BOX_SIZE.y, back_ground_gpc_hundle[1], false, false);

	//�X�R�A�̕\��
	DrawStringEx(score_pos_x, score_pos_y, -1, "score : %d", score);

	//�e�̕`��
	DrawGraph(bullet.getPos().x, bullet.getPos().y, bullet.getGpcHdl(), false);
	
	//�O�g��\������
	DrawBoxEx(OUTER_BOX_POS, OUTER_BOX_SIZE.x, OUTER_BOX_SIZE.y, false, -1);

	//�G�`�揈��
	DrawGraph(enemy.getPos().x, enemy.getPos().y, enemy.getGpcHdl(), false);

	//Player�`�揈��
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	DrawGraph(player.getPos().x, player.getPos().y, player.getPlayerGpcHdl(), false);
}

/// <summary>
/// �v���C���[�̓��͏���
/// </summary>
void Input()
{
	//player�̈ړ�����
	if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT)) player.move(true);
	if (tnl::Input::IsKeyDown(eKeys::KB_LEFT)) player.move(false);

	//�ˌ�����
	if (tnl::Input::IsKeyDown(eKeys::KB_SPACE) && bullet.currentState() == BulletState::WAITING) {
		auto shotPos = tnl::Vector3(player.getPos().x + NOZLE_OFFSET, player.getPos().y, 0);
		bullet.setPos(shotPos);
		bullet.SwitchState(BulletState::FLYING);
	}
}

/// <summary>
/// �Փ˔�����s��
/// ���ꂼ��̒��S�_�̍��W���擾���A���̍��̐�Βl���e�}�`�̏c���̘a�͈͓̔��Ȃ瓖����
/// </summary>
void Hit()
{
	//�G�̏��
	int enemy_size_x = 0;
	int enemy_size_y = 0;
	GetGraphSize(enemy.getGpcHdl(), &enemy_size_x, &enemy_size_y);
	tnl::Vector3 enemy_center_pos = {enemy.getPos().x + static_cast<float>(enemy_size_x) / 2, enemy.getPos().y + static_cast<float>(enemy_size_y) / 2, 0};

	//�e�̏��
	int bullet_size_x = 0;
	int bullet_size_y = 0;
	GetGraphSize(bullet.getGpcHdl(), &bullet_size_x, &bullet_size_y);
	tnl::Vector3 bullet_center_pos = {bullet.getPos().x + static_cast<float>(bullet_size_x) / 2, bullet.getPos().y + static_cast<float>(bullet_size_y) / 2, 0};

	auto xDiff = std::abs(enemy_center_pos.x - bullet_center_pos.x);
	auto yDiff = std::abs(enemy_center_pos.y - bullet_center_pos.y);

	if (yDiff < enemy_size_y / 2 + bullet_size_y / 2 &&
	xDiff < enemy_size_x / 2 + bullet_size_x / 2) {
		enemy.hit(bullet.getBulletDamage());
		score++;
	}
	
}

//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {

	//�G�ړ�����
	enemy.move();

	//�e�ړ�����
	if (bullet.currentState() == BulletState::FLYING) bullet.move();

	Input();

	CheckPos();
	
	Hit();

	DrawOBJ();
}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {
	
}
