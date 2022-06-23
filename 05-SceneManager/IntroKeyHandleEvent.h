#pragma once

#include "Scene.h"

class CIntroKeyHandleEvent : public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CIntroKeyHandleEvent(LPSCENE s) :CSceneKeyHandler(s) {};
};
