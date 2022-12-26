#pragma once

#include "BasePickup.h"

class CompanionPickup : public BasePickup
{
public:
	CompanionPickup();
protected:
	virtual void CallPickupPower(class IUpgradableShip* other) override;
};

