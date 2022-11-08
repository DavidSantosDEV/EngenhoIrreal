#pragma once

#include "Transform.h"

class PhysicsWorld //Manager class for anything related with physics on the world
{
protected:
	static PhysicsWorld* m_Instance;
	
	class b2World* m_b2World;


public:
	PhysicsWorld();
	~PhysicsWorld();

	void Init();

	b2World* GetWorld() { return m_b2World; }

	void SetGravity(Vector2D gravityDir);

	static PhysicsWorld* GetInstance() { return m_Instance; }

	class b2Body* CreateBody(struct b2BodyDef& def);
	void DestroyBody(b2Body* bodyDes);
};

