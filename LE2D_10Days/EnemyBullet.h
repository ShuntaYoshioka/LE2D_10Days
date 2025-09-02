#pragma once
#include "Vector2.h"
#include <Novice.h>

class EnemyBullet {
public:
    EnemyBullet();
    void Shoot(const Vector2& startPos);
    void Update();
    void Draw() const;
    bool IsShot() const { return isShot; }

private:
    Vector2 pos;
    float radius;
    Vector2 velocity;
    bool isShot;
};
