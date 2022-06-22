#pragma once

#include "Scene.h"

class CWorld1KeyHandleEvent : public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CWorld1KeyHandleEvent(LPSCENE s) :CSceneKeyHandler(s) {};
};
