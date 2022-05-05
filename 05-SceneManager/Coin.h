#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN 11000

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16

class CCoin : public CGameObject {
	float ay;
	ULONGLONG drop_start;
public:
	CCoin(float x, float y) : CGameObject(x, y) {
		vy = 0;
		ay = 0.002f;
		drop_start = -1;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	void Fly() { vy = -0.5f; drop_start = GetTickCount64(); }
};