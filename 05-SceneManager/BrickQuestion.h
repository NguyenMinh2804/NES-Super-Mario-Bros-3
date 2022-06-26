#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK_QUESTION 120
#define ID_ANI_BRICK_QUESTION_BROKEN 125
#define BRICK_QUESTION_BBOX_WIDTH 16
#define BRICK_QUESTION_BBOX_HEIGHT 16
#define HAVE_ITEM 1
#define BRICK_QUESTION_STATE_NORMAL 1
#define BRICK_QUESTION_STATE_BROKEN 0
#define BRICK_QUESTION_DROP_TIME 100
#define BRICK_PUSHED 6

class CBrickQuestion : public CGameObject {
public:
	int type;
	ULONGLONG drop_start;
	bool isDrop = false;
	CBrickQuestion(float x, float y, int type) : CGameObject(x, y) {
		this->type = type;
		drop_start = -1;
		SetState(BRICK_QUESTION_STATE_NORMAL);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
	void DropItem(int marioLevel);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
};