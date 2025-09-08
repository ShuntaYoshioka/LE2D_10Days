#pragma once
#include "Vector2.h"
#include "PlayerBullet.h"

class Enemy {
public:
    Enemy();
    void Initialize();
    void Move(int windowLeft, int windowRight, int windowTop,const Vector2& playerPos, const PlayerBullet* bullets, int bulletCount);
    void Draw() ;

    void Update();
    void Hit();

    Vector2 GetPos() const { return pos; }
    float GetRadius() const { return radius; }

    bool CheckHit(const Vector2& bulletPos, float bulletRadius);

    bool IsHit() const { return isHit; }

    int GetFrameCount() const { return frameCount; }
private:
    Vector2 pos;
    float radius;
    Vector2 speed;

    // クールタイム
    int dodgeCooldown;  
    int dodgeDuration; 
    bool isDodging;

    int frameCount = 0;

    bool isHit = false;
    float hitTimer = 0.0f;
    float hitDuration = 30.0f;

};
