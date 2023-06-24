#include <time.h>
#include <string>
#include <vector>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "CollisionDetect.h"

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

tnl::Vector3 originPos = tnl::Vector3(650, 550, 0);
Player player = Player(3, 4, originPos);

Enemy enemy;
Bullet bullet;
std::vector<Enemy> enemies(2);

//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart(){
	srand(time(0));
	
	//�摜���[�h����
	player.setPlayerGpcHdl();
	enemy.enemy_gpc_hdl_ = LoadGraph("graphics/Enemy.bmp");
	bullet.bullet_gpc_hdl_ = LoadGraph("graphics/red1.bmp");

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
	if (bullet.pos_.y < - BULLET_SIZE_Y)
	{
		bullet.current_bullet_state_ = Bullet::WAITING;
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
	DrawGraph(bullet.pos_.x + NOZLE_OFFSET, bullet.pos_.y, bullet.bullet_gpc_hdl_, false);
	
	//�O�g��\������
	DrawBoxEx(OUTER_BOX_POS, OUTER_BOX_SIZE.x, OUTER_BOX_SIZE.y, false, -1);

	//�G�`�揈��
	DrawGraph(enemy.pos_.x, enemy.pos_.y, enemy.enemy_gpc_hdl_, false);

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
	if (tnl::Input::IsKeyDown(eKeys::KB_LEFT)) player.move(false);
	if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT)) player.move(true);

	//�ˌ�����
	if (tnl::Input::IsKeyDown(eKeys::KB_SPACE) && bullet.current_bullet_state_ == Bullet::WAITING) {
		bullet.pos_ = player.getPos();
		bullet.current_bullet_state_ = Bullet::FLYING;
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
	GetGraphSize(enemy.enemy_gpc_hdl_, &enemy_size_x, &enemy_size_y);
	tnl::Vector3 enemy_center_pos = {enemy.pos_.x + enemy_size_x / 2, enemy.pos_.y + enemy_size_y / 2, 0};

	//�e�̏��
	int bullet_size_x = 0;
	int bullet_size_y = 0;
	GetGraphSize(bullet.bullet_gpc_hdl_, &bullet_size_x, &bullet_size_y);
	tnl::Vector3 bullet_center_pos = {bullet.pos_.x + bullet_size_x / 2, bullet.pos_.y + bullet_size_y / 2, 0};

	if (std::abs(enemy_center_pos.x - bullet_center_pos.x) < enemy_size_x / 2 + bullet_size_x / 2)
	{
		if (std::abs(enemy_center_pos.y - bullet_center_pos.y) < enemy_size_y / 2 + bullet_size_y / 2)
		{
			enemy.enemy_gpc_hdl_ = 0;
			score++;
		}
	}
}

//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {

	//�G�ړ�����
	enemy.move();

	//�e�ړ�����
	if (bullet.current_bullet_state_ == Bullet::FLYING) bullet.pos_.y -= bullet.speed_;

	Input();

	CheckPos();
	
	Hit();

	DrawOBJ();
}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {
	
}
