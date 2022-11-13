#pragma once
#include "Pawn.h"
#include "PhysicsComponent.h"

class PhysicsTestActor : public Pawn
{
public:

	PhysicsComponent* physComp;
	class SquareCollision* circleCol;

	bool hasInput = false;

	PhysicsTestActor();

	virtual void Start() override;
	virtual void Update(float deltaTime) override;

	void SetHasInput();

	virtual void OnTriggerEnter(GameObject* other);
};

