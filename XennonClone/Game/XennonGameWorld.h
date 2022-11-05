#pragma once
#include "GameWorld.h"

class XennonGameWorld : public GameWorld
{
protected:
	class GameObject* obj;
	// Inherited via GameWorld
	virtual void Start() override;
	virtual void Update() override;
};

