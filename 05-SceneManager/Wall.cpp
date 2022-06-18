#include "Wall.h"

void CWall::Render()
{
	//RenderBoundingBox();
}

void CWall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - WALL_BBOX_WIDTH / 2;
	t = y - WALL_BBOX_HEIGHT / 2;
	r = l;
	b = t + WALL_BBOX_HEIGHT;
}