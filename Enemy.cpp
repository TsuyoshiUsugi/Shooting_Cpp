#include "Enemy.h"

/// <summary>
/// 移動処理
/// 画面したに向かってまっすぐすすむ
/// </summary>
void Enemy::move()
{
	pos_.y += speed_;
}

