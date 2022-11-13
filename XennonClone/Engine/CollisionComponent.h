#pragma once

#include "Component.h"


class CollisionComponent : public Component
{
protected:
	class b2Shape* m_baseShape;
	class PhysicsComponent* m_PhysComp;
	class b2Fixture* m_myFixture;

	float m_friction = 1;

	bool m_enabled = true;
	bool m_IsTrigger=false;
	bool m_IsCollisionEnabled = true;

protected:
	//virtual b2Shape* GetBuiltShape() =0;
	b2Fixture* FindMyFixture();

	virtual b2Fixture* CreateFixture();
public:
	CollisionComponent(){};

	CollisionComponent(PhysicsComponent* physical);
	~CollisionComponent();

	virtual void Start() override;

	b2Shape* GetCurrentShape() { return m_baseShape; }

	void SetIsTrigger(bool newVal);

	float GetFriction() { return m_friction; };

	void SetCollisionEnabled(bool bNewEnabled);

	bool GetIsTrigger() { return m_IsTrigger; }
	bool GetIsEnabled() { return m_enabled; }
};

