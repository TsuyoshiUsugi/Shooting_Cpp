#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "Player.h"
#include "Enemy.h"

//�O���̕Ǘp�̒l
RECT rect;
const tnl::Vector3 outer_box_pos = {650, 350, 0};
const tnl::Vector3 outer_box_size = {900, 700, 0};

//player�̐ݒ�
Player player;
Enemy enemy;

//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart(){
	srand(time(0));

	//���܂��^�񒆂����Ȃ�����
	//GetClientRect(GetMainWindowHandle(), &rect);
	
	player.player_gpc_hdl_ = LoadGraph("graphics/Player.png");
	enemy.enemy_gpc_hdl_ = LoadGraph("graphics/Enemy.bmp");
}

void checkPos()
{

}

//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {
	//�O�g��\������
	enemy.pos_.y += enemy.speed_;
	DrawBoxEx(outer_box_pos, outer_box_size.x, outer_box_size.y, false, -1);

	//�G�ړ�����
	DrawGraph(enemy.pos_.x, enemy.pos_.y, enemy.enemy_gpc_hdl_, false);

	//player�̈ړ�����
	if (tnl::Input::IsKeyDown(eKeys::KB_LEFT)) player.current_player_pos_.x -= player.speed_;
	if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT)) player.current_player_pos_.x += player.speed_;
	if (player.current_player_pos_.x > outer_box_pos.x + outer_box_size.x / 2 - 110) {
		player.current_player_pos_.x = outer_box_pos.x + outer_box_size.x / 2 - 110;
	}
	if (player.current_player_pos_.x < outer_box_pos.x - outer_box_size.x / 2 + 10) {
		player.current_player_pos_.x = outer_box_pos.x - outer_box_size.x / 2 + 10;
	}
	DrawGraph(player.current_player_pos_.x, player.current_player_pos_.y, player.player_gpc_hdl_, false);
}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {
	
}
