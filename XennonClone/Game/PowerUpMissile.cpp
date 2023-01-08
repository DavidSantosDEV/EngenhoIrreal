#include "PowerUpMissile.h"
#include "IUpgradableShip.h"
void PowerUpMissile::CallPickupPower(IUpgradableShip* other)
{
	other->UpgradeWeaponPower();
}
