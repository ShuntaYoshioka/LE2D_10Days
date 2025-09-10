#include "ItemTracking.h"
#include <cstdlib>

ItemTracking::ItemTracking() {
    Initialize();
    graphHandleItem = Novice::LoadTexture("Resource/Items/follow.png"); // アイテムの見た目
}

void ItemTracking::Initialize() {
    pos.x = static_cast<float>(rand() % 1280 + 40);
    pos.y = 0.0f;
    radius = 32.0f;
    speedY_ = 2.0f;
    isGet = false;
    isAppear = true;
    itemCooldown = 240.0f;
    respawnTimer = 0;
}

void ItemTracking::Move() {
    if (isAppear) {
        pos.y += speedY_;
        if (pos.y > 720) {
            isAppear = false;
            respawnTimer = 180; //3秒くらい待つ
        }
    }

    if (isGet) {
        itemCooldown--;
        if (itemCooldown <= 0) {
            isGet = false;
            respawnTimer = 180;
        }
    }

    if (!isAppear && !isGet && respawnTimer > 0) {
        respawnTimer--;
        if (respawnTimer <= 0) {
            Initialize();
        }
    }
}

void ItemTracking::Draw() {
    if (isAppear) {
        Novice::DrawSprite((int)(pos.x - radius), (int)(pos.y - radius), graphHandleItem, 1.0f, 1.0f, 0.0f, WHITE);
    }
}

void ItemTracking::CheckGet(PlayerBullet* bullets, int bulletCount) {
    if (!isAppear) return;

    for (int i = 0; i < bulletCount; i++) {
        if (bullets[i].IsShot()) {
            float dx = bullets[i].GetPos().x - pos.x;
            float dy = bullets[i].GetPos().y - pos.y;
            float distance = dx * dx + dy * dy;

            float rr = bullets[i].GetRadius() + radius;
            float rad = rr * rr;

            if (distance <= rad) {
                isGet = true;
                isAppear = false;
                itemCooldown = 240.0f;
                bullets[i].SetShot(false);
            }
        }
    }
}
