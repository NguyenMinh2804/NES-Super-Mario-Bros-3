#include "GameObject.h"

#define ID_ANI_BUTTON 201
#define BUTTON_BBOX_WIDTH 16
#define BUTTON_BBOX_HEIGHT 16
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