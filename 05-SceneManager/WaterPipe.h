#include "GameObject.h"

class CWaterPipe : public CGameObject {
	int size;
public:
	CWaterPipe(float x, float y, int size)
	{
		this->x = x;
		this->y = y;
		this->size = size;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};