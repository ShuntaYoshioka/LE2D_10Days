#pragma once
#include "Vector2.h"
#include "Player.h"
#include "PlayerBullet.h"

class Enemy {
public:
    Enemy();
    void Move(int windowLeft, int windowRight, const Vector2& playerPos,
        const PlayerBullet* bullets, int bulletCount); void Draw() const;

    Vector2 GetPos() const { return pos; }
    float GetRadius() const { return radius; }

private:
    Vector2 pos;
    float radius;
    Vector2 speed;

    int dodgeCooldown; //回避行動とかのクールタイム
};
