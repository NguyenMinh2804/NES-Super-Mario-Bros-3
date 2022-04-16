#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
class CFire : public CGameObject {
	int direction;
	float x;
	float y;
public:
	CFire(float x, float y, int direction){
		this->x = x;
		this->y = y;
		this->direction = direction;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
};