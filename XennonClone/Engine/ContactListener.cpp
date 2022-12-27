/*
* - Contact listener for box2d collisions. Methods are called 
* - automatically as longs as this is the active listener 
************************************************************/

#include "ContactListener.h"
#include "box2d\b2_contact.h"
#include "CollisionComponent.h"
#include "PhysicsComponent.h"
#include "GameEngine.h"
#include <mutex>
#include "GameObject.h"

bool ContactListener::IsValidObject(GameObject* objA, GameObject* objB)
{
	if (objA == nullptr || objB == nullptr) {
		return false;
	}
	if (objA->IsPendingDestroy() || objB->IsPendingDestroy()) {
		return false;
	}
	return true;
}

bool ContactListener::IsValidComponent(CollisionComponent* compA, CollisionComponent* compB)
{
	if (!compA || !compB)
	{
		return false;
	}
	if (compA->GetIsPendingKill() || compB->GetIsPendingKill())return false;
	if (!compA->GetIsCollisionEnabled() || !compB->GetIsCollisionEnabled()) {
		return false;
	}
	return true;
}

void ContactListener::BeginContact(b2Contact* contact)
{
	CollisionComponent* const compA = (CollisionComponent*)contact->GetFixtureA()->GetUserData().pointer;
	CollisionComponent* const compB = (CollisionComponent*)contact->GetFixtureB()->GetUserData().pointer;
	
	if (!IsValidComponent(compA,compB)) {
		return;
	}

	GameObject* objA = compA->GetOwnerGameObject();
	GameObject* objB = compB->GetOwnerGameObject();

	if (!IsValidObject(objA,objB)) {
		return;
	}

	if (compA->GetIsTrigger() || compB->GetIsTrigger()) {

		//compA->OnTriggerEnter.Broadcast(objB);
		//compB->OnTriggerEnter.Broadcast(objA);
		AddDel(objA, &compA->OnTriggerEnter, objB);
		AddDel(objB, &compB->OnTriggerEnter, objA);
		//objA->OnTriggerEnter(objB);
		//objB->OnTriggerEnter(objA);
	}
	else {
		
		//compA->OnCollisionEnter.Broadcast(objB);
		//compB->OnCollisionEnter.Broadcast(objA);
		AddDel(objA, &compA->OnCollisionEnter, objB);
		AddDel(objB, &compB->OnCollisionEnter, objA);
		//objA->OnBeginCollision(objB);
		//objB->OnBeginCollision(objA);
	}
}

void ContactListener::EndContact(b2Contact* contact) 
{
	CollisionComponent* const compA = (CollisionComponent*)contact->GetFixtureA()->GetUserData().pointer;
	CollisionComponent* const compB = (CollisionComponent*)contact->GetFixtureB()->GetUserData().pointer;
	if (!IsValidComponent(compA,compB)) {
		return;
	}
	GameObject* objA = compA->GetOwnerGameObject();
	GameObject* objB = compB->GetOwnerGameObject();

	if (!IsValidObject(objA,objB)) {
		return;
	}

	if (compA->GetIsTrigger() || compB->GetIsTrigger()) {
		
		compA->OnTriggerExit.Broadcast(objB);
		compB->OnTriggerExit.Broadcast(objA);
		
		//AddDel(objA, &compA->OnTriggerExit, objB);
		//AddDel(objB, &compB->OnTriggerExit, objA);
		//objA->OnTriggerExit(objB);
		//objB->OnTriggerExit(objA);
	}
	else {

		compA->OnCollisionExit.Broadcast(objB);
		compB->OnCollisionExit.Broadcast(objA);
		//AddDel(objA, &compA->OnCollisionExit, objB);
		//AddDel(objB, &compB->OnCollisionExit, objA);
		//objA->OnEndCollision(objB);
		//objB->OnEndCollision(objA);
	}
}


static std::mutex m_HandlesMutex;
void ContactListener::ExecuteHandles()
{
	std::lock_guard<std::mutex> lock(m_HandlesMutex);
	if (m_delList.size()>0) {
		for (int i = 0; i < m_delList.size(); ++i) {
			m_delList[i].del->Broadcast(m_delList[i].param);
		}
		m_delList.clear();
	}
}

void ContactListener::AddDel(GameObject* caller,Delegate<GameObject*>* newDel, GameObject* param)
{
	
	std::lock_guard<std::mutex> lock(m_HandlesMutex);

	for (int i = 0; i < m_delList.size();++i) {
		if (caller == m_delList[i].original && newDel == m_delList[i].del && m_delList[i].param == param) {
			return;
		}
	}
	m_delList.push_back(DelegateAndParam(caller,newDel,param));
}

