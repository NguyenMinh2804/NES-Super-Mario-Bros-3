#include "Leaf.h"

CLeaf::CLeaf(float x, float y) : CGameObject(x, y)
{
	ax = LEAF_GRAVITY_X;
	ay = LEAF_GRAVITY_Y;
	vx = 0;
	vy = 0;
}

void CLeaf::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - LEAF_BBOX_WIDTH / 2;
	top = y - LEAF_BBOX_HEIGHT / 2;
	right = left + LEAF_BBOX_WIDTH;
	bottom = top + LEAF_BBOX_HEIGHT;
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
	if (vx > MAX_SPEED_RIGHT)
	{
		ax = -ax;
	}
	if (vx < -MAX_SPEED_LEFT)
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
	CSprites::GetInstance()->Get(ID_ANI_LEAF)->Draw(x, y);
}

void CLeaf::SetState(int state)
{
	CGameObject::SetState(state);
}
