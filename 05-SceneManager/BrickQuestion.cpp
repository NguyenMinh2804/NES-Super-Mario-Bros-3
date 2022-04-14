#include "BrickQuestion.h"

void CBrickQuestion::Render()
{
	if (state == 0)
	{
		CSprites::GetInstance()->Get(125)->Draw(x, y);
	}
	else
	{
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(120)->Render(x, y);
	}
}

void CBrickQuestion::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 16 / 2;
	t = y - 16 / 2;
	r = l + 16;
	b = t + 16;
}

void CBrickQuestion::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void CBrickQuestion::SetState(int state)
{
	CGameObject::SetState(state);
}