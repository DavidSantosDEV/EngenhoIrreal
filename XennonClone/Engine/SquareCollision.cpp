/*
* - Square Collision Component. Responsible for having a square
* collision shape around GO and calling collision events
* (whether they are trigger or not).
*  - GameObject MUST have PhysicsComponent for collision events be called
************************************************************/

#include "SquareCollision.h"
#include "box2d/b2_fixture.h"
#include "PhysicsComponent.h"
#include "box2d/b2_polygon_shape.h"

b2Fixture* SquareCollision::CreateFixture()
{
	b2FixtureDef fixDef;
	fixDef.userData.pointer = (uintptr_t)this;
	b2PolygonShape shape;

	shape.SetAsBox(m_width, m_Height);
	shape.m_type = b2Shape::e_polygon;

	fixDef.shape = &shape;
	fixDef.isSensor = GetIsTrigger();
	fixDef.friction = GetFriction();

	b2Fixture* fix = m_PhysComp->GetB2Body()->CreateFixture(&fixDef);
	m_PhysComp->ClearDefaultBody();

	return fix;
}

void SquareCollision::UpdateShape(float width, float height)
{
	if (!m_myFixture) {
		return;
	}
	b2PolygonShape* shape = (b2PolygonShape*) m_myFixture->GetShape();
	if (shape) {
		shape->SetAsBox(width, height);
	}
}

void SquareCollision::SetHeight(float height)
{
	if (m_Height!=height) {
		m_Height = height;
		UpdateShape(m_width, m_Height);
	}
}

void SquareCollision::SetWidth(float width)
{
	if (m_width != width) {
		m_width = width;
		UpdateShape(m_width, m_Height);
	}
}

void SquareCollision::SetBounds(Vector2D bounds)
{
	if (Vector2D(m_width,m_Height) != bounds) {
		m_width = bounds.x;
		m_Height = bounds.y;
		UpdateShape(m_width, m_Height);
	}
}

void SquareCollision::SetBounds(float width, float height)
{
	if (m_width != width || m_Height != height) {
		m_width = width;
		m_Height = height;
		UpdateShape(m_width, m_Height);
	}
}

SquareCollision::SquareCollision(PhysicsComponent* physComp, float width, float height)
{
	m_PhysComp = physComp;
	m_width = width;
	m_Height = height;
}
