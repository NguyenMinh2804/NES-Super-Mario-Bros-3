#include "Rectangle.h"
#include "Sprites.h"

void CRectangle::Render()
{
	if (type == 1)
	{
		CSprites::GetInstance()->Get(71)->Draw(x, y);
	}
	else if (type == 2)
	{
		CSprites::GetInstance()->Get(72)->Draw(x, y);
	}
	else
	{
		CSprites::GetInstance()->Get(73)->Draw(x, y);
	}
}

void CRectangle::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 16 / 2;
	t = y - 16 / 2;
	r = l + 16;
	b = t + 16;
}