#include "InvisibleWall.h"

void CInvisibleWall::Render()
{
	//RenderBoundingBox();
}

void CInvisibleWall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 16 / 2;
	t = y - 16 / 2;
	r = l;
	b = t + 16;
}