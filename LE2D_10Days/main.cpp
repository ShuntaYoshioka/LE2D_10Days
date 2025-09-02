#include <Novice.h>
#include "Player.h"
#include "Enemy.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"
#include "Line.h"
#include "Vector2.h"
#include <cstring>

const char kWindowTitle[] = "2061_試作";

const int WL = 0;
const int WR = 1280;
const int WT = 0;
const int WB = 720;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    Novice::Initialize(kWindowTitle, WR, WB);

    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

   
    Player player;
    Enemy enemy;
    Line line;

    const int kMaxPlayerBullets = 8;
    PlayerBullet playerBullets[kMaxPlayerBullets];

    const int kMaxEnemyBullets = 8;
    EnemyBullet enemyBullets[kMaxEnemyBullets];

    int playerBulletCooldown = 0;
    int enemyBulletCooldown = 0;

    while (Novice::ProcessMessage() == 0)
    {
        Novice::BeginFrame();
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        // プレイヤー移動
        player.Move(WL, WR, WT, WB, keys);

        // 敵移動
        enemy.Move(WL, WR, player.GetPos(), playerBullets, kMaxPlayerBullets);

        // プレイヤー弾発射
        if (playerBulletCooldown > 0) playerBulletCooldown--;
        if (keys[DIK_SPACE] && playerBulletCooldown <= 0){
            for (int i = 0; i < kMaxPlayerBullets; i++){
                if (!playerBullets[i].IsShot()){
                    playerBullets[i].Shoot(player.GetPos());
                    playerBulletCooldown = 10;
                    break;
                }
            }
        }

        // プレイヤー弾更新
        for (int i = 0; i < kMaxPlayerBullets; i++) playerBullets[i].Update();

        // 敵弾発射
        if (enemyBulletCooldown > 0) {
            enemyBulletCooldown--;
        };

        if (enemyBulletCooldown <= 0)
        {
            for (int i = 0; i < kMaxEnemyBullets; i++)
            {
                if (!enemyBullets[i].IsShot())
                {
                    enemyBullets[i].Shoot(enemy.GetPos());
                    enemyBulletCooldown = 30; // 敵のクールタイム
                    break;
                }
            }
        }

        //敵弾
        for (int i = 0; i < kMaxEnemyBullets; i++) enemyBullets[i].Update();

        //描画
        player.Draw();
        enemy.Draw();
        line.Draw();

        for (int i = 0; i < kMaxPlayerBullets; i++) playerBullets[i].Draw();
        for (int i = 0; i < kMaxEnemyBullets; i++) enemyBullets[i].Draw();

        Novice::EndFrame();

        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) break;
    }

    Novice::Finalize();
    return 0;
}
