#include "FlowerFire.h"

void CFlowerFire::Render()
{
	CSprites::GetInstance()->Get(101)->Draw(x, y);
}

void CFlowerFire::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 16 / 2;
	t = y - 32 / 2;
	r = l + 16;
	b = t + 32;
}

void CFlowerFire::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Up();
	Down();
}
void CFlowerFire::Up()
{
	if (y > 345)
	{
		y = y - 0.3;
	}
}
void CFlowerFire::Down()
{
	//if (y < 376)
	//{
	//	y = y + 0.3;
	//}
}
void CFlowerFire::OnNoCollision(DWORD dt)
{
	//y += vy * dt;
};