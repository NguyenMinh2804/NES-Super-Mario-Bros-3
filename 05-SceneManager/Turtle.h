#pragma once
#include "GameObject.h"

#define TURTLE_GRAVITY 0.001f
#define TURTLE_WALKING_SPEED 0.02f
#define TURTLE_DIE_SPEED 0.38f;

#define TURTLE_BBOX_WIDTH 16
#define TURTLE_BBOX_HEIGHT 24
#define TURTLE_BBOX_HEIGHT_SHELL 14

#define TURTLE_SHELL_TIMEOUT 7000


#define TURTLE_STATE_WALKING 100
#define TURTLE_STATE_SHELL 200
#define TURTLE_STATE_SHELL_BY_TAIL 201

#define TURTLE_STATE_SHELL_ACTTACK_RIGHT 300
#define TURTLE_STATE_SHELL_ACTTACK_LEFT 400
#define TURTLE_STATE_FLY 500

#define	ID_ANI_TURTLE_RED_WALKING_LEFT 1801;
#define	ID_ANI_TURTLE_RED_WALKING_RIGHT 1808;
#define	ID_ANI_TURTLE_RED_SHELL 1802;
#define	ID_ANI_TURTLE_RED_ATTACK 1803;
#define ID_ANI_TURTLE_RED_SHELL_BY_TAIL 1812;
#define ID_ANI_TURTLE_RED_ATTACK_BY_TAIL 1830;

#define ID_ANI_TURTLE_GREEN_WALKING_LEFT 1804;
#define ID_ANI_TURTLE_GREEN_WALKING_RIGHT 1809;
#define ID_ANI_TURTLE_GREEN_SHELL 1805;
#define ID_ANI_TURTLE_GREEN_SHELL_BY_TAIL 1811;
#define ID_ANI_TURTLE_GREEN_ATTACK 1806;
#define ID_ANI_TURTLE_GREEN_ATTACK_BY_TAIL 1834;

#define ID_ANI_TURTLE_FLY_LEFT 1807
#define ID_ANI_TURTLE_FLY_RIGHT 1810

#define TURTLE_FLY_GRAVITY 0.0002
#define TURTLE_FLY_SPEED 0.27f
#define TURTLE_ATTACK_SPEED 0.22f
class CTurtle : public CGameObject
{
protected:
	int ID_ANI_TURTLE_WALKING_LEFT, 
		ID_ANI_TURTLE_WALKING_RIGHT, 
		ID_ANI_TURTLE_SHELL, 
		ID_ANI_TURTLE_ATTACK, 
		ID_ANI_TURTLE_ATTACK_BY_TAIL,
		ID_ANI_TURTLE_SHELL_BY_TAIL;

	float ax;
	float ay;
	ULONGLONG shell_start;
	ULONGLONG attack_start;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() {
		return 0; 
	}
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	bool isFly;
	bool isRed;
	bool isPickUp = false;
	bool isActtackByTail = false;
	int marioNX;
	CTurtle(float x, float y, bool isRed, bool isFly);
	virtual void SetState(int state);
	bool GetIsFly() { return isFly; };
	void SetIsFly(bool isFly) { this->isFly = isFly; };
};