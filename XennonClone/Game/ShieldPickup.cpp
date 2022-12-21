#include "ShieldPickup.h"
#include "IUpgradableShip.h"

ShieldPickup::ShieldPickup()
{
	SetupPickup("PUShield.bmp", 4, 2, 25);
}

void ShieldPickup::CallPickupPower(class IUpgradableShip* other)
{
	other->UpgradeShields(10);
}

