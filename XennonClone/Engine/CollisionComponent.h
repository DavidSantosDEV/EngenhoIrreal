#pragma once

#include "Component.h"


class CollisionComponent : Component
{
protected:
	b2Shape* nShape;
public:
	CollisionComponent();
	~CollisionComponent();
};

