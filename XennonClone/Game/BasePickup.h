#pragma once
#include "GameObject.h"

class BasePickup : public GameObject
{
public:
	BasePickup();
	virtual void Update(float deltaTime) override;
	virtual void OnTriggerEnter(GameObject* other) override;

protected:
	virtual void CallPickupPower(class IUpgradableShip* other) = 0;
	void SetupPickup(const char* spritePath, int spriteColumns, int spriteRows, int colliderRadius);
	class Sprite* m_SpriteComponent = nullptr;
	class AnimationComponent* m_AnimationComponent = nullptr;
	class PhysicsComponent* m_PhysicsComponent = nullptr;
	class CircleCollision* m_Collider = nullptr;
};

