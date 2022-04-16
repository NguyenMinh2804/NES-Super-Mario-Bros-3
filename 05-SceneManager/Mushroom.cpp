#include "Mushroom.h"

void CMushroom::Render()
{
	CSprites::GetInstance()->Get(131)->Draw(x, y);
}

void CMushroom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 16 / 2;
	t = y - 16 / 2;
	r = l + 16;
	b = t + 16;
}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}


void CMushroom::SetState(int state)
{
	CGameObject::SetState(state);
}