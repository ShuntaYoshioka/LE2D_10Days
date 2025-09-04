#include "Enemy.h"
#include <Novice.h>

Enemy::Enemy() {
	pos = { 640.0f, 100.0f };
	radius = 36.0f;
	speed = { 5.0f, 0.0f };

	dodgeCooldown = 0;
	dodgeDuration = 0;
	isDodging = false;    
}

void Enemy::Move(int windowLeft, int windowRight, const Vector2& playerPos, const PlayerBullet* bullets, int bulletCount) {
	if (dodgeCooldown > 0) {
		dodgeCooldown--;
	}
	if (dodgeDuration > 0) {
		dodgeDuration--;
		if (dodgeDuration == 0) {
			isDodging = false;
			dodgeCooldown = 60; //クールタイム
		}
	}

	// 弾が近いかチェック
	if (!isDodging && dodgeCooldown <= 0) {
		float nearestDistance = 9999.9f;
		Vector2 nearestBulletPos{};
		bool foundBullet = false;

		for (int i = 0; i < bulletCount; i++) {
			if (!bullets[i].IsShot()) continue;

			float dx = bullets[i].GetPos().x - pos.x;
			float dy = bullets[i].GetPos().y - pos.y;
			float dist = dx * dx + dy * dy;

			if (dist < nearestDistance) {
				nearestDistance = dist;
				nearestBulletPos = bullets[i].GetPos();
				foundBullet = true;
			}
		}

		if (foundBullet && nearestDistance < 200 * 200) { //回避が起きる間合い
			isDodging = true;
			dodgeDuration = 20; // 20fだけ回避

			if (nearestBulletPos.x > pos.x) {
				pos.x -= speed.x * 8;
			} else {
				pos.x += speed.x * 8;
			}
		}
	}

	//追尾
	if (!isDodging) {
		if (playerPos.x > pos.x) {
			pos.x += speed.x;
		} else if (playerPos.x < pos.x) {
			pos.x -= speed.x;
		}
	}

	//画面外に出ないようにする
	if (pos.x - radius < windowLeft) pos.x = windowLeft + radius;
	if (pos.x + radius > windowRight) pos.x = windowRight - radius;
}

void Enemy::Draw() {
	if (isHit) {
		Novice::DrawBox((int)(pos.x - radius), (int)(pos.y - radius),
			(int)(radius * 2), (int)(radius * 2), 0.0f,
			RED, kFillModeSolid);
	} else {
		Novice::DrawBox(
			static_cast<int>(pos.x - radius), static_cast<int>(pos.y - radius), static_cast<int>(radius * 2), static_cast<int>(radius * 2),
			0.0f,
			BLACK,
			kFillModeSolid
		);
	}
}

void Enemy::Update()
{
	if (isHit) {
		hitTimer--;
		if (hitTimer <= 0.0f) {
			isHit = false;
		}
	}

}

void Enemy::Hit()
{
	isHit = true;
	hitTimer = hitDuration;
}

bool Enemy::CheckHit(const Vector2& bulletPos, float bulletRadius) {
	if (!isHit) {
		float dx = bulletPos.x - pos.x;
		float dy = bulletPos.y - pos.y;
		float distSq = dx * dx + dy * dy;
		float hitRange = radius + bulletRadius;

		if (distSq < hitRange * hitRange) {
			isHit = true;
			hitTimer = 60; // 60f 被弾状態
			return true;
		}
	}
	
	return false;
}




