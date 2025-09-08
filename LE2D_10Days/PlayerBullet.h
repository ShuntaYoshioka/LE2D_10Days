#pragma once
#include "Vector2.h"

class PlayerBullet {
public:
    PlayerBullet();
    void Initialize();
    void Update();
    void Draw() ;
    void Shoot(const Vector2& startPos);

    bool IsShot() const { return isShot; }
    Vector2 GetPos() const { return pos; }
    float GetRadius() const { return radius; }
	void SetShot(bool shot) { isShot = shot; }

    Vector2 GetVelocity() const { return velocity; }
    void SetVelocity(const Vector2& v) { velocity = v; }

private:
    bool isShot;
    Vector2 pos;
    Vector2 velocity;
    float radius;
};
