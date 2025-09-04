#pragma once
#include "Vector2.h"

class Line {
public:
    Line();
    void Draw() ;

    void SetPos(float x, float y) { pos.x = x; pos.y = y; }
    void SetSize(float w, float h) { width = w; height = h; }

    void LinePlayerHit(); // プレイヤーに当たった時
    void LineEnemyHit();  // 敵に当たった時

private:
    Vector2 pos;
    float width;
    float height;

    int LineTexture_;

    float moveAmountPlayer; // Playerに当たったときの移動量
    float moveAmountEnemy;  // Enemyに当たったときの移動量

};
