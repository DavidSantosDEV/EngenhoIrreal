#pragma once

#include "CollisionComponent.h"

class CircleCollision : public CollisionComponent
{
protected:
	float m_Radius =100;

protected:
	virtual class b2Fixture* CreateFixture() override;
public:

	CircleCollision();

	CircleCollision(PhysicsComponent* physComp);

	CircleCollision(PhysicsComponent* physComp, float radius);

	void SetRadius(float radius);
	inline float GetRadius() { return m_Radius; }
};

