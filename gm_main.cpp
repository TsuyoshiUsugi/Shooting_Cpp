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
tnl::Vector3 score_pos = tnl::Vector3(1150, 0, 0);
int game_timer = 0;
tnl::Vector3 timer_pos = tnl::Vector3(1150, 100, 0);

//Playerの移動オフセット
const float RIGHT_OFFSET = 110;
const float LEFT_OFFSET = 10;
const float NOZLE_OFFSET = 30;

//弾のサイズ
const float BULLET_SIZE_Y = 30;

tnl::Vector3 player_origin_pos = tnl::Vector3(650, 550, 0);
Player player = Player(3, 4, player_origin_pos);
Bullet bullet = Bullet(1, 1);
std::vector<Enemy> enemies;

//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart(){
	srand(time(0));
	
	//画像ロード処理
	player.setPlayerGpcHdl();

	initializeEnemy();

	bullet.SetGpcHdl();

	for (int i = 0; i < sizeof(back_ground_gpc_hundle) / sizeof(back_ground_gpc_hundle[0]); i++)
	{
		back_ground_gpc_hundle[i] = LoadGraph("graphics/space_star.png");
	}
}

void initializeEnemy()
{
	for (size_t i = 0; i < 1; i++)
	{
		enemies.push_back(Enemy(1, 1, tnl::Vector3(550, 0, 0)));
	}

	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i].setGpcHdl();
	}
}

//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time) {

	//敵移動処理
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i].move();
	}

	//弾移動処理
	if (bullet.currentState() == BulletState::FLYING) bullet.move();

	Input();

	CheckPos();
	
	CheckHit();

	DrawObj();	//最後に行うこと
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

	//時間計測
	game_timer++;
}

/// <summary>
/// 衝突判定を行う
/// </summary>
void CheckHit()
{
	//敵の画像サイズを格納する
	int enemy_size_x = 0;
	int enemy_size_y = 0;

	//弾の画像サイズを格納する
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

}

/// <summary>
/// 画面にオブジェクトを表示する関数
/// 表示する処理をまとめている
/// </summary>
void DrawObj()
{
	//背景の描画処理
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawRectGraph(back_ground_offset.x, back_ground_offset.y, 0, 0, OUTER_BOX_SIZE.x, OUTER_BOX_SIZE.y, back_ground_gpc_hundle[0], false, false);
	DrawRectGraph(back_ground_offset.x, back_ground_offset.y - OUTER_BOX_SIZE.y, 0, 0, OUTER_BOX_SIZE.x, OUTER_BOX_SIZE.y, back_ground_gpc_hundle[1], false, false);

	//スコアの表示
	DrawStringEx(score_pos.x, score_pos.y, -1, "score : %d", score);

	//外枠を表示する
	DrawBoxEx(OUTER_BOX_POS, OUTER_BOX_SIZE.x, OUTER_BOX_SIZE.y, false, -1);

	//開始してからの時間を表示する
	DrawStringEx(timer_pos.x, timer_pos.y, -1, "Time : %d", game_timer / 60);

	//弾の描写
	DrawGraph(bullet.getPos().x, bullet.getPos().y, bullet.getGpcHdl(), false);


	//敵描画処理
	for (size_t i = 0; i < enemies.size(); i++)
	{
		DrawGraph(enemies[i].getPos().x, enemies[i].getPos().y, enemies[i].getGpcHdl(), false);
	}

	//Player描画処理
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	DrawGraph(player.getPos().x, player.getPos().y, player.getPlayerGpcHdl(), false);
}

//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {
	
}
