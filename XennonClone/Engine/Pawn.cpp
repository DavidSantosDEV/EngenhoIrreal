/*
* Generic Pawn GameObject, HandleEvents() is called every frame from 
* GameEngine.h
* Should be used for GO that respond to input
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
	/*
	const float Speed = 130;
	Vector2D movement = (Vector2D(Input::GetRightAxisValue(), -Input::GetUpAxisValue()));
	movement.Normalize();
	//LOG("X: " << movement.x << " " << "Y: "<< movement.y);
	movement *= Speed;
	GetTransform()->AddPosition(movement*deltaTime);*/

	GameObject::Update(deltaTime);
}

void Pawn::HandleEvents()
{
	m_InputRightAxis = Input::GetRightAxisValue();
	m_InputUpAxis = Input::GetUpAxisValue();
}