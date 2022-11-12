#include "CircleCollision.h"
#include "Transform.h"
#include "PhysicsComponent.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_circle_shape.h"
#include "GameObject.h"

b2Fixture* CircleCollision::CreateFixture()
{
	b2FixtureDef fixDef;
	fixDef.userData.pointer = (uintptr_t)this;
	b2CircleShape shape;
	shape.m_radius = m_Radius;
	shape.m_p = b2Vec2(0, 0);
	shape.m_type = b2Shape::e_circle;
	fixDef.shape = &shape;
	fixDef.isSensor = GetIsTrigger();
	fixDef.friction = GetFriction();
	b2Fixture* fix = m_PhysComp->GetB2Body()->CreateFixture(&fixDef);
	m_PhysComp->ClearDefaultBody();
	return fix;
}

CircleCollision::CircleCollision()
{
}

CircleCollision::CircleCollision(PhysicsComponent* physComp) : CollisionComponent(physComp)
{
	m_PhysComp = physComp;
	m_Radius = 2.f;
}

CircleCollision::CircleCollision(PhysicsComponent* physComp, float radius)
{
	m_PhysComp = physComp;
	m_Radius = radius;
}
