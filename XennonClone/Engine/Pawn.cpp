/*
* Generic Pawn GameObject, HandleEvents() is called every frame from 
* GameEngine.h
************************************************************/

#include "GameEngine.h"
#include "Pawn.h"
#include "SDL.h"
#include "Log.h"

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

void Pawn::HandleEvents(SDL_Event& ev)
{
	if (ev.type == SDL_KEYDOWN)
	{
		LOG_WARNING("Key down");
	}
}