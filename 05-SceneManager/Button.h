#include "GameObject.h"

class CButton : public CGameObject {
public:
	CButton(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Trigger();
};