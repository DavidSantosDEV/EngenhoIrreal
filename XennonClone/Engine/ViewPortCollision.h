#pragma once
#include "GameObject.h"
class ViewPortCollision : public GameObject
{
	ViewPortCollision();

	virtual void OnTriggerEnter(GameObject* other) override;

	virtual void OnTriggerExit(GameObject* other) override;

};

