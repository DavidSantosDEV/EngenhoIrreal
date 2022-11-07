#pragma once
#include "Component.h"
class AnimationComponent : public Component
{
public:
	AnimationComponent(class Sprite& spriteComponent, float animationSpeed) :
		m_ParentSpriteComponent{ spriteComponent }, m_AnimationSpeed{animationSpeed} {};

	virtual void Update(float deltatime) override;

private:
	class Sprite& m_ParentSpriteComponent;
	float m_AnimationSpeed = 1.f;
};

