#include "GameObject.h"
#define ID_ANI_MUSHROOM_RED 131
#define ID_ANI_MUSHROOM_GREEN 132
#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 16
#define TYPE_MUSHROOM_RED 0
#define TYPE_MUSHROOM_GREEN 1
#define MUSHROOM_GRAVITY 0.001f
#define MUSHROOM_SPEED 0.045f

class CMushroom : public CGameObject
{
protected:
	float ax;
	float ay;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	int type;
	CMushroom(float x, float y, int type);
	virtual void SetState(int state);
};