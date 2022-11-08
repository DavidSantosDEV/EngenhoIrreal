#include "ContactListener.h"
#include "box2d\b2_contact.h"
#include "PhysicsComponent.h"
#include "GameObject.h"

void ContactListener::BeginContact(b2Contact* contact) 
{
	void* userData = (void*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	if (userData)
	{
		if (PhysicsComponent* compA = (PhysicsComponent*)userData) {
			GameObject* objA = compA->GetOwnerGameObject();
			userData = (void*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
			if (userData) {
				if (PhysicsComponent* CompB = (PhysicsComponent*)userData) {
					GameObject* objB = CompB->GetOwnerGameObject();

					objA->OnBeginCollision(objA);
					objB->OnBeginCollision(objB);
				}
				
			}
		}
		
		//contact->GetFixtureA()->GetBody()->GetUserData().pointer = (uintptr_t) nullptr;
	}
}

void ContactListener::EndContact(b2Contact* contact) {
	

}
