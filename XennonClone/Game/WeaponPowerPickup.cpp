#include "WeaponPowerPickup.h"
#include "IUpgradableShip.h"

WeaponPowerPickup::WeaponPowerPickup()
{
	SetupPickup("png/PUMissil.png", 4, 2, 25);
}

void WeaponPowerPickup::CallPickupPower(class IUpgradableShip* other)
{
	other->UpgradeWeaponPower();
}
