#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
class CBrickQuestion : public CGameObject {
public:
	CBrickQuestion(float x, float y) : CGameObject(x, y) {
		SetState(1);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
};