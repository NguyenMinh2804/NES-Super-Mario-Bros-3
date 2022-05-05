#pragma once
#include "GameObject.h"

#define TURTLE_GRAVITY 0.001f
#define TURTLE_WALKING_SPEED 0.02f


#define TURTLE_BBOX_WIDTH 16
#define TURTLE_BBOX_HEIGHT 24
#define TURTLE_BBOX_HEIGHT_SHELL 14

#define TURTLE_SHELL_TIMEOUT 6000


#define TURTLE_STATE_WALKING 100
#define TURTLE_STATE_SHELL 200
#define TURTLE_STATE_SHELL_ACTTACK_RIGHT 300
#define TURTLE_STATE_SHELL_ACTTACK_LEFT 400
#define TURTLE_STATE_FLY 500

#define ID_ANI_TURTLE_FLY 1807
class CTurtle : public CGameObject
{
protected:
	int ID_ANI_TURTLE_WALKING, ID_ANI_TURTLE_SHELL, ID_ANI_TURTLE_ATTACK;
	float ax;
	float ay;
	bool isRed;
	bool isFly;
	ULONGLONG shell_start;
	ULONGLONG attack_start;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 1; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CTurtle(float x, float y, bool isRed, bool isFly);
	virtual void SetState(int state);
	bool GetIsFly() { return isFly; };
	void SetIsFly(bool isFly) { this->isFly = isFly; };
};