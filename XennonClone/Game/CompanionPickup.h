#pragma once

#include "BasePickup.h"

class CompanionPickup : public BasePickup
{
public:
	CompanionPickup();
	virtual void Start() override;
protected:
	virtual void CallPickupPower(class IUpgradableShip* other) override;
};

