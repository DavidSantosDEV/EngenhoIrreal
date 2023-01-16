#pragma once
#include "GameObject.h"
#include <vector>
class PlayerUI : public GameObject
{
	std::vector<class Sprite> playerHealthCountSprites;
public:
	virtual void Start() override;

	void SetLifeCount(int count);
};

