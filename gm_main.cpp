#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

//�O���̕Ǘp�̒l
RECT rect;
const tnl::Vector3 OUTER_BOX_POS = {650, 350, 0};
const tnl::Vector3 OUTER_BOX_SIZE = {900, 750, 0};

//�w�i�̏��
int BACK_GROUND_GPC_HUNDLE[] = {0, 0};
tnl::Vector3 back_ground_offset = { 200, 0, 0 };

//Player�̈ړ��I�t�Z�b�g
const float RIGHT_OFFSET = 110;
const float LEFT_OFFSET = 10;
const float NOZLE_OFFSET = 30;

//�e�̃T�C�Y
const float BULLET_SIZE_Y = 30;

Player player;
Enemy enemy;
Bullet bullet;

//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart(){
	srand(time(0));

	//���܂��^�񒆂����Ȃ�����
	//GetClientRect(GetMainWindowHandle(), &rect);
	
	//�摜���[�h����
	player.player_gpc_hdl_ = LoadGraph("graphics/Player.png");
	enemy.enemy_gpc_hdl_ = LoadGraph("graphics/Enemy.bmp");
	bullet.bullet_gpc_hdl_ = LoadGraph("graphics/red1.bmp");

	for (int i = 0; i < sizeof(BACK_GROUND_GPC_HUNDLE) / sizeof(BACK_GROUND_GPC_HUNDLE[0]); i++)
	{
		BACK_GROUND_GPC_HUNDLE[i] = LoadGraph("graphics/space_star.png");
	}
}

/// <summary>
/// ��ʂ̃I�u�W�F�N�g�̈ʒu���m�F��
/// �ʒu�ɉ����ď��������s
/// </summary>
void CheckPos()
{
	//Player�̈ʒu�C��
	if (player.current_player_pos_.x > OUTER_BOX_POS.x + OUTER_BOX_SIZE.x / 2 - RIGHT_OFFSET) {
		player.current_player_pos_.x = OUTER_BOX_POS.x + OUTER_BOX_SIZE.x / 2 - RIGHT_OFFSET;
	}
	if (player.current_player_pos_.x < OUTER_BOX_POS.x - OUTER_BOX_SIZE.x / 2 + LEFT_OFFSET) {
		player.current_player_pos_.x = OUTER_BOX_POS.x - OUTER_BOX_SIZE.x / 2 + LEFT_OFFSET;
	}

	//�e����ʊO�ɏo����
	if (bullet.pos_.y < - BULLET_SIZE_Y)
	{
		bullet.current_bullet_state_ = Bullet::WAITING;
	}

	//�w�i�摜�̗���鏈��
	back_ground_offset.y += 10;

	if (back_ground_offset.y > OUTER_BOX_SIZE.y)
	{
		back_ground_offset.y = 0;
	}
}

/// <summary>
/// ��ʂɃI�u�W�F�N�g��\������֐�
/// �\�����鏈�����܂Ƃ߂Ă���
/// </summary>
void DrawOBJ()
{
	//�w�i�̕`�揈��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawRectGraph(back_ground_offset.x, back_ground_offset.y,0, 0, OUTER_BOX_SIZE.x, OUTER_BOX_SIZE.y, BACK_GROUND_GPC_HUNDLE[0], false, false);
	DrawRectGraph(back_ground_offset.x, back_ground_offset.y - OUTER_BOX_SIZE.y,0, 0, OUTER_BOX_SIZE.x, OUTER_BOX_SIZE.y, BACK_GROUND_GPC_HUNDLE[1], false, false);

	//�e�̕`��
	DrawGraph(bullet.pos_.x + NOZLE_OFFSET, bullet.pos_.y, bullet.bullet_gpc_hdl_, false);
	
	//�O�g��\������
	DrawBoxEx(OUTER_BOX_POS, OUTER_BOX_SIZE.x, OUTER_BOX_SIZE.y, false, -1);

	//�G�`�揈��
	DrawGraph(enemy.pos_.x, enemy.pos_.y, enemy.enemy_gpc_hdl_, false);

	//Player�`�揈��
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	DrawGraph(player.current_player_pos_.x, player.current_player_pos_.y, player.player_gpc_hdl_, false);
}

/// <summary>
/// �v���C���[�̓��͏���
/// </summary>
void Input()
{
	//player�̈ړ�����
	if (tnl::Input::IsKeyDown(eKeys::KB_LEFT)) player.current_player_pos_.x -= player.speed_;
	if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT)) player.current_player_pos_.x += player.speed_;

	//�ˌ�����
	if (tnl::Input::IsKeyDown(eKeys::KB_SPACE) && bullet.current_bullet_state_ == Bullet::WAITING) {
		bullet.pos_ = player.current_player_pos_;
		bullet.current_bullet_state_ = Bullet::FLYING;
	}
}


//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {

	//�G�ړ�����
	enemy.pos_.y += enemy.speed_;

	//�e�ړ�����
	if (bullet.current_bullet_state_ == Bullet::FLYING) bullet.pos_.y -= bullet.speed_;

	Input();

	CheckPos();
	
	DrawOBJ();
}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {
	
}
