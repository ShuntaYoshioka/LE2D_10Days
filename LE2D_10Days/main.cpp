#include <Novice.h>
#include "Player.h"
#include "Enemy.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"
#include "Line.h"
#include "Item.h"
#include "ItemTracking.h"
#include "TrackingBullet.h"
#include "Vector2.h"
#include <ctime>
#include <cstdlib>

const char kWindowTitle[] = "2061_試作";

const int WL = 0;
const int WR = 1280;
const int WT = 0;
const int WB = 720;

enum Scene {
	TITLE,
	CREDIT,
	TUTORIAL,
	GAME,
	CLEAR,
	OVER
};


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Novice::Initialize(kWindowTitle, WR, WB);

	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	int scene = TITLE;


	unsigned int currentTime = static_cast<unsigned int>(time(nullptr));
	srand(currentTime);

	Player player;
	Enemy enemy;
	Line line;

	ItemTracking trackingItem;
	Item doubleAttack;

	const int kMaxPlayerBullets = 8;
	PlayerBullet playerBullets[kMaxPlayerBullets];

	const int kMaxEnemyBullets = 8;
	EnemyBullet enemyBullets[kMaxEnemyBullets];

	const int kMaxTrackingBullets = 8;
	TrackingBullet trackingBullets[kMaxTrackingBullets];

	int playerBulletCooldown = 0;
	int enemyBulletCooldown = 0;
	int trackingBulletCooldown = 0;

	int isGameOver = false;
	int isGameClear = false;

	while (Novice::ProcessMessage() == 0)
	{
		Novice::BeginFrame();
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		switch (scene) {
		case TITLE:
			Novice::ScreenPrintf(600, 360, "SPACE : GAME");
			Novice::ScreenPrintf(600, 380, "C : CREDIT");
			Novice::ScreenPrintf(600, 400, "T : TUTORIAL");

			player.Initialize();
			enemy.Initialize();
			line.Initialize();
			doubleAttack.Initialize();
			trackingItem.Initialize();
			for (int i = 0; i < kMaxTrackingBullets; i++) trackingBullets[i].Initialize();
			for (int i = 0; i < kMaxPlayerBullets; i++) playerBullets[i].Initialize();
			for (int i = 0; i < kMaxEnemyBullets; i++) enemyBullets[i].Initialize();
			isGameOver = false;
			isGameClear = false;
			playerBulletCooldown = 0;
			enemyBulletCooldown = 0;
			trackingBulletCooldown = 0;



			if (keys[DIK_SPACE]) {
				scene = GAME;
				break;
			}
			if (preKeys[DIK_C]) {
				scene = CREDIT;
				break;
			}
			if (preKeys[DIK_T]) {
				scene = TUTORIAL;
				break;
			}
			break;


		case CREDIT:
			Novice::ScreenPrintf(600, 360, "E : TITLE");

			if (preKeys[DIK_E]) {
				scene = TITLE;
				break;
			}
			break;


		case TUTORIAL:
			Novice::ScreenPrintf(600, 360, "E : TITLE");

			if (preKeys[DIK_E]) {
				scene = TITLE;
				break;
			}
			break;

		case GAME:
			Novice::ScreenPrintf(600, 360, "C : CLEAR");
			Novice::ScreenPrintf(600, 380, "B : OVER");

			if (preKeys[DIK_C]) {
				scene = CLEAR;
				break;
			}
			if (preKeys[DIK_B]) {
				scene = OVER;
				break;
			}

			// プレイヤー移動
			player.Move(WL, WR, WT, WB, keys);

			// 敵移動
			enemy.Move(WL, WR, WT, player.GetPos(), playerBullets, kMaxPlayerBullets);

			// プレイヤー弾発射
			if (playerBulletCooldown > 0) {
				playerBulletCooldown--;
			}
			if (trackingBulletCooldown > 0) {
				trackingBulletCooldown--;
			}
			
			// --- 弾発射処理 ---
			if (keys[DIK_SPACE] && playerBulletCooldown <= 0) {

				// ダブルアタックを取得していないとき
				if (!doubleAttack.IsActiveGet()) {
					for (int i = 0; i < kMaxPlayerBullets; i++) {
						if (!playerBullets[i].IsShot()) {
							playerBullets[i].Shoot(player.GetPos());
							playerBulletCooldown = 20; // クールダウン
							break;
						}
					}
				}
				// ダブルアタック取得中のとき
				else {
					int firstIndex = -1;
					int secondIndex = -1;

					// 空いている弾を2つ探す
					for (int i = 0; i < kMaxPlayerBullets; i++) {
						if (!playerBullets[i].IsShot()) {
							if (firstIndex == -1) {
								firstIndex = i;
							} else if (secondIndex == -1) {
								secondIndex = i;
								break;
							}
						}
					}

					if (firstIndex != -1 && secondIndex != -1) {
						Vector2 playerPos = player.GetPos();

						// 左の弾
						Vector2 leftPos = { playerPos.x - 20.0f, playerPos.y };
						playerBullets[firstIndex].Shoot(leftPos);

						// 右の弾
						Vector2 rightPos = { playerPos.x + 20.0f, playerPos.y };
						playerBullets[secondIndex].Shoot(rightPos);

						playerBulletCooldown = 10; // クールダウン
					}
				}

				if (trackingItem.IsActiveGet()) {
					for (int i = 0; i < kMaxTrackingBullets; i++) {
						if (!trackingBullets[i].IsShot()) {
							trackingBullets[i].Shoot(player.GetPos());
							trackingBulletCooldown = 20; // クールダウン
							break;
						}
					}
				}
			}
			// プレイヤー弾更新
			for (int i = 0; i < kMaxPlayerBullets; i++) playerBullets[i].Update();
			for (int i = 0; i < kMaxTrackingBullets; i++) trackingBullets[i].Update(enemy);



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

			for (int i = 0; i < kMaxPlayerBullets; i++) {
				if (playerBullets[i].IsShot()) {
					float dx = playerBullets[i].GetPos().x - enemy.GetPos().x;
					float dy = playerBullets[i].GetPos().y - enemy.GetPos().y;
					float distSq = dx * dx + dy * dy;
					float hitRange = playerBullets[i].GetRadius() + enemy.GetRadius();

					if (distSq < hitRange * hitRange) {
						playerBullets[i].SetShot(false); // 弾は必ず消える
						if (!enemy.IsHit()) {            // 無敵中でなければ被弾演出
							enemy.Hit();
							line.LineEnemyHit();
						}
					}
				}
			}

			for (int i = 0; i < kMaxTrackingBullets; i++) {
				if (trackingBullets[i].IsShot()) {
					float dx = trackingBullets[i].GetPos().x - enemy.GetPos().x;
					float dy = trackingBullets[i].GetPos().y - enemy.GetPos().y;
					float distSq = dx * dx + dy * dy;
					float hitRange = trackingBullets[i].GetRadius() + enemy.GetRadius();

					if (distSq < hitRange * hitRange) {
						trackingBullets[i].SetShot(false); // 弾は必ず消える
						if (!enemy.IsHit()) {              // 無敵中でなければ被弾演出
							enemy.Hit();
							line.LineEnemyHit();
						}
					}
				}
			}

			// アイテム更新
			doubleAttack.Move();
			trackingItem.Move();

			for (int i = 0; i < kMaxPlayerBullets; i++) {
				if (playerBullets[i].IsShot()) {
					doubleAttack.CheckGet(playerBullets, kMaxPlayerBullets);
					trackingItem.CheckGet(playerBullets, kMaxPlayerBullets);
				}
			}





			//被弾タイマー更新 ======
			player.Update();
			enemy.Update();

			if (line.CheckHitPlayer(player)) {
				isGameOver = true;  //負け
				scene = OVER;
			}
			if (line.CheckHitEnemy(enemy)) {
				isGameClear = true; //勝利
				scene = CLEAR;
			}



			//描画
			player.Draw();
			enemy.Draw();
			line.Draw();
			doubleAttack.Draw();
			trackingItem.Draw();



			for (int i = 0; i < kMaxPlayerBullets; i++) playerBullets[i].Draw();
			for (int i = 0; i < kMaxEnemyBullets; i++) enemyBullets[i].Draw();
			for (int i = 0; i < kMaxTrackingBullets; i++) trackingBullets[i].Draw();

			break;


		case CLEAR:
			Novice::ScreenPrintf(600, 360, "GAME CLEAR  E : TITLE");

			if (preKeys[DIK_E]) {
				scene = TITLE;
				break;
			}
			break;


		case OVER:
			Novice::ScreenPrintf(600, 360, "GAME OVER  E : TITLE");

			if (preKeys[DIK_E]) {
				scene = TITLE;
				break;
			}
			break;
		}



		Novice::EndFrame();

		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) break;
	}

	Novice::Finalize();
	return 0;
}
