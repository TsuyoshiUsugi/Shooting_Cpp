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
tnl::Vector3 score_pos = tnl::Vector3(1125, 25, 0);
int game_frame_timer = 0;
tnl::Vector3 timer_pos = tnl::Vector3(1125, 0, 0);
int enemy_count = 0;
tnl::Vector3 hp_pos = tnl::Vector3(1125, 50, 0);

//Player�̈ړ��I�t�Z�b�g
const float RIGHT_OFFSET = 110;
const float LEFT_OFFSET = 10;
const float NOZLE_OFFSET = 30;

//�e�̃T�C�Y
const float BULLET_SIZE_Y = 30;

tnl::Vector3 player_origin_pos = tnl::Vector3(650, 550, 0);
Player player = Player(3, 4, player_origin_pos);
Bullet bullet = Bullet(1, 1);
std::vector<Enemy> enemies;

//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart(){
	srand(time(0));
	
	//�摜���[�h����
	player.setPlayerGpcHdl();

	initializeEnemy();

	bullet.SetGpcHdl();

	for (int i = 0; i < sizeof(back_ground_gpc_hundle) / sizeof(back_ground_gpc_hundle[0]); i++)
	{
		back_ground_gpc_hundle[i] = LoadGraph("graphics/space_star.png");
	}
}

/// <summary>
/// �G�̏���������
/// vector�Ɋi�[���ĉ摜��ݒ肷��
/// </summary>
void initializeEnemy()
{
	enemies.push_back(Enemy(1, 1, tnl::Vector3(250, 0, 0)));
	enemies[0].setGpcHdl();
	enemy_count++;
}

//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {

	game_frame_timer++;

	GenerateEnemy();

	MovePos();

	Input();

	CheckPos();
	
	CheckHit();

	DrawObj();	//�Ō�ɍs������
}

/// <summary>
/// �G�𐶐�����
/// </summary>
void GenerateEnemy()
{
	if (game_frame_timer % 60 * 2 == 0) { //�ܕb�����ɓG�𐶐�����B���ƂŃ}�W�b�N�i���o�[��ς��邱��
		auto pos = enemy_count % 6 * 150;	//6���[�����Ƃɐ���
		enemies.push_back(Enemy(1, 1, tnl::Vector3(250 + pos, 0, 0)));
		enemies[enemies.size() - 1].setGpcHdl();
		enemy_count++;
	}
}

/// <summary>
/// �I�u�W�F�N�g�̈ړ�����
/// </summary>
void MovePos()
{
	//�G�ړ�����
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i].move();
	}

	//�e�ړ�����
	if (bullet.currentState() == BulletState::FLYING) bullet.move();
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
/// �Փ˔�����s��
/// </summary>
void CheckHit()
{
	//�G�̉摜�T�C�Y���i�[����
	int enemy_size_x = 0;
	int enemy_size_y = 0;

	//�e�̉摜�T�C�Y���i�[����
	int bullet_size_x = 0;
	int bullet_size_y = 0;
	GetGraphSize(bullet.getGpcHdl(), &bullet_size_x, &bullet_size_y);
	auto bulletPos = bullet.getPos();
	auto bulletDamage = bullet.getBulletDamage();

	for (size_t i = 0; i < enemies.size(); i++)
	{
		GetGraphSize(enemies[i].getGpcHdl(), &enemy_size_x, &enemy_size_y);
		auto isHit = usl::rectAngleAndRectAngleHitDetect(enemies[i].getPos(), enemy_size_x, enemy_size_y,
			bulletPos, bullet_size_x, bullet_size_y);

		if (isHit) {
			enemies[i].hit(bulletDamage);
			score++;
		}
	}

	//�v���C���[�̉摜�T�C�Y���i�[����
	int player_size_x = 0;
	int player_size_y = 0;
	GetGraphSize(player.getPlayerGpcHdl(), &player_size_x, &player_size_y);
	auto playerPos = player.getPos();
	for (size_t i = 0; i < enemies.size(); i++)
	{
		GetGraphSize(enemies[i].getGpcHdl(), &enemy_size_x, &enemy_size_y);
		auto isHit = usl::rectAngleAndRectAngleHitDetect(enemies[i].getPos(), enemy_size_x, enemy_size_y,
			playerPos, player_size_x, player_size_y);

		if (isHit) {
			player.Hit(enemies[i].getEnemyDamage());
			enemies[i].hit(99999);		//�G���������鏈��
		}
	}
}

/// <summary>
/// ��ʂɃI�u�W�F�N�g��\������֐�
/// �\�����鏈�����܂Ƃ߂Ă���
/// </summary>
void DrawObj()
{
	SetFontSize(25);

	//�w�i�̕`�揈��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawRectGraph(back_ground_offset.x, back_ground_offset.y, 0, 0, OUTER_BOX_SIZE.x, OUTER_BOX_SIZE.y, back_ground_gpc_hundle[0], false, false);
	DrawRectGraph(back_ground_offset.x, back_ground_offset.y - OUTER_BOX_SIZE.y, 0, 0, OUTER_BOX_SIZE.x, OUTER_BOX_SIZE.y, back_ground_gpc_hundle[1], false, false);

	//�X�R�A�̕\��
	DrawStringEx(score_pos.x, score_pos.y, -1, "score : %d", score);

	//HP�̕\��
	DrawStringEx(hp_pos.x, hp_pos.y, -1, "Hp : %d", player.getPlayerHp());

	//�O�g��\������
	DrawBoxEx(OUTER_BOX_POS, OUTER_BOX_SIZE.x, OUTER_BOX_SIZE.y, false, -1);

	//�J�n���Ă���̎��Ԃ�\������
	DrawStringEx(timer_pos.x, timer_pos.y, -1, "Time : %d", game_frame_timer / 60);

	//�e�̕`��
	DrawGraph(bullet.getPos().x, bullet.getPos().y, bullet.getGpcHdl(), false);


	//�G�`�揈��
	for (size_t i = 0; i < enemies.size(); i++)
	{
		DrawGraph(enemies[i].getPos().x, enemies[i].getPos().y, enemies[i].getGpcHdl(), false);
	}

	//Player�`�揈��
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	DrawGraph(player.getPos().x, player.getPos().y, player.getPlayerGpcHdl(), false);
}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {
	
}
