//#include "Leaf.h"
//#include "Rectangle.h"
//#include "Ground.h"
//
//CLeaf::CLeaf(float x, float y) :CGameObject(x, y)
//{
//	this->ax = 0.00005f;
//	this->ay = 0.00001f;
//	SetState(0);
//}
//
//void CLeaf::GetBoundingBox(float& left, float& top, float& right, float& bottom)
//{
//	left = x - 16 / 2;
//	top = y - 14 / 2;
//	right = left + 16;
//	bottom = top + 14;
//}
//
//void CLeaf::OnNoCollision(DWORD dt)
//{
//	x += vx * dt;
//	y += vy * dt;
//};
//
//void CLeaf::OnCollisionWith(LPCOLLISIONEVENT e)
//{
//}
//
//void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
//{
//	if (vx > 0.04)
//	{
//		ax = -ax;
//	}
//	if (vx < -0.05)
//	{
//		ax = -ax;
//	}
//	vy += ay * dt;
//	vx += ax * dt;
//
//	CGameObject::Update(dt, coObjects);
//	CCollision::GetInstance()->Process(this, dt, coObjects);
//}
//
//
//void CLeaf::Render()
//{
//	CSprites::GetInstance()->Get(141)->Draw(x, y);
//}
//
//void CLeaf::SetState(int state)
//{
//	CGameObject::SetState(state);
//}

#include "Leaf.h"

CLeaf::CLeaf(float x, float y) : CGameObject(x, y)
{
	ax = 0.00008f;
	ay = 0.00003f;
	vx = 0;
	vy = 0;
	SetState(0);
}

void CLeaf::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - 16 / 2;
	top = y - 14 / 2;
	right = left + 16;
	bottom = top + 14;
}

void CLeaf::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CLeaf::OnCollisionWith(LPCOLLISIONEVENT e)
{

}

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (vx > 0.04)
	{
		ax = -ax;
	}
	if (vx < -0.05)
	{
		ax = -ax;
	}
	vy += ay * dt;
	vx += ax * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CLeaf::Render()
{
	CSprites::GetInstance()->Get(141)->Draw(x, y);
}

void CLeaf::SetState(int state)
{
	CGameObject::SetState(state);
}
