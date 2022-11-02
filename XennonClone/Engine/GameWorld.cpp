/*
* - Works as GameMode on Unreal
* - MUST be implemented by client
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

GameObject* GameWorld::InstantiateObject()
{
	if (m_Engine == nullptr) { return nullptr; }

	GameObject* gameObject = new GameObject();
	m_Engine->AddGameObjectToStack(gameObject);
	gameObject->Start();

	return gameObject;
}

void GameWorld::CallRemoveObjectFromStack(GameObject* gameObject)
{
	if (m_Engine == nullptr) { return; }
	m_Engine->RemoveObjectFromStack(gameObject);
}
