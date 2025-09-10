#pragma once
#include "Vector2.h"
#include <Novice.h>
#include "Enemy.h"

class TrackingBullet {
public:
    TrackingBullet();

    void Initialize();
    void Shoot(const Vector2& startPos);
    void Update(Enemy& enemy);
    void Draw();

    bool IsShot() const { return isShot; }
    void SetShot(bool value) { isShot = value; }

    Vector2 GetPos() const { return pos; }
    float GetRadius() const { return radius; }

private:
    Vector2 pos;
    float speed;
    float radius;
    bool isShot;

    int graphHandleBullet;
};
