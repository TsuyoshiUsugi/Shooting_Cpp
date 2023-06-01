#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

//外側の壁用の値
RECT rect;
const tnl::Vector3 OUTER_BOX_POS = {650, 350, 0};
const tnl::Vector3 OUTER_BOX_SIZE = {900, 750, 0};

//背景の情報
int BACK_GROUND_GPC_HUNDLE[] = {0, 0};
tnl::Vector3 back_ground_offset = { 200, 0, 0 };

//Playerの移動オフセット
const float RIGHT_OFFSET = 110;
const float LEFT_OFFSET = 10;
const float NOZLE_OFFSET = 30;

//弾のサイズ
const float BULLET_SIZE_Y = 30;

Player player;
Enemy enemy;
Bullet bullet;

//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart(){
	srand(time(0));

	//うまく真ん中が取れなかった
	//GetClientRect(GetMainWindowHandle(), &rect);
	
	//画像ロード処理
	player.player_gpc_hdl_ = LoadGraph("graphics/Player.png");
	enemy.enemy_gpc_hdl_ = LoadGraph("graphics/Enemy.bmp");
	bullet.bullet_gpc_hdl_ = LoadGraph("graphics/red1.bmp");

	for (int i = 0; i < sizeof(BACK_GROUND_GPC_HUNDLE) / sizeof(BACK_GROUND_GPC_HUNDLE[0]); i++)
	{
		BACK_GROUND_GPC_HUNDLE[i] = LoadGraph("graphics/space_star.png");
	}
}

/// <summary>
/// 画面のオブジェクトの位置を確認し
/// 位置に応じて処理を実行
/// </summary>
void CheckPos()
{
	//Playerの位置修正
	if (player.current_player_pos_.x > OUTER_BOX_POS.x + OUTER_BOX_SIZE.x / 2 - RIGHT_OFFSET) {
		player.current_player_pos_.x = OUTER_BOX_POS.x + OUTER_BOX_SIZE.x / 2 - RIGHT_OFFSET;
	}
	if (player.current_player_pos_.x < OUTER_BOX_POS.x - OUTER_BOX_SIZE.x / 2 + LEFT_OFFSET) {
		player.current_player_pos_.x = OUTER_BOX_POS.x - OUTER_BOX_SIZE.x / 2 + LEFT_OFFSET;
	}

	//弾が画面外に出たら
	if (bullet.pos_.y < - BULLET_SIZE_Y)
	{
		bullet.current_bullet_state_ = Bullet::WAITING;
	}

	//背景画像の流れる処理
	back_ground_offset.y += 10;

	if (back_ground_offset.y > OUTER_BOX_SIZE.y)
	{
		back_ground_offset.y = 0;
	}
}

/// <summary>
/// 画面にオブジェクトを表示する関数
/// 表示する処理をまとめている
/// </summary>
void DrawOBJ()
{
	//背景の描画処理
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawRectGraph(back_ground_offset.x, back_ground_offset.y,0, 0, OUTER_BOX_SIZE.x, OUTER_BOX_SIZE.y, BACK_GROUND_GPC_HUNDLE[0], false, false);
	DrawRectGraph(back_ground_offset.x, back_ground_offset.y - OUTER_BOX_SIZE.y,0, 0, OUTER_BOX_SIZE.x, OUTER_BOX_SIZE.y, BACK_GROUND_GPC_HUNDLE[1], false, false);

	//弾の描写
	DrawGraph(bullet.pos_.x + NOZLE_OFFSET, bullet.pos_.y, bullet.bullet_gpc_hdl_, false);
	
	//外枠を表示する
	DrawBoxEx(OUTER_BOX_POS, OUTER_BOX_SIZE.x, OUTER_BOX_SIZE.y, false, -1);

	//敵描画処理
	DrawGraph(enemy.pos_.x, enemy.pos_.y, enemy.enemy_gpc_hdl_, false);

	//Player描画処理
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	DrawGraph(player.current_player_pos_.x, player.current_player_pos_.y, player.player_gpc_hdl_, false);
}

/// <summary>
/// プレイヤーの入力処理
/// </summary>
void Input()
{
	//playerの移動処理
	if (tnl::Input::IsKeyDown(eKeys::KB_LEFT)) player.current_player_pos_.x -= player.speed_;
	if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT)) player.current_player_pos_.x += player.speed_;

	//射撃処理
	if (tnl::Input::IsKeyDown(eKeys::KB_SPACE) && bullet.current_bullet_state_ == Bullet::WAITING) {
		bullet.pos_ = player.current_player_pos_;
		bullet.current_bullet_state_ = Bullet::FLYING;
	}
}


//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time) {

	//敵移動処理
	enemy.pos_.y += enemy.speed_;

	//弾移動処理
	if (bullet.current_bullet_state_ == Bullet::FLYING) bullet.pos_.y -= bullet.speed_;

	Input();

	CheckPos();
	
	DrawOBJ();
}

//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {
	
}
