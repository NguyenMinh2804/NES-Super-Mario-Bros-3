#include "GameObject.h"

class CTail : public CGameObject {
	ULONGLONG attack_start;
	int nx;
public:
	CTail(float x, float y, int nx)
	{
		this->nx = nx;
		if (nx == 1)
		{
			vx = 0.05f;
		}
		else
		{
			vx = -0.05f;
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