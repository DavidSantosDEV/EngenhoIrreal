/*
* - Contact listener for box2d collisions. Methods are called 
* - automatically as longs as this is the active listener 
************************************************************/

#include "ContactListener.h"
#include "box2d\b2_contact.h"
#include "CollisionComponent.h"
#include "PhysicsComponent.h"
#include "GameEngine.h"
#include "GameObject.h"

void ContactListener::BeginContact(b2Contact* contact) 
{
	CollisionComponent* const compA = (CollisionComponent*)contact->GetFixtureA()->GetUserData().pointer;
	CollisionComponent* const compB = (CollisionComponent*)contact->GetFixtureB()->GetUserData().pointer;
	if (!compA || !compB)
	{
		return;
	}
	if (!compA->GetIsEnabled() || !compB->GetIsEnabled()) {
		return;
	}
	GameObject* const objA = compA->GetOwnerGameObject();
	GameObject* const objB = compB->GetOwnerGameObject();
	if (&objA == nullptr || &objB == nullptr) {
		return;
	}

	if (objA->IsPendingDestroy() || objB->IsPendingDestroy()) {
		return;
	}
	if (compA->GetIsTrigger() || compB->GetIsTrigger()) {
		objA->OnTriggerEnter(objB);
		objB->OnTriggerEnter(objA);
	}
	else {
		objA->OnBeginCollision(objB);
		objB->OnBeginCollision(objA);
	}
}

void ContactListener::EndContact(b2Contact* contact) 
{
	CollisionComponent* const compA = (CollisionComponent*)contact->GetFixtureA()->GetUserData().pointer;
	CollisionComponent* const compB = (CollisionComponent*)contact->GetFixtureB()->GetUserData().pointer;
	if (compA && compB)
	{
		if (compA->GetIsEnabled() && compB->GetIsEnabled()) {
			GameObject* const objA = compA->GetOwnerGameObject();
			GameObject* const objB = compB->GetOwnerGameObject();
			
			if (&objA == nullptr || &objB == nullptr) {
				return;
			}
			if (objA->IsPendingDestroy() || objB->IsPendingDestroy()) {
				return;
			}
			if (compA->GetIsTrigger() || compB->GetIsTrigger()) {
				objA->OnTriggerExit(objB);
				objB->OnTriggerExit(objA);
			}
			else {
				objA->OnEndCollision(objB);
				objB->OnEndCollision(objA);
			}
		}
	}
}
