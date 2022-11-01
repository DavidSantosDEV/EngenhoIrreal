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

GameObject* GameWorld::InstatianteObject()
{
	if (m_Engine) {
		GameObject* obj = new GameObject(this);
		m_Engine->AddGameObjectToStack(obj);
		obj->Start();
		return obj;
	}
	return nullptr;
}
