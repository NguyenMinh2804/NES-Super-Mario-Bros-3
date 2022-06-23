#pragma once

#include "GameObject.h"

/*
	Object that triggers scene switching
*/
#define ANI_PORTAL_ID 135
#define PORTAL_FLY_TIME 1000
#define PORTAL_FLY_SPEED 0.1f
class CPortal : public CGameObject
{
	int scene_id;	// target scene to switch to 
	ULONGLONG touch_start;
	float width;
	float height; 
public:
	bool isTouch = false;
	CPortal(float l, float t, float r, float b, int scene_id);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);

	void RenderBoundingBox(void);
	
	int GetSceneId() { return scene_id;  }
	int IsBlocking() { return 1; }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Touch();
};