#pragma once
#include "Pawn.h"
class PhysicsComponent;
class CircleCollision;

class Player : public Pawn
{
public:
	Player();
	~Player();
	virtual void HandleEvents() override;

	virtual void Start() override;

	virtual void Update(float deltaTime) override;
private:
	class AnimationComponent* m_AnimationComponent;
	class Sprite* m_SpriteComponent;
	PhysicsComponent* m_physComp;
	CircleCollision* m_Col;
};

