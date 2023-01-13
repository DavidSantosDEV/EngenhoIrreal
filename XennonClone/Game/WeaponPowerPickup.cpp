#include "WeaponPowerPickup.h"
#include "IUpgradableShip.h"
#include "AnimationComponent.h"

WeaponPowerPickup::WeaponPowerPickup()
{
	SetupPickup("PUMissil.bmp", 4, 2, 25);
}

void WeaponPowerPickup::Start()
{
	m_AnimationComponent->PlayAnimation(0, 0, 2, 4,true);
}

void WeaponPowerPickup::CallPickupPower(class IUpgradableShip* other)
{
	other->UpgradeWeaponPower();
}
