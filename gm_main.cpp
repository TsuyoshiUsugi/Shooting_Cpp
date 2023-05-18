#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "Player.h"

//外側の壁用の値
RECT rect;
const tnl::Vector3 outer_box_pos = {650, 350, 0};
const tnl::Vector3 outer_box_size = {900, 650, 0};

Player player;

//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart(){
	srand(time(0));

	//うまく真ん中が取れなかった
	//GetClientRect(GetMainWindowHandle(), &rect);
	
	player.player_gpc_hdl_ = LoadGraph("graphics/Player.png");

}

//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time) {
	//外枠を表示する
	DrawBoxEx(outer_box_pos, outer_box_size.x, outer_box_size.y, false, -1);
	
	DrawGraph(outer_box_pos.x, outer_box_pos.y, player.player_gpc_hdl_, false);
}

//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {
	
}
