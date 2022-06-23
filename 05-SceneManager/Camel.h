#pragma once
#include "GameObject.h"

#define CAMEL_GRAVITY 0.002f
#define CAMEL_WALKING_SPEED 0.03f


#define CAMEL_BBOX_WIDTH 16
#define CAMEL_BBOX_HEIGHT 16
#define ID_ANI_CAMEL_WALKING_RIGHT 35
#define ID_ANI_CAMEL_WALKING_LEFT 36
#define CAMEL_DISTANCE_MAX 6

class CCamel : public CGameObject
{
protected:
	float ax;
	float ay;
	int startX;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
public:
	CCamel(float x, float y) : CGameObject(x, y) {
		startX = x;
		ax = 0;
		ay = 0;
		vx = -0.01f;
		vy = 0;
	};
};