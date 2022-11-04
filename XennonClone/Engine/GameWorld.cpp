/*
* - Works as GameMode on Unreal
* - MUST be implemented by client
* Start() and Update() are called before any other GameObjects
************************************************************/

#include "GameWorld.h"
#include "GameObject.h"
#include "GameEngine.h"

// Initialize static variables
GameEngine* GameWorld::m_Engine = nullptr;

GameWorld::GameWorld()
{
}

GameWorld::~GameWorld()
{
		
}

void GameWorld::Init(GameEngine* myEngine)
{
	m_Engine = myEngine;
}
