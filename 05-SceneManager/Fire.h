#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
class CFire : public CGameObject {
public:
	CFire(float x, float y) : CGameObject(x, y) {
	}
	void Render();
	//void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};