#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0002f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_JUMP_SPEED_Y		0.53f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_GRAVITY			0.00177777777777f
#define MARIO_SLOW_GRAVITY			0.0001f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_FLY_RIGHT	700
#define MARIO_STATE_FLY_LEFT	800

#define MARIO_STATE_SLOW_FALL	900
#define MARIO_STATE_FLY	901

#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

// FLY MARIO
#define ID_ANI_MARIO_FLY_IDLE_RIGHT 2100
#define ID_ANI_MARIO_FLY_IDLE_LEFT 2101

#define ID_ANI_MARIO_FLY_WALKING_RIGHT 2200
#define ID_ANI_MARIO_FLY_WALKING_LEFT 2201

#define ID_ANI_MARIO_FLY_RUNNING_RIGHT 2300
#define ID_ANI_MARIO_FLY_RUNNING_LEFT 2301

#define ID_ANI_MARIO_FLY_BRACE_RIGHT 2400
#define ID_ANI_MARIO_FLY_BRACE_LEFT 2401

#define ID_ANI_MARIO_JUMP_FLY_WALK_RIGHT 2500
#define ID_ANI_MARIO_JUMP_FLY_WALK_LEFT 2501

#define ID_ANI_MARIO_JUMP_FLY_RUN_RIGHT 2600
#define ID_ANI_MARIO_JUMP_FLY_RUN_LEFT 2601

#define ID_ANI_MARIO_FLY_SIT_RIGHT 2900
#define ID_ANI_MARIO_FLY_SIT_LEFT 2901

#define ID_ANI_MARIO_SLOW_FALL_RIGHT 2902
#define ID_ANI_MARIO_SLOW_FALL_LEFT 2903
#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_FLY		3

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12

#define MARIO_FLY_BBOX_WIDTH  14
#define MARIO_FLY_BBOX_HEIGHT 24
#define MARIO_FLY_SITTING_BBOX_WIDTH  14
#define MARIO_FLY_SITTING_BBOX_HEIGHT 16

#define MARIO_UNTOUCHABLE_TIME 2500

class CMario : public CGameObject
{
	BOOLEAN isSitting;
	float maxVx;
	float ay;				// acceleration on y 
	int untouchable; 
	int gameTime;
	ULONGLONG untouchable_start;
	ULONGLONG game_start;
	int coin; 

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithFlowerFire(LPCOLLISIONEVENT e);
	void OnCollisionWithBrickQuestion(LPCOLLISIONEVENT e);
	void OnCollisionWithFire(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e); 
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithRectangle(LPCOLLISIONEVENT e);
	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdFly();

public:
	int level;
	BOOLEAN isOnPlatform;
	int test;
	float ax;
	CMario(float x, float y, int gameTime) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 

		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		untouchable_start = -1;
		this->gameTime = gameTime;
		game_start = GetTickCount64();
		isOnPlatform = false;
		coin = 0;
		test = 0;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	void StartUntouchable() { untouchable = 5; untouchable_start = GetTickCount64(); }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};