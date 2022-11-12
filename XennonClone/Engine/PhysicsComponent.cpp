#include "GameObject.h"
#include "PhysicsComponent.h"
#include "PhysicsWorld.h"
#include "CollisionComponent.h"
#include "box2d\b2_body.h"
#include "box2d\b2_fixture.h"
#include "box2d\b2_circle_shape.h"
#include "box2d\b2_shape.h"

//Vector2D PhysicsComponent::m_LinearVelocity = Vector2D::Zero();

PhysicsComponent::PhysicsComponent() : Component()
{
	
}

PhysicsComponent::~PhysicsComponent()
{
	PhysicsWorld::GetInstance()->DestroyBody(m_storedBody);
}

void PhysicsComponent::Start()
{
	Component::Start();

	m_parentTransform = GetOwnerGameObject()->GetTransform();

	BuildBody();
	BuildDefaultFixture();
}

void PhysicsComponent::SetVelocity(Vector2D velocity)
{	
	m_LinearVelocity = velocity;

	b2Vec2 vec;
	vec.x = m_LinearVelocity.x;
	vec.y = -m_LinearVelocity.y;
	m_storedBody->SetLinearVelocity(vec);
}

void PhysicsComponent::SetGravityScale(float scale)
{
	m_storedBody->SetGravityScale(scale);
}

void PhysicsComponent::AddForce(Vector2D velocity)
{
	//m_storedBody->ApplyLinearImpulse()
}

void PhysicsComponent::ClearVelocity()
{
	m_LinearVelocity = Vector2D::Zero();
	m_storedBody->SetLinearVelocity(b2Vec2(0, 0));
}

Vector2D PhysicsComponent::GetVelocity()
{
	const b2Vec2 vel = m_storedBody->GetLinearVelocity();
	return Vector2D(vel.x,vel.y);
}

bool PhysicsComponent::GetIsBodyAwake()
{
	return m_storedBody->IsAwake();
}

void PhysicsComponent::SetPosition(Vector2D position)
{
	m_storedBody->SetTransform(b2Vec2(position.x,position.y), 0);
	m_parentTransform->SetPosition(position);
}

void PhysicsComponent::SetPosition(float x, float y)
{
	m_storedBody->SetTransform(b2Vec2(x, y), 0);
	m_parentTransform->SetPosition(Vector2D(x,y));
}

void PhysicsComponent::Update(float deltatime)
{
	const b2Vec2 pos = m_storedBody->GetPosition();
	m_parentTransform->SetPosition(Vector2D(pos.x, -pos.y));
}

void PhysicsComponent::ClearDefaultBody()
{
	if (m_bodyFixture) {
		m_storedBody->DestroyFixture(m_bodyFixture);
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
	def.enabled = true;
	
	Vector2D pos = m_OwnerGameObject->GetTransform()->GetPosition();

	def.position = b2Vec2(pos.x, pos.y);


	b2BodyUserData data;

	data.pointer = (uintptr_t)this;

	def.userData = data;

	def.bullet = m_ContinuousCollision;

	m_storedBody = world->CreateBody(def);
}

void PhysicsComponent::BuildDefaultFixture()
{
	if (m_storedBody) 
	{
		b2FixtureDef fixDef;
		fixDef.userData.pointer = (uintptr_t)this;
		fixDef.density = m_density;
		b2CircleShape Circle;
		Circle.m_radius = 2;
		fixDef.shape = &Circle;
		fixDef.isSensor = true;
		fixDef.friction = 0;
		m_storedBody->CreateFixture(&fixDef);
		
	}
}
