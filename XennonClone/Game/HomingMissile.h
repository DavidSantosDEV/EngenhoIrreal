#pragma once
#include "GameObject.h"
class HomingMissile : public GameObject
{
protected:
	Vector2D m_TargetDirection;
	float missileSpeed = 400;
public:
	HomingMissile();

	void EnableMissile();

	virtual void OnTriggerEnter(GameObject* other) override;
	virtual void OnBecameHidden() override;
};

