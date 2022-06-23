#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK2 190
#define BRICK2_BBOX_WIDTH 16
#define BRICK2_BBOX_HEIGHT 16
#define ITEM_BUTTON 1
#define ITEM_GREEN_MUSHROOM 2
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