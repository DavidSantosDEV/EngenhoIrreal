/*
* Generic GameObject class. EVERY entity in the game should inherit from this 
* Inherited methods and called automatically
* Start() and Update() of the gameobject's components are also called
* automatically
************************************************************/

#include "GameEngine.h"
#include "GameObject.h"
#include "Component.h"
#include <algorithm>
#include "Log.h"

GameObject::GameObject() 
{
	_Transform = Transform(0, 0, 1, 1);
	//GameEngine::AddGameObjectToStack(this);
	LOG("BUILD");
}

GameObject::GameObject(Transform transform) {
	_Transform = transform;
	//GameEngine::AddGameObjectToStack(this);
}
GameObject::GameObject(Vector2D position, Vector2D scale) {
	_Transform = Transform(position, scale);
	//GameEngine::AddGameObjectToStack(this);
}

GameObject::~GameObject() 
{
	LOG("GameObjeect Destroyed");
}

void GameObject::Start()
{
	if (m_WasInitialized) { return; }

	LOG("GameObject Start");
	
	m_WasInitialized = true;
}

void GameObject::Update(float deltaTime)
{
}

void GameObject::OnDestroyed()
{
}

bool GameObject::HasTag(std::string tag) {
	for (std::string str : m_objectTags) {
		if (str == tag) {
			return true;
		}
	}
	return false;
}
bool GameObject::HasTag(const char* tag) {
	for (std::string str : m_objectTags) {
		if (std::strcmp(tag, str.c_str()) == 0) {
			return true;
		}
	}
	return false;
}

void GameObject::AddTag(const char* tag) {
	m_objectTags.push_back(tag);
}
