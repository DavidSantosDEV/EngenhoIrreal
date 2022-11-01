#include "GameWorld.h"
#include "GameObject.h"
#include "GameEngine.h"


void GameWorld::Init(GameEngine* myEngine) {
	m_Engine = myEngine;
}

GameWorld::GameWorld()
{
	m_Engine = nullptr;
}

GameWorld::~GameWorld()
{
}

GameObject* GameWorld::InstantiateObject()
{
	if (m_Engine) {
		GameObject* obj = new GameObject();
		m_Engine->AddGameObjectToStack(obj);
		obj->Start();
		return obj;
	}
	return nullptr;
}

void GameWorld::RemoveObject(GameObject* Object)
{
	if (m_Engine) {
		m_Engine->DeleteObject(Object);
	}
}
