#include "GameObject.h"

class CMushroom : public CGameObject {
public:
	CMushroom(float x, float y) : CGameObject(x, y) {
		SetState(0);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
};