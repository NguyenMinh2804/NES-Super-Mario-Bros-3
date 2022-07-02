#pragma once
#include "GameObject.h"

#define	EFFECT_BRICK_BROKEN_FLY_SPEED 0.28f
#define EFFECT_BRICK_BROKEN_GRAVITY 0.0006f
#define EFFECT_BRICK_BROKEN_SPEED 0.04f

#define ID_ANI_EFFECT_TAIL_ACTTACK 41
#define ID_ANI_EFFECT_BRICK_BROKEN	44

#define EFFECT_BBOX_WIDTH 16
#define EFFECT_BBOX_HEIGHT 16
#define EFFECT_TIME_TAIL_ACTTACK 150
#define EFFECT_TIME_BRICK_BROKEN 1000
#define	EFFECT_TAIL_ACTTACK 0
#define	EFFECT_BRICK_BROKEN 1
#define	EFFECT_LEFT 1
#define	EFFECT_RIGHT 2
class CEffect : public CGameObject {
public:
	ULONGLONG effect_start;
	int type;
	int direction;
	float ay;
	float ax;
	CEffect(float x, float y, int type, int direction)
	{
		this->x = x;
		this->y = y;
		this->type = type;
		this->direction = direction;
		ax = 0;
		ay = EFFECT_BRICK_BROKEN_GRAVITY;
		vy = -EFFECT_BRICK_BROKEN_FLY_SPEED;
		if (direction == EFFECT_LEFT)
		{
			vx = -EFFECT_BRICK_BROKEN_SPEED;
		}
		else if (direction == EFFECT_RIGHT)
		{
			vx = EFFECT_BRICK_BROKEN_SPEED;
		}
		effect_start = GetTickCount64();
	}
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
};