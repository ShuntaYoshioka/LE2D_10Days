#pragma once
#include "Vector2.h"
#include <Novice.h>

class Enemy;
class PlayerBullet;

class Item {
public:
    enum class Type {
        DoubleAttack,
        FollowBullet
    };

    Item(Type type);
    void Initialize();
    void Update();
    void Draw() const;

    // アイテム取得判定
    void CheckGet(PlayerBullet* bullets, int bulletCount);

    // Getter
    Vector2 GetPos() const { return pos; }
    float GetRadius() const { return radius; }
    bool IsGet() const { return isGet; }
    bool IsAppear() const { return isAppear; }

    // Setter
    void SetGet(bool get) { isGet = get; }
    void SetAppear(bool appear) { isAppear = appear; }

    // 追尾弾
    void FollowBullet(PlayerBullet& bullet, const Enemy& enemy) const;

private:
    Type type;
    Vector2 pos;
    Vector2 speed;
    float radius;
    bool isAppear;
    bool isGet;
    int timeLimit;

    // 静的テクスチャ（全インスタンス共通）
    static int textureDoubleAttack;
    static int textureFollowBullet;

    // テクスチャ読み込み
    void LoadTexture();
};
