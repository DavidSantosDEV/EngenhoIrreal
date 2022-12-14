/*
* - World where physics bodies live in. 
* - Used to create physics bodies to live inside of it.
* - Bodies created will not have collision detected unless 
* - a CollisionComponent is added after
************************************************************/

#include "PhysicsWorld.h"
#include "box2d\b2_world.h"
#include "ContactListener.h"
#include "box2d\b2_body.h"

PhysicsWorld* PhysicsWorld::m_Instance{ nullptr };


PhysicsWorld::~PhysicsWorld() {
	delete m_b2World;
	delete m_Listener;
}

void PhysicsWorld::Init() {
	if (m_Instance) {
		delete this;
	}
	else {
		m_Instance = this;
		m_Listener = new ContactListener();
		m_b2World = new b2World(b2Vec2(0, -10));
		m_b2World->SetContactListener(m_Listener);
	}
}

void PhysicsWorld::SetGravity(Vector2D gravityDir) {
	if (m_b2World) {
		m_b2World->SetGravity(b2Vec2(gravityDir.x, gravityDir.y));
	}
}

void PhysicsWorld::UpdatePhysics(float delta)
{
	m_b2World->Step(delta,8,8);
	//m_b2World->Step(1.f/60.f, 8, 3);
}

void PhysicsWorld::ExecuteStashedEvents()
{
	if (m_Listener) {
		m_Listener->ExecuteHandles();
	}
}

b2Body* PhysicsWorld::CreateBody(b2BodyDef& def) {

	if (!m_b2World) {
		return nullptr;
	}
	return m_b2World->CreateBody(&def);
}

void PhysicsWorld::DestroyBody(b2Body* body) {
	if (m_b2World) {
		m_b2World->DestroyBody(body);
	}
}