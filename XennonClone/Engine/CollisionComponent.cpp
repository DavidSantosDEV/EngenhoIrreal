/*
* - Generic Collision Component. SHOULDN'T be used directly by users
* - Instead use inherited classes such as CircleCollision and SquareCollision
************************************************************/

#include "CollisionComponent.h"
#include "box2d/b2_shape.h"
#include "PhysicsComponent.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_body.h"
#include "Log.h"
#include "box2d/b2_circle_shape.h"

b2Fixture* CollisionComponent::FindMyFixture()
{
	b2Fixture* list = m_PhysComp->GetB2Body()->GetFixtureList();
	while (list != m_myFixture) {
		list = list->GetNext();
		if (!list)
		{
			//Didn't have it for some reason?
			return nullptr;
		}
	}
	return list;
}

b2Fixture* CollisionComponent::CreateFixture()
{
	b2FixtureDef fixDef;
	fixDef.userData.pointer = (uintptr_t)this;
	b2CircleShape shape;
	shape.m_radius = 20;
	shape.m_p = b2Vec2(0, 0);
	shape.m_type = b2Shape::e_circle;
	fixDef.shape = &shape;
	fixDef.isSensor = GetIsTrigger();
	fixDef.friction = GetFriction();

	b2Fixture* fix= m_PhysComp->GetB2Body()->CreateFixture(&fixDef);
	m_PhysComp->ClearDefaultBody();
	return fix;
}

CollisionComponent::CollisionComponent(PhysicsComponent* physical)
{
	m_PhysComp = physical;
	m_myFixture = nullptr;
}

void CollisionComponent::Start()
{
	if (m_PhysComp) {
		m_myFixture = CreateFixture();
	}
}

CollisionComponent::~CollisionComponent()
{
	m_PhysComp->GetB2Body()->DestroyFixture(m_myFixture);
	delete m_myFixture;
}

void CollisionComponent::SetIsTrigger(bool newVal)
{
	if (!m_PhysComp) {
		return;
	}
	if (!m_myFixture) {
		return;
	}
	b2Fixture* fix = FindMyFixture();
	if (fix) {
		m_IsTrigger = newVal;
		fix->SetSensor(newVal);
	}
}

void CollisionComponent::SetCollisionEnabled(bool bNewEnabled)
{
	if (m_enabled== bNewEnabled) {
		return;
	}
	b2Fixture* fix = FindMyFixture();
	if (!fix) {
		return;
	}
	if (m_enabled == true) {
		fix->SetSensor(true);
	}
	else {
		fix->SetSensor(false);
	}

	m_enabled = bNewEnabled;
}
