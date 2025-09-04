#pragma once
#include "Vector2.h"

class Player {
public:
    Player();
    void Move(int windowLeft, int windowRight, int windowTop, int windowBottom, const char* keys);
    void Hit();
    void Update();
    bool IsHit() const { return isHit; }
    bool CheckHit(const Vector2& bulletPos, float bulletRadius);
   


    void Draw() ;

    Vector2 GetPos() const { return pos; }
    float GetRadius() const { return radius; }

private:
    Vector2 pos;
    float radius;
    Vector2 speed;

    bool isHit = false;
    float hitTimer = 0.0f;
    float hitDuration = 30.0f;//次にヒットするまでの猶予 無敵時間とする
    int playerTexture_;

};