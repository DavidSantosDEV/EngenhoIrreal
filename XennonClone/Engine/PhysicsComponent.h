#pragma once
#include "Component.h"
#include "Transform.h"

//Body type for Box2D physics
enum BodyType {
	Dynamic,
	Kinematic,
	Static,
};

//Rename to Physics Body
class PhysicsComponent : public Component
{
public:
	PhysicsComponent();
	~PhysicsComponent();

	void SetVelocity(Vector2D velocity);
	void AddVelocity(Vector2D velocity);

	void ClearVelocity();

	bool GetIsBodyAwake();

protected:
	void BuildBody();
protected:
	class b2Body* m_storedBody;

	Vector2D m_Position;
	Vector2D m_LinearVelocity;

	BodyType m_BodyType = BodyType::Dynamic;

	float m_gravityScale = 1;
	float m_bodyMass = 1;

	bool m_StartEnabled = true;
	bool m_Enabled = true;
	bool m_FixedRotation = true; //prevent body from rotating
	bool m_ContinuousCollision = false; //prevent tuneling
	bool m_allowSleep = false; //If body can sleep 
};

