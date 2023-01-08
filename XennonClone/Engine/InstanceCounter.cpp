/*
* - Used to check for Memory Leaks. Shows how many GO and 
* Components are currently in the game
************************************************************/

#include "InstanceCounter.h"
#include "Log.h"
#include <vector>
#include "Component.h"
#include "GameObject.h"


static std::vector<class GameObject*> m_objects;
static std::vector<class Component*> m_comps;

int InstanceCounter::ComponentCount = 0;
int InstanceCounter::objectCount = 0;

void InstanceCounter::AddObjectCount(GameObject* other) 
{
	if (!other)return;
	m_objects.push_back(other);
	objectCount++;
}
void InstanceCounter::RemoveObjectCount(GameObject* other) 
{
	if (!other)return;

	objectCount--;

	for (int i = 0; i < m_objects.size(); ++i) {
		if (m_objects[i] == other) {
			m_objects.erase(m_objects.begin() + i);
			return;
		}
	}
}
void InstanceCounter::AddComponentCount(Component* other) 
{
	if (!other)return;
	m_comps.push_back(other);
	ComponentCount++;
}
void InstanceCounter::RemoveComponentCount(Component* other)
{
	if (!other)return;

	ComponentCount--;

	for (int i = 0; i < m_comps.size(); ++i) {
		if (m_comps[i] == other) {
			m_comps.erase(m_comps.begin() + i);
			return;
		}
	}

}

void InstanceCounter::PrintCounts()
{
	LOG("Objects: " << objectCount << std::endl << "Components: " << ComponentCount);
}
