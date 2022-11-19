#pragma once
#include "GameObject.h"
class Explosion : public GameObject
{
public:
	Explosion();

	virtual void OnAnimationEnd() override;

private:
	class Sprite* m_SpriteComponent = nullptr;
	class AnimationComponent* m_AnimationComponent = nullptr;
};

