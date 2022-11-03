#pragma once
#include "GameObject.h"

class Pawn : public GameObject
{
public:
	virtual void Start() override;
	virtual void Update() override;
	virtual void HandleEvents(union SDL_Event& ev);
};

