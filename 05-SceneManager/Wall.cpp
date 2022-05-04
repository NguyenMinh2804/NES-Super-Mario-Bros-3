#include "Wall.h"

void CWall::Render()
{
	//RenderBoundingBox();
}

void CWall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 16 / 2;
	t = y - 16 / 2;
	r = l;
	b = t + 16;
}