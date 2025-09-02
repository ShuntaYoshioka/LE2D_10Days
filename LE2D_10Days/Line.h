#pragma once
#include "Vector2.h"

class Line {
public:
    Line();
    void Draw() const;

private:
    Vector2 pos;
    float width;
    float height;
public:
    void SetPos(float x, float y) { pos.x = x; pos.y = y; }
    void SetSize(float w, float h) { width = w; height = h; }
};
