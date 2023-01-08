#include "PowerUpManager.h"
#include "CompanionPickup.h"
#include "ShieldPickup.h"
#include "WeaponPowerPickup.h"
#include "MathHelper.h"
#include "GameWorld.h"
#include "PhysicsComponent.h"

void PowerUpManager::Update(float delta)
{
	currentTime += delta;
	if (currentTime>=waitTime) {
		currentTime = 0;
		SpawnRandomPickup();
	}
}

Vector2D PowerUpManager::GetRandomPosition()
{
	int pos = MathHelper::GetRandomInRange(0, 3);
	return m_SpawnPositions[pos];
}

void PowerUpManager::SpawnRandomPickup()
{
	BasePickup* bpickup = nullptr;
	int rnd = MathHelper::GetRandomInRange(0, 3);
	switch (rnd)
	{
	case 0:
		bpickup = GameWorld::InstantiateObject<WeaponPowerPickup>();
		break;
	case 1:
		bpickup = GameWorld::InstantiateObject<ShieldPickup>();
		break;
	default:
	case 2:
		bpickup = GameWorld::InstantiateObject<CompanionPickup>();
		break;
	}
	if (bpickup) {
		PhysicsComponent* physc = bpickup->GetComponent<PhysicsComponent>();
		if (physc) {
			Vector2D pos = GetRandomPosition();
			physc->SetPosition(pos);
		}
	}
}
