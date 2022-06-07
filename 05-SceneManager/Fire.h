#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

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