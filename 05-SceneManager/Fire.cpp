#include "Fire.h"

void CFire::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(110)->Render(x, y);
	//RenderBoundingBox();
}

void CFire::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 8 / 2;
	t = y - 8 / 2;
	r = l + 8;
	b = t + 8;
}