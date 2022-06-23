#include "GameObject.h"

#define ID_ANI_WOOD 81
#define INTRO_SCREEN_WIDTH 256
#define INTRO_SCREEN_HEIGHT 224
#define INTRO_SCREEN_TIME 2000
#define INTRO_SCREEN_2_TIME 2000
#define INTRO_SCREEN_3_TIME 2000
#define INTRO_SCREEN_1_ID 41
#define INTRO_SCREEN_2_ID 42
#define INTRO_SCREEN_3_ID 43
#define INTRO_SCREEN_4_ID 44
#define ONE_PLAYER_ID 45
#define TWO_PLAYER_ID 46
#define PLAYER_X 144
#define PLAYER_Y 140
class CIntro : public CGameObject {
public:
	int screenSpiteID;
	bool is1Player = true;
	bool isRenderPlayer = false;
	ULONGLONG start_sceen;
	CIntro(float x, float y)
	{
		this->x = x;
		this->y = y;
		screenSpiteID = INTRO_SCREEN_1_ID;
		start_sceen = GetTickCount64();
	}
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void ChangeNumerPlayer();
};