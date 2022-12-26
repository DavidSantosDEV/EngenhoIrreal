#pragma once
#include "Log.h"

class IUpgradableShip
{
public:
	/* Cannot be pure virtual since a dynamic_cast is performed for this class 
		And c++ does not allow dynamic_cast for pure virtual classes */
	virtual void UpgradeShields(int amountToHeal) { LOG_ERROR(" Forgot to override IUpgradableShip methods") };
	virtual void UpgradeWeaponPower() { LOG_ERROR(" Forgot to override IUpgradableShip methods") };
	virtual void AddCompanion() {};
};
