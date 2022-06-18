#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_FIRE 110
#define FIRE_BBOX_WIDTH 8
#define FIRE_BBOX_HEIGHT 8
#define FIRE_UP_LEFT 1
#define FIRE_DOWN_LEFT 2
#define FIRE_UP_RIGHT 3
#define FIRE_DOWN_RIGHT 4
#define FIRE_TIME 6000
#define SPEED_X 0.055f
#define SPEED_Y 0.02f

class CFire : public CGameObject
{
protected:
	int direction;
	ULONGLONG attack_start;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CFire(float x, float y, int direction);
	virtual void SetState(int state);
};