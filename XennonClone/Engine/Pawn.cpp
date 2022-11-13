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
	GameObject::Update(deltaTime);
}

void Pawn::HandleEvents()
{
	m_InputRightAxis = Input::GetRightAxisValue();
	m_InputUpAxis = Input::GetUpAxisValue();
}
