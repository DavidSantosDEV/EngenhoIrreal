#pragma once
#include "GameWorld.h"

class XennonGameWorld : public GameWorld
{
	// Inherited via GameWorld
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
};

