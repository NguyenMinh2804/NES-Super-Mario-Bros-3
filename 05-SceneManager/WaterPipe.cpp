#include "Ground.h"
#include "WaterPipe.h"

void CWaterPipe::Render()
{
	CSprites::GetInstance()->Get(91)->Draw(x, y);
	CSprites::GetInstance()->Get(92)->Draw(x + 16, y);
	for (int i = 1; i <= size; i++)
	{
		CSprites::GetInstance()->Get(93)->Draw(x, y + 16*i);
		CSprites::GetInstance()->Get(94)->Draw(x + 16, y + 16*i);
	}

}

void CWaterPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 16 / 2;
	t = y - 16 / 2;
	r = l + 32;
	b = t + 16 * (size + 1);
}