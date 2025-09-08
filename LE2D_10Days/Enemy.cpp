#include "Enemy.h"
#include <Novice.h>
#include <corecrt_math.h>

Enemy::Enemy() {
	Initialize();

	//テクスチャ読み込みはここ

}

void Enemy::Initialize()
{
	pos = { 640.0f, 100.0f };
	radius = 36.0f;
	speed = { 5.0f, 0.0f };

	dodgeCooldown = 0;
	dodgeDuration = 0;
	isDodging = false;

	isHit = false;
}

void Enemy::Move(int windowLeft, int windowRight, int windowTop, const Vector2& playerPos, const PlayerBullet* bullets, int bulletCount) {
	
	frameCount++;
	if (frameCount > 360) frameCount = 0;

	
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
		// X方向追従
		if (playerPos.x > pos.x) {
			pos.x += speed.x;
		} else if (playerPos.x < pos.x) {
			pos.x -= speed.x;
		}

		// Y方向にゆらゆら
		pos.y += sinf(GetFrameCount() * 0.1f) * 1.5f; // 上下ゆらゆら
	}


	//画面外に出ないようにする
	if (pos.x - radius < windowLeft) pos.x = windowLeft + radius;
	if (pos.x + radius > windowRight) pos.x = windowRight - radius;
	if (pos.y - radius < windowTop) pos.y = windowTop + radius;
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