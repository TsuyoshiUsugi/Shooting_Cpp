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

//外側の壁用の値
RECT rect;
const tnl::Vector3 OUTER_BOX_POS = {650, 350, 0};
const tnl::Vector3 OUTER_BOX_SIZE = {900, 750, 0};

//背景の情報
int back_ground_gpc_hundle[] = {0, 0};
int back_ground_speed = 10;
tnl::Vector3 back_ground_offset = { 200, 0, 0 };

//ゲーム全体の情報
int score = 0;
float score_pos_x = 1150;
float score_pos_y = 0;

//Playerの移動オフセット
const float RIGHT_OFFSET = 110;
const float LEFT_OFFSET = 10;
const float NOZLE_OFFSET = 30;

//弾のサイズ
const float BULLET_SIZE_Y = 30;

tnl::Vector3 player_origin_pos = tnl::Vector3(650, 550, 0);
Player player = Player(3, 4, player_origin_pos);
Enemy enemy = Enemy(1, 1, tnl::Vector3(500, 0, 0));
Bullet bullet = Bullet(1, 1);

//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart(){
	srand(time(0));
	
	//画像ロード処理
	player.setPlayerGpcHdl();
	enemy.setGpcHdl();
	bullet.SetGpcHdl();

	for (int i = 0; i < sizeof(back_ground_gpc_hundle) / sizeof(back_ground_gpc_hundle[0]); i++)
	{
		back_ground_gpc_hundle[i] = LoadGraph("graphics/space_star.png");
	}
}

/// <summary>
/// 画面のオブジェクトの位置を確認し
/// 位置に応じて処理を実行
/// </summary>
void CheckPos()
{
	//Playerの位置修正
	if (player.getPos().x > OUTER_BOX_POS.x + OUTER_BOX_SIZE.x / 2 - RIGHT_OFFSET) {
		player.setPos(OUTER_BOX_POS.x + OUTER_BOX_SIZE.x / 2 - RIGHT_OFFSET, player.getPos().y);
	}
	if (player.getPos().x < OUTER_BOX_POS.x - OUTER_BOX_SIZE.x / 2 + LEFT_OFFSET) {
		player.setPos(OUTER_BOX_POS.x - OUTER_BOX_SIZE.x / 2 + LEFT_OFFSET, player.getPos().y);
	}

	//弾が画面外に出たら
	if (bullet.getPos().y < -BULLET_SIZE_Y)
	{
		bullet.SwitchState(BulletState::WAITING);
	}

	//背景画像の流れる処理
	back_ground_offset.y += back_ground_speed;
	if (back_ground_offset.y > OUTER_BOX_SIZE.y) back_ground_offset.y = 0;
	
}

/// <summary>
/// 画面にオブジェクトを表示する関数
/// 表示する処理をまとめている
/// </summary>
void DrawOBJ()
{
	//背景の描画処理
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawRectGraph(back_ground_offset.x, back_ground_offset.y,0, 0, OUTER_BOX_SIZE.x, OUTER_BOX_SIZE.y, back_ground_gpc_hundle[0], false, false);
	DrawRectGraph(back_ground_offset.x, back_ground_offset.y - OUTER_BOX_SIZE.y,0, 0, OUTER_BOX_SIZE.x, OUTER_BOX_SIZE.y, back_ground_gpc_hundle[1], false, false);

	//スコアの表示
	DrawStringEx(score_pos_x, score_pos_y, -1, "score : %d", score);

	//弾の描写
	DrawGraph(bullet.getPos().x, bullet.getPos().y, bullet.getGpcHdl(), false);
	
	//外枠を表示する
	DrawBoxEx(OUTER_BOX_POS, OUTER_BOX_SIZE.x, OUTER_BOX_SIZE.y, false, -1);

	//敵描画処理
	DrawGraph(enemy.getPos().x, enemy.getPos().y, enemy.getGpcHdl(), false);

	//Player描画処理
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	DrawGraph(player.getPos().x, player.getPos().y, player.getPlayerGpcHdl(), false);
}

/// <summary>
/// プレイヤーの入力処理
/// </summary>
void Input()
{
	//playerの移動処理
	if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT)) player.move(true);
	if (tnl::Input::IsKeyDown(eKeys::KB_LEFT)) player.move(false);

	//射撃処理
	if (tnl::Input::IsKeyDown(eKeys::KB_SPACE) && bullet.currentState() == BulletState::WAITING) {
		auto shotPos = tnl::Vector3(player.getPos().x + NOZLE_OFFSET, player.getPos().y, 0);
		bullet.setPos(shotPos);
		bullet.SwitchState(BulletState::FLYING);
	}
}

/// <summary>
/// 衝突判定を行う
/// それぞれの中心点の座標を取得し、その差の絶対値が各図形の縦横の和の範囲内なら当たり
/// </summary>
void Hit()
{
	//敵の情報
	int enemy_size_x = 0;
	int enemy_size_y = 0;
	GetGraphSize(enemy.getGpcHdl(), &enemy_size_x, &enemy_size_y);
	tnl::Vector3 enemy_center_pos = {enemy.getPos().x + static_cast<float>(enemy_size_x) / 2, enemy.getPos().y + static_cast<float>(enemy_size_y) / 2, 0};

	//弾の情報
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
// 毎フレーム実行されます
void gameMain(float delta_time) {

	//敵移動処理
	enemy.move();

	//弾移動処理
	if (bullet.currentState() == BulletState::FLYING) bullet.move();

	Input();

	CheckPos();
	
	Hit();

	DrawOBJ();
}

//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {
	
}
