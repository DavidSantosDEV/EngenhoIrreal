#pragma once
#include "GameObject.h"
class Explosion : public GameObject
{
public:
	Explosion();

	void OnAnimationEnd();

private:
	class Sprite* m_SpriteComponent = nullptr;
	class AnimationComponent* m_AnimationComponent = nullptr;
};

