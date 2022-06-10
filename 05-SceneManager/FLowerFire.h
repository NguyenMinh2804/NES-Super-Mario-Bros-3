#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
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