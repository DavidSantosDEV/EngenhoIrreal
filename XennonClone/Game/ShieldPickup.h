#pragma once
#include "BasePickup.h"
class ShieldPickup : public BasePickup
{
public:
	ShieldPickup();

	virtual void Start() override;
	
protected:
	virtual void CallPickupPower(class IUpgradableShip* other);
};

