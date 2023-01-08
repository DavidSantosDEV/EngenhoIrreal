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

void GameObject::RemoveTag(const char* tag)
{
	for (int i = 0; i < m_objectTags.size();++i) {
		if (std::strcmp(tag, m_objectTags[i].c_str()) == 0) {
			m_objectTags.erase(m_objectTags.begin()+i);
		}
	}
}

void GameObject::RemoveTag(std::string tag)
{
	RemoveTag(tag.c_str());
}

void GameObject::SetPendingDestroy()
{
	m_pendingDestroy = true;
	for (auto cpt : m_Components) {
		cpt->SetPendingKill();
	}
}

bool GameObject::IsPendingDestroy()
{
	if (!this) {
		throw 505;
		return true;
	}
	return m_pendingDestroy;
}
