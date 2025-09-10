#include "TrackingBullet.h"
#include <cmath>
#include "Itemtracking.h"

TrackingBullet::TrackingBullet() {
    Initialize();
    graphHandleBullet = Novice::LoadTexture("Resource/Player_Bullet/trackingBullet.png"); // 弾の見た目
}

void TrackingBullet::Initialize() {
    pos = { 0.0f, 0.0f };
    speed = 4.0f;
    radius = 16.0f;
    isShot = false;
}

void TrackingBullet::Shoot(const Vector2& startPos) {
    pos = startPos;
    isShot = true;
}

void TrackingBullet::Update(Enemy& enemy) {
    if (!isShot) return;

    Vector2 dir = { enemy.GetPos().x - pos.x, enemy.GetPos().y - pos.y };
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len != 0.0f) {
        dir.x /= len;
        dir.y /= len;
    }

    pos.x += dir.x * speed;
    pos.y += dir.y * speed;
}

void TrackingBullet::Draw() {
    if (isShot) {
        Novice::DrawSprite((int)(pos.x - radius), (int)(pos.y - radius), graphHandleBullet, 1.0f, 1.0f, 0.0f, WHITE);
    }
}
