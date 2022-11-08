#pragma once
#include "Component.h"
#include "Transform.h"

//Body type for Box2D physics
enum BodyType {
	Dynamic,
	Kinematic,
	Static,
};
enum CollisionShape {
	Circle,
	Square,
	Custom,
	None,
};

//Rename to Physics Body
class PhysicsComponent : public Component
{
public:
	PhysicsComponent();
	~PhysicsComponent();

	//Velocity
	void SetVelocity(Vector2D velocity);
	void AddVelocity(Vector2D velocity);
	void ClearVelocity();
	bool GetIsBodyAwake();

	//Shape
	void SetCollisionShape(CollisionShape newShape);

protected:
	void BuildBody();
protected:

	class b2Fixture* m_bodyFixture;
	class b2Body* m_storedBody;

	Vector2D m_Position;
	Vector2D m_LinearVelocity;

	BodyType m_BodyType = BodyType::Dynamic;
	CollisionShape m_ColShape = CollisionShape::None;

	float m_gravityScale = 1;
	float m_bodyMass = 1;

	bool m_StartEnabled = true;
	bool m_Enabled = true;
	bool m_FixedRotation = true; //prevent body from rotating
	bool m_ContinuousCollision = false; //prevent tuneling
	bool m_allowSleep = false; //If body can sleep 
};

