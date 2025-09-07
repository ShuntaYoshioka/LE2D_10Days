#include "Line.h"
#include <Novice.h>

Line::Line() {
    pos = { 0, 350 };
    width = 1280;
    height = 20;

    moveAmountPlayer = 20.0f;
    moveAmountEnemy = 20.0f;

    LineTexture_ = Novice::LoadTexture("Resource/Line/WarningColor.png");
}

// Playerが被弾したら線を下に移動
void Line::LinePlayerHit() {
    pos.y += moveAmountPlayer;
}

// Enemyが被弾したら上に線を移動
void Line::LineEnemyHit() {
    pos.y -= moveAmountEnemy;
}



void Line::Draw()  {
    Novice::DrawSprite(
        static_cast<int>(pos.x),
        static_cast<int>(pos.y),
        LineTexture_,
        1.0f, 1.0f, 0.0f, WHITE);
}

bool Line::CheckHitPlayer(const Player& player) {
    // プレイヤーの中心とLineの矩形との交差判定
    float top = pos.y;
    float bottom = pos.y + height;
    float playerTop = player.GetPos().y - player.GetRadius();
    float playerBottom = player.GetPos().y + player.GetRadius();

    // y方向で重なっているかチェック
    if (playerBottom >= top && playerTop <= bottom) {
        return true;
    }
    return false;
}

bool Line::CheckHitEnemy(const Enemy& enemy) {
    float top = pos.y;
    float bottom = pos.y + height;
    float enemyTop = enemy.GetPos().y - enemy.GetRadius();
    float enemyBottom = enemy.GetPos().y + enemy.GetRadius();

    if (enemyBottom >= top && enemyTop <= bottom) {
        return true;
    }
    return false;
}

