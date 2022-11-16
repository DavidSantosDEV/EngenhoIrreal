/*
* Generic GameObject(), Update() called every frame from GameEngine.h
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
	m_Transform = Transform(0, 0, 1, 1);
	GameEngine::AddGameObjectToStack(this);
	LOG("BUILD");
}

GameObject::GameObject(Transform transform) {
	m_Transform = transform;
	GameEngine::AddGameObjectToStack(this);
}
GameObject::GameObject(Vector2D position, Vector2D scale) {
	m_Transform = Transform(position, scale);
	GameEngine::AddGameObjectToStack(this);
}

GameObject::~GameObject() 
{
	/*for (auto c : m_Components) {
		delete c.get();
	}*/
	//GameEngine::RemoveGameObjectFromStack(this);
	LOG("DESTROY");
}

void GameObject::Start()
{
	if (m_WasInitialized) { return; }

	LOG("GO Start");
	/*
	std::for_each(
		m_Components.begin(),
		m_Components.end(),
		[](std::shared_ptr<Component> cpt) { cpt->Start(); }
	);*/

	m_WasInitialized = true;
}

void GameObject::Update(float deltaTime)
{
}

void GameObject::Destroy()
{
	delete this;
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
