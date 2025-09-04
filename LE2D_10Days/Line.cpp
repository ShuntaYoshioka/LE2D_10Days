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
