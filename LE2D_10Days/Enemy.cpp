#include "Enemy.h"
#include <Novice.h>
#include <cmath>
#include <cstdlib>

Enemy::Enemy() {
    pos = { 640.0f, 100.0f };
    radius = 20.0f;
    speed = { 9.0f, 0.0f };
    dodgeCooldown = 0;
}

void Enemy::Move(int windowLeft, int windowRight, const Vector2& playerPos, const PlayerBullet* bullets, int bulletCount) {
    if (dodgeCooldown > 0) {
        dodgeCooldown--; // クールタイム経過
    }

    // 一番近い弾を探す
    float nearestDistance = 99999.0f;//
    Vector2 nearestBulletPos = { -1000.0f, -1000.0f };//とりあえずでかい値　後でまとめる
    int foundBullet = false;

    for (int i = 0; i < bulletCount; i++) {
        if (!bullets[i].IsShot()) continue;

        float dx = bullets[i].GetPos().x - pos.x;
        float dy = bullets[i].GetPos().y - pos.y;
        float dist = dx * dx + dy * dy;

        if (dist < nearestDistance) {
            nearestDistance = dist;
            nearestBulletPos = bullets[i].GetPos();
            foundBullet = true;
        }
    }

    //ら回避
    if (foundBullet && dodgeCooldown <= 0) {
        if (nearestBulletPos.x > pos.x) {
            pos.x -= speed.x * 2.0f; 
        } else {
            pos.x += speed.x * 2.0f;
        }
        dodgeCooldown = 60; 
    }

    // プレイヤーを追いかける処理
    if (playerPos.x > pos.x) {
        pos.x += speed.x;
    } else if (playerPos.x < pos.x) {
        pos.x -= speed.x;
    }

    // 画面外に出ないように制限
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
