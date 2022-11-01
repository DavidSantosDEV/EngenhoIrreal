/*
* - Works as a GameMode on Unreal.
* - Start and Update are automatically called from GameEngine.h
* - CLIENT must create this together with the engine
************************************************************/

#include "GameWorld.h"
#include "GameObject.h"
#include "GameEngine.h"
#include "Log.h"

GameWorld::GameWorld()
{
	m_Engine = nullptr;
}

void GameWorld::Init(GameEngine* myEngine) 
{
	m_Engine = myEngine;
}

GameObject* GameWorld::InstantiateObject()
{
	if (m_Engine == nullptr) 
	{ 
		LOG_ERROR("Game Engine is null, no object was instantiated");
		return nullptr; 
	}

	GameObject* newGameObject = new GameObject();
	m_Engine->AddGameObjectToStack(newGameObject);
	newGameObject->Start();
	return newGameObject;
}

void GameWorld::CallRemoveObjectFromStack(GameObject* gameObject)
{
	if (m_Engine == nullptr) 
	{
		LOG_ERROR("Game Engine is null, no object was removed");
		return; 
	}

	m_Engine->RemoveGameObjectFromStack(gameObject);
}

GameWorld::~GameWorld()
{
}
