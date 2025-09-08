#pragma once
#include "Vector2.h"
#include <Novice.h>

class EnemyBullet {
public:
    EnemyBullet();
    void Initialize();
    void Shoot(const Vector2& startPos);
    void Update();
    void Draw() ;

    bool IsShot() const { return isShot; }

    Vector2 GetPos() const { return pos; }
    float GetRadius() const { return radius; }
	void SetShot(bool shot) { isShot = shot; }

private:
    Vector2 pos;
    float radius;
    Vector2 velocity;
    bool isShot;
};
