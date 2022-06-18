#include "Rectangle.h"
#include "Sprites.h"

void CRectangle::Render()
{
	if (type == RECTANGLE_TYPE_PINK)
	{
		for (int i = 0; i < size; i++)
		{
			if (i == 0)
			{
				CSprites::GetInstance()->Get(ID_ANI_RECTANGLE_PINK_FIRST)->Draw(x, y);
			}
			else if (i == size - 1)
			{
				CSprites::GetInstance()->Get(ID_ANI_RECTANGLE_PINK_LAST)->Draw(x + RECTANGLE_BBOX_WIDTH * i, y);
			}
			else {
				CSprites::GetInstance()->Get(ID_ANI_RECTANGLE_PINK_MID)->Draw(x + RECTANGLE_BBOX_WIDTH * i, y);
			}
		}
	}
	else if (type == RECTANGLE_TYPE_BULE)
	{
		for (int i = 0; i < size; i++)
		{
			if (i == 0)
			{
				CSprites::GetInstance()->Get(ID_ANI_RECTANGLE_BLUE_FIRST)->Draw(x, y);
			}
			else if (i == size - 1)
			{
				CSprites::GetInstance()->Get(ID_ANI_RECTANGLE_BLUE_LAST)->Draw(x + RECTANGLE_BBOX_WIDTH * i, y);
			}
			else {
				CSprites::GetInstance()->Get(ID_ANI_RECTANGLE_BLUE_MID)->Draw(x + RECTANGLE_BBOX_WIDTH * i, y);
			}
		}
	}
	else if (type == RECTANGLE_TYPE_GREEN)
	{
		for (int i = 0; i < size; i++)
		{
			if (i == 0)
			{
				CSprites::GetInstance()->Get(ID_ANI_RECTANGLE_GREEN_FIRST)->Draw(x, y);
			}
			else if (i == size - 1)
			{
				CSprites::GetInstance()->Get(ID_ANI_RECTANGLE_GREEN_LAST)->Draw(x + RECTANGLE_BBOX_WIDTH * i, y);
			}
			else {
				CSprites::GetInstance()->Get(ID_ANI_RECTANGLE_GREEN_MID)->Draw(x + RECTANGLE_BBOX_WIDTH * i, y);
			}
		}
	}
	else if (type == RECTANGLE_TYPE_WHITE)
	{
		for (int i = 0; i < size; i++)
		{
			if (i == 0)
			{
				CSprites::GetInstance()->Get(ID_ANI_RECTANGLE_WHITE_FIRST)->Draw(x, y);
			}
			else if (i == size - 1)
			{
				CSprites::GetInstance()->Get(ID_ANI_RECTANGLE_WHITE_LAST)->Draw(x + RECTANGLE_BBOX_WIDTH * i, y);
			}
			else {
				CSprites::GetInstance()->Get(ID_ANI_RECTANGLE_WHITE_MID)->Draw(x + RECTANGLE_BBOX_WIDTH * i, y);
			}
		}
	}
	else if (type == RECTANGLE_TYPE_CLOUD)
	{
		for (int i = 0; i < size; i++)
		{
			CSprites::GetInstance()->Get(ID_ANI_RECTANGLE_CLOUD)->Draw(x + RECTANGLE_BBOX_WIDTH * i, y);
		}
	}
}

void CRectangle::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - RECTANGLE_BBOX_WIDTH / 2;
	t = y - RECTANGLE_BBOX_HEIGHT / 2;
	r = l + RECTANGLE_BBOX_WIDTH * (size);
	b = t;
}