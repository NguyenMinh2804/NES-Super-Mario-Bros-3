#include "Effect.h"
#include "Sprites.h"

void CEffect::Render()
{
	CSprites::GetInstance()->Get(ID_ANI_EFFECT)->Draw(x, y);
}

void CEffect::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - EFFECT_BBOX_WIDTH / 2;
	t = y - EFFECT_BBOX_HEIGHT / 2;
	r = l + EFFECT_BBOX_WIDTH;
	b = t + EFFECT_BBOX_HEIGHT;
}

void CEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetTickCount64() - effect_start > EFFECT_TIME)
	{
		this->Delete();
	}
}
