#pragma once
#include "Component.h"
#include "Transform.h"

//Body type for Box2D physics
enum BodyType {
	Dynamic,
	Kinematic,
	Static,
};

class PhysicsComponent : public Component
{
protected:
	class b2Fixture* m_bodyFixture = nullptr;

	class b2Body* m_storedBody = nullptr;
	Transform* m_parentTransform = nullptr;

	Vector2D m_Position;
	Vector2D m_LinearVelocity;
	BodyType m_BodyType = BodyType::Dynamic;

	float m_gravityScale = 1;
	float m_bodyMass = 1;
	float m_density = 1;

	bool m_StartEnabled = true;
	bool m_Enabled = true;
	bool m_FixedRotation = true; //prevent body from rotating
	bool m_ContinuousCollision = true; //prevent tunneling
	bool m_allowSleep = false; //If body can sleep 

protected:
	void BuildBody();
	void BuildDefaultFixture();
public:
	PhysicsComponent() {};
	PhysicsComponent(BodyType type, float GravityScale, float bodyMass, float density);
	~PhysicsComponent();
	
	virtual void OnDestroyed() override;
	virtual void Start() override;

	void SetVelocity(Vector2D velocity);
	void AddForce(Vector2D velocity);
	void ClearVelocity();
	Vector2D GetVelocity();
	bool GetIsBodyAwake();

	void SetGravityScale(float scale);

	void SetPosition(Vector2D position);
	void SetPosition(float x, float y);

	Vector2D GetPosition();

	virtual void Update(float deltatime) override;

	void SetBodyType(BodyType newType);

	b2Body* GetB2Body() { return m_storedBody; }

	void ClearDefaultBody();
};

