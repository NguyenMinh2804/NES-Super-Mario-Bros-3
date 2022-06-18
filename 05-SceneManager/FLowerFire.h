#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_FLOWER_GREEN 107
#define FIRE_FLOWER_BBOX_WIDTH 16
#define FIRE_FLOWER_BBOX_HEIGHT 32
#define FIRE_FLOWER_RED 1
#define FIRE_FLOWER_GREEN 2
#define FLOWER_GREEN 3
#define FIRE_FLOWER_RED_UP_LEFT 101
#define FIRE_FLOWER_RED_DOWN_LEFT 102
#define FIRE_FLOWER_RED_UP_RIGHT 108
#define FIRE_FLOWER_RED_DOWN_RIGHT 109
#define FIRE_FLOWER_GREEN_UP_LEFT 103
#define FIRE_FLOWER_GREEN_DOWN_LEFT 104
#define FIRE_FLOWER_GREEN_UP_RIGHT 1010
#define FIRE_FLOWER_GREEN_DOWN_RIGHT 1011
#define Y_DEFINE 320
#define FLOWER_FIRE_TIME 1000
#define UP_TIME 3000
#define CUT_TIME 500
#define STATE_UP 0
#define STATE_DOWN 1
#define STATE_RELEASE_ACTTACK 2
#define UP_SPEED 0.8

class CFlowerFire : public CGameObject {
public:
	int direction;
	int type;
	float startX;
	float startY;
	int height;
	ULONGLONG fire_start;
	ULONGLONG up_start;
	CFlowerFire(float x, float y, int type) : CGameObject(x, y) {
		startX = x;
		startY = y;
		SetState(0);
		fire_start = -1;
		up_start = -1;
		this->type = type;
		if (type == 1)
		{
			height = 31;
		}
		else
		{
			height = 26;
		}
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Up();
	void Down();
	void SetState(int state);
	void StartFire() {fire_start = GetTickCount64(); }
	void StartUp() { up_start = GetTickCount64(); }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
};