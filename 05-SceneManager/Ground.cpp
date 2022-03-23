#include "Ground.h"
#include "Sprites.h"

void CGround::Render()
{
	if (type == 1)
	{
		CSprites::GetInstance()->Get(61)->Draw(x, y);
	}else if(type == 2)
	{
		CSprites::GetInstance()->Get(62)->Draw(x, y);
	}else
	{
		CSprites::GetInstance()->Get(63)->Draw(x, y);
	}
}

void CGround::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 16 / 2;
	t = y - 16 / 2;
	r = l + 16;
	b = t + 16;
}