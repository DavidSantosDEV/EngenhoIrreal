#pragma once
#include "Enemy.h"

class MetalAsteroid : public Enemy
{
public:
	MetalAsteroid();
	virtual void Update(float deltaTime) override;
private:
	Vector2D m_MovementDirection = Vector2D::Down();

};

