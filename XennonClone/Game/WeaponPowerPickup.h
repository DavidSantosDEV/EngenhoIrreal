#pragma once
#include "BasePickup.h"
class WeaponPowerPickup : public BasePickup
{
public:
	WeaponPowerPickup();

	virtual void Start() override;

protected:
	virtual void CallPickupPower(class IUpgradableShip* other);
};

