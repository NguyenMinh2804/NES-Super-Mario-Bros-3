#include "Wood.h"
#include "Sprites.h"

void CWood::Render()
{
	int aniId = ID_ANI_WOOD;
	switch (type)
	{
	case 0:
	{
		aniId = ID_ANI_WOOD; break;
	}
	case 1:
	{
		aniId = ID_ANI_WORLD1; break;
	}case 2:
	{
		aniId = ID_ANI_WORLD2; break;
	}case 3:
	{
		aniId = ID_ANI_WORLD3; break;
	}case 4:
	{
		aniId = ID_ANI_WORLD4; break;
	}
	case 5:
	{
		aniId = ID_ANI_WORLD5; break;
	}
	case 6:
	{
		aniId = ID_ANI_WORLD6; break;
	}
	case 7:
	{
		aniId = ID_ANI_WORLD_START; break;
	}
	case 8:
	{
		aniId = ID_ANI_WORLD_HEART; break;
	}
	case 9:
	{
		CAnimations::GetInstance()->Get(ID_ANI_WORLD_HELP)->Render(x, y);
		return;
		break;
	}
	}
	CSprites::GetInstance()->Get(aniId)->Draw(x, y);
}

void CWood::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - WOOD_BBOX_WIDTH / 2;
	t = y - WOOD_BBOX_HEIGHT / 2;
	r = l + WOOD_BBOX_WIDTH;
	b = t + WOOD_BBOX_HEIGHT;
}