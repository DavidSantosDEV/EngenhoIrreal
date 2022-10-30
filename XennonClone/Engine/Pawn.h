#pragma once
#include "GameObject.h"

class Pawn : public GameObject
{
public:
	virtual void HandleEvents(union SDL_Event& ev);
};

