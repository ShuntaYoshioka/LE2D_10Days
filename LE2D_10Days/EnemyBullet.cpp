#include "EnemyBullet.h"

EnemyBullet::EnemyBullet() {
    pos = { 0.0f, 0.0f };
    radius = 5.0f;
    velocity = { 0.0f, 10.0f };
    isShot = false;
}

void EnemyBullet::Shoot(const Vector2& startPos) {
    pos = startPos;
    isShot = true;
}

void EnemyBullet::Update() {
    if (!isShot) return;

    pos.x += velocity.x;
    pos.y += velocity.y;

    // 画面外に出たら消す
    if (pos.y - radius > 720) {
        isShot = false;
    }
}

void EnemyBullet::Draw() const {
    if (!isShot) return;
    Novice::DrawBox(
        static_cast<int>(pos.x - radius),
        static_cast<int>(pos.y - radius),
        static_cast<int>(radius * 2),
        static_cast<int>(radius * 2),
        0.0f,
        RED
		, kFillModeSolid
    );
}
