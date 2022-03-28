#include "Wood.h"
#include "Sprites.h"

void CWood::Render()
{	
	CSprites::GetInstance()->Get(81)->Draw(x, y);
}

void CWood::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 16 / 2;
	t = y - 16 / 2;
	r = l + 16;
	b = t + 16;
}