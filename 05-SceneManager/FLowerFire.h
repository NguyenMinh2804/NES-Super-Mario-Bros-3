#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
class CFlowerFire : public CGameObject {
public:
	CFlowerFire(float x, float y) : CGameObject(x, y) {
		SetState(0);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Up();
	void Down();
	void SetState(int state);
};