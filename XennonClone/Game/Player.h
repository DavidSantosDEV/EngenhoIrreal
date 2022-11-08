#pragma once
#include "Pawn.h"

class Player : public Pawn
{
public:
	Player();
	virtual void HandleEvents() override;

private:
	class AnimationComponent* m_AnimationComponent;
	class Sprite* m_SpriteComponent;
};

