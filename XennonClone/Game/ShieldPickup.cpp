#include "ShieldPickup.h"
#include "IUpgradableShip.h"
#include "AnimationComponent.h"

ShieldPickup::ShieldPickup()
{
	SetupPickup("png/PUShield.png", 4, 2, 25);
}

void ShieldPickup::Start()
{
	m_AnimationComponent->PlayAnimation(0, 0, 1, 3, true);
}

void ShieldPickup::CallPickupPower(class IUpgradableShip* other)
{
	other->UpgradeShields(10);
}

