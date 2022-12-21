#include "WeaponPowerPickup.h"
#include "IUpgradableShip.h"

WeaponPowerPickup::WeaponPowerPickup()
{
	SetupPickup("PUMissil.bmp", 4, 2, 25);
}

void WeaponPowerPickup::CallPickupPower(class IUpgradableShip* other)
{
	other->UpgradeWeaponPower();
}
