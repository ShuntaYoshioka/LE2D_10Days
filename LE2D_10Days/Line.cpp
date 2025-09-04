#include "Line.h"
#include <Novice.h>

Line::Line() {
    pos = { 0, 350 };
    width = 1280;
    height = 20;
}

void Line::Draw()  {
    Novice::DrawBox((int)pos.x, (int)pos.y, (int)width, (int)height, 0.0f,BLACK, kFillModeSolid);
}
