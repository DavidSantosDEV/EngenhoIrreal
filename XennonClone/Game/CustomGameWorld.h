#pragma once
#include "GameWorld.h"

class CustomGameWorld : public GameWorld
{
	int bananas = 0;
	// Inherited via GameWorld
	virtual void Start() override;
	virtual void Update() override;
};

