#pragma once
#include "PlayerBullet.h"
#include "Vector2.h"
#include <Novice.h>

class ItemTracking {
public:
    ItemTracking();

    void Initialize();
    void Move();                       // アイテム自体の落下などの動き
    void Draw();
    void CheckGet(PlayerBullet* bullets, int bulletCount);

    bool IsActiveGet() const { return isGet; }
    bool IsActiveAppear() const { return isAppear; }

private:
    Vector2 pos;
    float radius;
    float speedY_;
    bool isGet;
    bool isAppear;
    int respawnTimer;
    float itemCooldown;

    int graphHandleItem;
};