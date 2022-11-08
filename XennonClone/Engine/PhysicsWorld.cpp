#include "PhysicsWorld.h"
#include "box2d\b2_world.h"
#include "box2d\b2_body.h"

PhysicsWorld* PhysicsWorld::m_Instance{ nullptr };

PhysicsWorld::PhysicsWorld() {
	m_b2World = nullptr;
}

PhysicsWorld::~PhysicsWorld() {
	delete m_b2World;
}

void PhysicsWorld::Init() {
	if (m_Instance) {
		delete this;
	}
	else {
		m_Instance = this;
		m_b2World = new b2World(b2Vec2(0, -1));
	}
}

void PhysicsWorld::SetGravity(Vector2D gravityDir) {
	if (m_b2World) {
		m_b2World->SetGravity(b2Vec2(gravityDir.x, gravityDir.y));
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