#include "Item.h"
#include "PlayerBullet.h"
#include "Enemy.h"
#include <cmath>
#include <cstdlib>

// 静的メンバ初期化
int Item::textureDoubleAttack = 0;
int Item::textureFollowBullet = 0;

Item::Item(Type type) : type(type) {
    Initialize();
    LoadTexture();
}

void Item::Initialize() {
    pos = { 0.0f, 0.0f };
    speed = { 0.0f, 1.0f };
    radius = 20.0f;
    isAppear = true;
    isGet = false;
    timeLimit = 1200;
}

void Item::LoadTexture() {
    if (textureDoubleAttack == 0) {
        textureDoubleAttack = Novice::LoadTexture("Resource/Items/doubleAttack.png");
    }
    if (textureFollowBullet == 0) {
        textureFollowBullet = Novice::LoadTexture("Resource/Items/follow.png");
    }
}

void Item::Update() {
    if (!isAppear) return;

    pos.x += speed.x;
    pos.y += speed.y;

    if (isGet) {
        timeLimit--;
        if (timeLimit <= 0) {
            isGet = false;
            timeLimit = 1200;
        }
    }
}

void Item::Draw() const {
    if (!isAppear) return;

    int tex = (type == Type::DoubleAttack) ? textureDoubleAttack : textureFollowBullet;
    Novice::DrawSprite(static_cast<int>(pos.x), static_cast<int>(pos.y), tex, 1, 1, 0.0f, 0xFFFFFFFF);
}

void Item::CheckGet(PlayerBullet* bullets, int bulletCount) {
    if (!isAppear) return;

    for (int i = 0; i < bulletCount; i++) {
        if (!bullets[i].IsShot()) continue;

        Vector2 bPos = bullets[i].GetPos();
        float dx = bPos.x - pos.x;
        float dy = bPos.y - pos.y;
        float dist2 = dx * dx + dy * dy;
        float rSum = bullets[i].GetRadius() + radius;
        if (dist2 <= rSum * rSum) {
            isGet = true;
            isAppear = false;
            bullets[i].SetShot(false);
        }
    }
}

void Item::FollowBullet(PlayerBullet& bullet, const Enemy& enemy) const {
    Vector2 dir = { enemy.GetPos().x - bullet.GetPos().x,
                    enemy.GetPos().y - bullet.GetPos().y };
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len != 0) {
        dir.x /= len;
        dir.y /= len;
    }
    Vector2 newPos = bullet.GetPos();
    newPos.x += dir.x * bullet.GetRadius(); // bullet speedに応じて調整可
    newPos.y += dir.y * bullet.GetRadius();
    bullet.Shoot(newPos);
}
