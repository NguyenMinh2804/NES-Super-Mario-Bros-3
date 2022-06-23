#include "Portal.h"
#include "Game.h"
#include "Textures.h"

CPortal::CPortal(float l, float t, float r, float b, int scene_id)
{
	this->scene_id = scene_id;
	x = l;
	y = t;
	width = r - l;
	height = b - t;
	vy = 0;
	touch_start = -1;
}

void CPortal::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	CGame::GetInstance()->Draw(x - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CPortal::Render()
{
	CAnimations::GetInstance()->Get(ANI_PORTAL_ID)->Render(x, y, isTouch ? true : false);
	//RenderBoundingBox();
}

void CPortal::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - width / 2;
	t = y - height / 2;
	r = x + width / 2;
	b = y + height / 2;
}

void CPortal::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isTouch)
	{
		y += vy * dt;
		if (GetTickCount64() - touch_start > PORTAL_FLY_TIME)
		{
			this->Delete();
		}
	}
}

void CPortal::Touch()
{
	vy = -PORTAL_FLY_SPEED;
	isTouch = true;
	touch_start = GetTickCount64();
}