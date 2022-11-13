/*
* Generic Pawn GameObject, HandleEvents() is called every frame from 
* GameEngine.h
************************************************************/

#include "GameEngine.h"
#include "Pawn.h"
#include "SDL.h"
#include "Log.h"
#include "Input.h"

Pawn::Pawn()
{
	GameEngine::AddPawnToStack(this);
}

Pawn::~Pawn()
{
	GameEngine::RemovePawnFromStack(this);
	LOG("Pawn Destroy");
}

void Pawn::Start()
{
	GameObject::Start();

	LOG("Pawn start");
}

void Pawn::Update(float deltaTime)
{
	const float Speed = 130;
	Vector2D movement = (Vector2D(Input::GetRightAxisValue(), -Input::GetUpAxisValue()));
	movement.Normalize();
	//LOG("X: " << movement.x << " " << "Y: "<< movement.y);
	movement *= Speed;
	GetTransform()->AddPosition(movement*deltaTime);

	GameObject::Update(deltaTime);
}

void Pawn::HandleEvents()
{
	//LOG("Horizontal: " << Input::GetRightAxisValue());
	//LOG("Vertical: " << Input::GetUpAxisValue());
	//LOG(Input::IsFireKeyDown());
}