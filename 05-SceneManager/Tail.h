#include "GameObject.h"

#define TAIL_BBOX_WIDTH 14
#define TAIL_BBOX_HEIGHT 4
#define TAIL_ATTACK_TIME 230
#define TAIL_ATTACK_SPEED 0.05f

class CTail : public CGameObject {
	ULONGLONG attack_start;
	int nx;
public:
	CTail(float x, float y, int nx)
	{
		this->nx = nx;
		if (nx == 1)
		{
			vx = TAIL_ATTACK_SPEED;
		}
		else
		{
			vx = -TAIL_ATTACK_SPEED;
		}
		this->x = x;
		this->y = y + 5;
		attack_start = GetTickCount64();
	}
	virtual int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
};