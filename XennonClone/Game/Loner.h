#pragma once
#include "Enemy.h"
class Loner : public Enemy
{
public:
	Loner();

	Vector2D m_MoveDirection = Vector2D::Left();

	virtual void Update(float deltaTime) override;
};

