#pragma once
#include "BasePickup.h"
class WeaponPowerPickup : public BasePickup
{
public:
	WeaponPowerPickup();

protected:
	virtual void CallPickupPower(class IUpgradableShip* other);
};

