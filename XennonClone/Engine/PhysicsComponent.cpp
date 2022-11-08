#include "GameObject.h"
#include "PhysicsComponent.h"
#include "PhysicsWorld.h"
#include "box2d\b2_body.h"
#include "box2d\b2_fixture.h"
#include "box2d\b2_shape.h"

PhysicsComponent::PhysicsComponent()
{
	BuildBody();
}

PhysicsComponent::~PhysicsComponent()
{
	PhysicsWorld::GetInstance()->DestroyBody(m_storedBody);
}

void PhysicsComponent::SetVelocity(Vector2D velocity)
{

}

void PhysicsComponent::AddVelocity(Vector2D velocity)
{

}

void PhysicsComponent::ClearVelocity()
{

}

bool PhysicsComponent::GetIsBodyAwake()
{
	return m_storedBody->IsAwake();
}

void PhysicsComponent::SetCollisionShape(CollisionShape newShape)
{
	if (m_ColShape == newShape) {
		return;
	}
	
	switch (newShape)
	{
	case None:
		delete m_bodyFixture;
		m_bodyFixture = nullptr;
		break;
	case Circle:
		
		break;
	case Square:
		
		break;
	case Custom:

		break;
	}
}

void PhysicsComponent::BuildBody()
{
	PhysicsWorld* const world = PhysicsWorld::GetInstance();
	if (!world) {
		return;
	}
	b2BodyDef def;

	def.userData.pointer = (uintptr_t)this; //Could be the user?

	switch (m_BodyType)
	{
		break;
	case Kinematic:
		def.type = b2_kinematicBody;
		break;
	case Static:
		def.type = b2_staticBody;
		break;
	case Dynamic:
	default:
		def.type = b2_dynamicBody;
		break;
	}
	def.gravityScale = m_gravityScale;
	def.awake = m_StartEnabled;
	
	Vector2D pos = m_OwnerGameObject->GetTransform()->GetPosition();

	def.position = b2Vec2(pos.x, pos.y);

	def.bullet = m_ContinuousCollision;

	m_storedBody = world->CreateBody(def);
}
