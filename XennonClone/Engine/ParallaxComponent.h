#pragma once
#include "Component.h"

class ParallaxComponent : public Component
{
public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;

private:

	float m_Speed = 50.f;

	/* The Sprite Component that this gameObject has */
	class Sprite* m_SpriteComponent = nullptr;

public:
	void SetSpeed(float speed) { m_Speed = speed; }
};

