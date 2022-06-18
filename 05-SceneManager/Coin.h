#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN 11000
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16
#define FLY_COIN 1
#define FLY_COIN_SPEED -0.5f
#define FLY_COIN_GRAVITY 0.002f
#define FLY_COIN_TIME 400

class CCoin : public CGameObject {
	float ay;
	ULONGLONG drop_start;
	int type;
public:
	CCoin(float x, float y, int type) : CGameObject(x, y) {
		this->type = type;
		vy = 0;
		ay = FLY_COIN_GRAVITY;
		drop_start = -1;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	void Fly() { vy = FLY_COIN_SPEED; drop_start = GetTickCount64(); }
};