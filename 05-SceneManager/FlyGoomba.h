#pragma once
#include "GameObject.h"

#define FlyGoomba_GRAVITY 0.0001f
#define FlyGoomba_WALKING_SPEED 0.03f


#define FlyGoomba_BBOX_WIDTH 16
#define FlyGoomba_BBOX_HEIGHT 14
#define FlyGoomba_FLY_BBOX_WIDTH 20
#define FlyGoomba_FLY_BBOX_HEIGHT 22
#define FlyGoomba_BBOX_HEIGHT_DIE 7

#define FlyGoomba_DIE_TIMEOUT 500

#define FlyGoomba_STATE_WALKING 100
#define FlyGoomba_STATE_DIE 200
#define FlyGoomba_STATE_FLY 300

#define ID_ANI_FlyGoomba_WALKING 15101
#define ID_ANI_FlyGoomba_FLY 15102
#define ID_ANI_FlyGoomba_WALKING_SMALL 15103
#define ID_ANI_FlyGoomba_DIE 15104

class CFlyGoomba : public CGameObject
{
protected:
	float ax;
	float ay;
	ULONGLONG die_start;
	ULONGLONG walk_start;
	bool isFly = false;
	bool isOnPlatform;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 1; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CFlyGoomba(float x, float y);
	virtual void SetState(int state);
	void StartWalk() { walk_start = GetTickCount64(); }
};