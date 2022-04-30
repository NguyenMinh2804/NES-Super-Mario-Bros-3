#include "Rectangle.h"
#include "Sprites.h"

void CRectangle::Render()
{
	if (type == 1)
	{
		for (int i = 0; i < size; i++)
		{
			if (i == 0)
			{
				CSprites::GetInstance()->Get(701)->Draw(x, y);
			}
			else if (i == size - 1)
			{
				CSprites::GetInstance()->Get(703)->Draw(x + 16 * i, y);
			}
			else {
				CSprites::GetInstance()->Get(702)->Draw(x + 16 * i, y);
			}
		}
	}
	else if (type == 2)
	{
		for (int i = 0; i < size; i++)
		{
			if (i == 0)
			{
				CSprites::GetInstance()->Get(704)->Draw(x, y);
			}
			else if (i == size - 1)
			{
				CSprites::GetInstance()->Get(706)->Draw(x + 16 * i, y);
			}
			else {
				CSprites::GetInstance()->Get(705)->Draw(x + 16 * i, y);
			}
		}
	}
	else if (type == 3)
	{
		for (int i = 0; i < size; i++)
		{
			if (i == 0)
			{
				CSprites::GetInstance()->Get(707)->Draw(x, y);
			}
			else if (i == size - 1)
			{
				CSprites::GetInstance()->Get(709)->Draw(x + 16 * i, y);
			}
			else {
				CSprites::GetInstance()->Get(708)->Draw(x + 16 * i, y);
			}
		}
	}
	else if (type == 4)
	{
		for (int i = 0; i < size; i++)
		{
			if (i == 0)
			{
				CSprites::GetInstance()->Get(710)->Draw(x, y);
			}
			else if (i == size - 1)
			{
				CSprites::GetInstance()->Get(712)->Draw(x + 16 * i, y);
			}
			else {
				CSprites::GetInstance()->Get(711)->Draw(x + 16 * i, y);
			}
		}
	}
	else if (type == 5)
	{
		for (int i = 0; i < size; i++)
		{
			CSprites::GetInstance()->Get(713)->Draw(x + 16 * i, y);
		}
	}
}

void CRectangle::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 16 / 2;
	t = y - 16 / 2;
	r = l + 16 * (size);
	b = t;
}