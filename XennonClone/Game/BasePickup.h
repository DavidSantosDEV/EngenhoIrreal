#pragma once
#include "GameObject.h"

class BasePickup : public GameObject
{
public:
	BasePickup();
	virtual void Update(float deltaTime) override;
	void OnTriggerEnter(GameObject* other);

	virtual void OnBecameHidden() override;
	virtual void OnBecameVisible() override;
protected:

	bool bWasVisible = false;

	virtual void CallPickupPower(class IUpgradableShip* other) = 0;
	void SetupPickup(const char* spritePath, int spriteColumns, int spriteRows, int colliderRadius);
	class Sprite* m_SpriteComponent = nullptr;
	class AnimationComponent* m_AnimationComponent = nullptr;
	class PhysicsComponent* m_PhysicsComponent = nullptr;
	class CircleCollision* m_Collider = nullptr;
};

