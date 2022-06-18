#pragma once
#include "GameObject.h"

#define ID_ANI_LEAF 141
#define LEAF_BBOX_WIDTH 14
#define LEAF_BBOX_HEIGHT 16
#define LEAF_GRAVITY_X	0.00008f
#define LEAF_GRAVITY_Y	0.00002f
#define MAX_SPEED_RIGHT	0.04
#define MAX_SPEED_LEFT	0.05

class CLeaf : public CGameObject
{
protected:
	float ax;
	float ay;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CLeaf(float x, float y);
	virtual void SetState(int state);
};