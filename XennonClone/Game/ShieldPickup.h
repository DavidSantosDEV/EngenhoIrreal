#pragma once
#include "BasePickup.h"
class ShieldPickup : public BasePickup
{
public:
	ShieldPickup();
	
protected:
	virtual void CallPickupPower(class IUpgradableShip* other);
};

