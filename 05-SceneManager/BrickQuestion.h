#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
class CBrickQuestion : public CGameObject {
public:
	int type;
	CBrickQuestion(float x, float y, int type) : CGameObject(x, y) {
		this->type = type;
		SetState(1);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
	void DropItem(int marioLevel);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
};