#include "FlowerFire.h"

void CFlowerFire::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(100)->Render(x, y);
}

void CFlowerFire::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 16 / 2;
	t = y - 32 / 2;
	r = l + 16;
	b = t + 32;
}