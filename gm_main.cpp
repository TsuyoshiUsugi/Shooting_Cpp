#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "Player.h"

//�O���̕Ǘp�̒l
RECT rect;
const tnl::Vector3 outer_box_pos = {650, 350, 0};
const tnl::Vector3 outer_box_size = {900, 650, 0};

Player player;

//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart(){
	srand(time(0));

	//���܂��^�񒆂����Ȃ�����
	//GetClientRect(GetMainWindowHandle(), &rect);
	
	player.player_gpc_hdl_ = LoadGraph("graphics/Player.png");

}

//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {
	//�O�g��\������
	DrawBoxEx(outer_box_pos, outer_box_size.x, outer_box_size.y, false, -1);
	
	DrawGraph(outer_box_pos.x, outer_box_pos.y, player.player_gpc_hdl_, false);
}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {
	
}
