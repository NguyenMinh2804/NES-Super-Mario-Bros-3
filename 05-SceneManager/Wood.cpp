#include "Wood.h"
#include "Sprites.h"

void CWood::Render()
{	
	CSprites::GetInstance()->Get(ID_ANI_WOOD)->Draw(x, y);
}

void CWood::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - WOOD_BBOX_WIDTH / 2;
	t = y - WOOD_BBOX_HEIGHT / 2;
	r = l + WOOD_BBOX_WIDTH;
	b = t + WOOD_BBOX_HEIGHT;
}