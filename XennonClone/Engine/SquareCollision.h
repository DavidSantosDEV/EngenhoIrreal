#pragma once

#include "CollisionComponent.h"
#include "Transform.h"

class SquareCollision : public CollisionComponent
{
protected:
	float m_Height = 1;
	float m_width = 1;

	b2Fixture* CreateFixture() override;
	void UpdateShape(float width, float height);

public:
	inline float GetHeight() { return m_Height; }
	inline float GetWidth() { return m_width; }

	void SetHeight(float height);
	void SetWidth(float width);

	void SetBounds(Vector2D bounds);
	void SetBounds(float width, float height);

	SquareCollision(class PhysicsComponent* physComp, float width, float height);
};

