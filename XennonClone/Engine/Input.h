#pragma once
class Input
{
public:
	Input();
	void ReceiveEvent(union SDL_Event& ev);
private:
	static union SDL_Event m_Event;
public:
	static union SDL_Event GetInputEvent();
	static int GetRightAxisValue();
	static int GetUpAxisValue();
	static bool IsFireKeyDown();
};

