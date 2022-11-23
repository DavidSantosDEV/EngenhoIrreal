#pragma once
#include "Component.h"

class ParallaxComponent : public Component
{
public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void OnDestroyed() override;
private:

	float m_Speed = 50.f;

	class Sprite* m_SpriteComponent = nullptr;

public:
	/* The speed the Sprite will move at */
	void SetSpeed(float speed) { m_Speed = speed; }
};

