#include "Fire.h"
#include "Mario.h"

void CFire::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(110)->Render(x, y);
	//RenderBoundingBox();
}

void CFire::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 8 / 2;
	t = y - 8 / 2;
	r = l + 8;
	b = t + 8;
}

void CFire::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	switch (direction)
	{
	case 1:
	{
		x = x - 0.6;
		//y = y + 0.6;
		break;
	}
	case 2: 
	{
		x = x - 0.6;
		y = y - 0.6;
		break;
	}
	case 3:
	{
		x = x + 0.6;
		y = y - 0.6;
		break;
	}
	case 4:
	{
		x = x + 0.6;
		y = y + 0.6;
		break;
	}
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CFire::OnCollisionWith(LPCOLLISIONEVENT e)
{
	this->Delete();
	//if (dynamic_cast<CMario*>(e->obj))
	//	OnCollisionWithMario(e);
}

void CFire::OnNoCollision(DWORD dt)
{

}
//void OnCollisionWithMario(LPCOLLISIONEVENT e)
//{
//	return;
//}