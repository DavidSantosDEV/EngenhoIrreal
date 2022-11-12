#include "PhysicsTestActor.h"
#include "Input.h"
#include "Log.h"
#include "CircleCollision.h"
#include "Sprite.h"



PhysicsTestActor::PhysicsTestActor()
{
	AddComponent<Sprite>("drone.bmp", 8, 2, 1.f);
}

void PhysicsTestActor::Start()
{
	physComp = AddComponent<PhysicsComponent>();
	circleCol = AddComponent<CircleCollision>(physComp,20);
	Pawn::Start();
}

void PhysicsTestActor::Update(float deltaTime)
{
	Pawn::Update(deltaTime);
	if (hasInput) {
		const float Speed = 80;
		Vector2D movement = (Vector2D(Input::GetRightAxisValue(), -Input::GetUpAxisValue()));
		movement *= Speed;
		physComp->SetVelocity(movement);
	}
}

void PhysicsTestActor::SetHasInput()
{
	hasInput = true; 
}

void PhysicsTestActor::OnTriggerEnter(GameObject* other)
{
	LOG("bananas")
}
