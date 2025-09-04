#include "Player.h"
#include <Novice.h>

Player::Player() {
	pos = { 640.0f, 650.0f };
	radius = 30.0f;
	speed = { 10.0f, 10.0f };
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

void Player::Draw()  {
	Novice::DrawBox((int)(pos.x - radius), (int)(pos.y - radius),
		(int)(radius * 2), (int)(radius * 2), 0.0f,
		BLACK, kFillModeSolid);
}
