#include "World1KeyHandleEvent.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

void CWorld1KeyHandleEvent::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_DOWN:
		mario->GoDown();
		break;
	case DIK_UP:
		mario->GoUp();
		break;
	case DIK_RIGHT:
		mario->GoRight();
		break;
	case DIK_LEFT:
		mario->GoLeft();
		break;
	case DIK_S:
		mario->GoPlayScreen();
		break;
	}
}

void CWorld1KeyHandleEvent::OnKeyUp(int KeyCode)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_DOWN:
		break;
	case DIK_UP:
		break;
	case DIK_RIGHT:
		break;
	case DIK_LEFT:
		break;
	case DIK_S:
		break;
	}
}

void CWorld1KeyHandleEvent::KeyState(BYTE* states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();		
}