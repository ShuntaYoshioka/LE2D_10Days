#pragma once
#include "Vector2.h"

class Player {
public:
    Player();
    void Move(int windowLeft, int windowRight, int windowTop, int windowBottom, const char* keys);
    void Draw() const;

    Vector2 GetPos() const { return pos; }
    float GetRadius() const { return radius; }

private:
    Vector2 pos;
    float radius;
    Vector2 speed;
};
