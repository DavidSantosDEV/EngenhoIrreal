#pragma once
#include "GameObject.h"
#include "Transform.h"

class PlayerBullet : public GameObject
{
public:
	PlayerBullet();
	~PlayerBullet();
	virtual void Update(float deltaTime) override;

	virtual void OnTriggerEnter(GameObject* other) override;

	class PhysicsComponent* GetPhysicsComponent() const { return m_PhysicsComponent; }

private:
	class AnimationComponent* m_AnimationComponent;
	class PhysicsComponent* m_PhysicsComponent = nullptr;
	float m_MoveSpeed = 200.f;

	float m_DestroyTimer = 0.f;

	/* After this seconds, the bullet will be destroyed (due to performance)*/
	float m_AutoDestroyBulletAfter = 4.f;
};

