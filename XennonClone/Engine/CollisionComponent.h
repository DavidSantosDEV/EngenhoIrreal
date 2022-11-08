#pragma once

#include "Component.h"

enum CollisionShape {
	Circle,
	Square,

};
class CollisionComponent : Component
{
protected:
	
public:
	CollisionComponent();
	CollisionComponent(CollisionShape shape);
	~CollisionComponent();
};

