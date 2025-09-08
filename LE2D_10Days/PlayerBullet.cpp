#include "PlayerBullet.h"
#include <Novice.h>

PlayerBullet::PlayerBullet() {
    Initialize();
}

void PlayerBullet::Initialize()
{
    isShot = false;
    pos = { 0, 0 };
    velocity = { 0, -10 };
    radius = 5;
}


void PlayerBullet::Shoot(const Vector2& startPos) {
    if (!isShot) {
        isShot = true;
        pos = startPos;
    }
}

void PlayerBullet::Update() {
    if (isShot) {
        pos.x += velocity.x;
        pos.y += velocity.y;
        if (pos.y < 0) isShot = false;
    }
}

void PlayerBullet::Draw()  {
    if (isShot) {
        Novice::DrawBox((int)(pos.x - radius), (int)(pos.y - radius),
            (int)(radius * 2), (int)(radius * 2),0.0f,
            BLUE, kFillModeSolid);
    }
}
