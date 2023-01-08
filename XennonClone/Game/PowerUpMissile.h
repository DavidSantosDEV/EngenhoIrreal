#pragma once
#include "BasePickup.h"
class PowerUpMissile : public BasePickup
{
protected:
	virtual void CallPickupPower(class IUpgradableShip* other) override;
};

