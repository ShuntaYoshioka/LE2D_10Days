#include "Enemy.h"
#include <Novice.h>

Enemy::Enemy() {
    pos = { 640.0f, 100.0f };
    radius = 20.0f;
    speed = { 5.0f, 0.0f };
}

void Enemy::Move(int windowLeft, int windowRight, const Vector2& playerPos) {
 

    if (playerPos.x > pos.x) {
        pos.x += speed.x;
    } else if (playerPos.x < pos.x) {
        pos.x -= speed.x;
    }

    // ウィンドウ端で反転
    if (pos.x - radius < windowLeft) {
        pos.x = windowLeft + radius;
    } else if (pos.x + radius > windowRight) {
        pos.x = windowRight - radius;
    }

   
}

void Enemy::Draw() const {
    Novice::DrawBox(
        static_cast<int>(pos.x - radius),
        static_cast<int>(pos.y - radius),
        static_cast<int>(radius * 2),
        static_cast<int>(radius * 2),
        0.0f,
        RED,
		kFillModeSolid
    );
}
