#pragma once
#include "GameObject.h"

#define ID_ANI_EFFECT 41
#define EFFECT_BBOX_WIDTH 16
#define EFFECT_BBOX_HEIGHT 16
#define EFFECT_TIME 150

class CEffect : public CGameObject {
public:
	ULONGLONG effect_start;
	CEffect(float x, float y)
	{
		this->x = x;
		this->y = y;
		effect_start = GetTickCount64();
	}
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
};