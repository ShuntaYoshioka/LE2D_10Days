#include "Player.h"
#include <Novice.h>

Player::Player() {
	pos = { 640.0f, 650.0f };
	radius = 36.0f;
	speed = { 10.0f, 10.0f };

	playerTexture_ = Novice::LoadTexture("Resource/Player/Tank.png");

}

void Player::Move(int windowLeft, int windowRight, int windowTop, int windowBottom, const char* keys) {

	//移動処理
	if (keys[DIK_W]) {
		pos.y -= speed.y;
	};

	if (keys[DIK_S]) {
		pos.y += speed.y;
	};

	if (keys[DIK_A]) {
		pos.x -= speed.x;
	};

	if (keys[DIK_D]) {
		pos.x += speed.x;
	};

	//出ないようにする
	if (pos.x - radius < windowLeft) {
		pos.x = windowLeft + radius;
	};

	if (pos.x + radius > windowRight) {
		pos.x = windowRight - radius;
	};

	if (pos.y - radius < windowTop) {
		pos.y = windowTop + radius;
	};

	if (pos.y + radius > windowBottom) {
		pos.y = windowBottom - radius;
	};
}



void Player::Hit() {
	//当たったかの確認と当たった時のフラグ
	isHit = true;
	hitTimer = hitDuration;
}

void Player::Update()
{
	//無敵時間を作る(まだ)
	if (isHit) {
		hitTimer--;
		if (hitTimer <= 0.0f) {
			isHit = false;//被弾状態解除
		}
	}


}

//当たり判定
bool Player::CheckHit(const Vector2& bulletPos, float bulletRadius) {
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


void Player::Draw() {
	if (isHit) {
		Novice::DrawBox((int)(pos.x - radius), (int)(pos.y - radius),
			(int)(radius * 2), (int)(radius * 2), 0.0f,
			RED, kFillModeSolid);
	} else {
		Novice::DrawSprite(
			static_cast<int>(pos.x - radius),
			static_cast<int>(pos.y - radius),
			playerTexture_,
			1.0f, 1.0f, 0.0f, WHITE);
	}



	// デバッグ用表示
	Novice::ScreenPrintf(0, 0, "Player isHit: %d", isHit);
}

