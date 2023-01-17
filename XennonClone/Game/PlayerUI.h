#pragma once
#include "GameObject.h"
#include <vector>
class PlayerUI : public GameObject
{

	class TextRendererComponent* textRenderer;

	std::vector<class Sprite> playerHealthCountSprites;
public:
	virtual void Start() override;

	void SetLifeCount(int count);
};

