/*
* - Works as GameMode on Unreal
* Start() and Update() are called before any other GameObjects
* - MUST be implemented by client
************************************************************/

#include "GameWorld.h"
#include "GameObject.h"
#include "GameEngine.h"

// Initialize static variables
GameEngine* GameWorld::m_Engine = nullptr;
GameWorld* GameWorld::m_World = nullptr;

GameWorld::GameWorld()
{
}

GameWorld::~GameWorld()
{

}

void GameWorld::Init(GameEngine* myEngine)
{
	if (m_World) {
		delete this;
	}
	else {
		m_Engine = myEngine;
		m_World = this;
	}
}

void GameWorld::DestroyObject(GameObject* Object) {
	Object->SetPendingDestroy();
	m_Engine->AddPendingDestroy(Object);
}

GameObject* GameWorld::FindObjectWithTag(std::string tag)
{
	if (m_Engine) {
		std::vector<GameObject*> objs = m_Engine->GetAllGameObjects();
		for (auto obj : objs) {
			if (obj->HasTag(tag)) {
				return obj;
			}
		}
	}
	return nullptr;
}
