#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
class CBrick2 : public CGameObject {
public:
	int type;
	CBrick2(float x, float y, int type) : CGameObject(x, y) {
		SetState(1);
		this->type = type;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
	void DropItem();
};