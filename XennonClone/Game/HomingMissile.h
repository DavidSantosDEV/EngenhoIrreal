#pragma once
#include "Bullet.h"
class HomingMissile : public Bullet
{
public:
	HomingMissile();

	virtual void Start() override;
};

