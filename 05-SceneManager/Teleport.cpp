#include "Teleport.h"

void CTeleport::Render()
{
	RenderBoundingBox();
}

void CTeleport::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - TELEPORT_BBOX_WIDTH / 2;
	t = y - TELEPORT_BBOX_HEIGHT / 2;
	r = l + TELEPORT_BBOX_WIDTH;
	b = t + TELEPORT_BBOX_HEIGHT;
}