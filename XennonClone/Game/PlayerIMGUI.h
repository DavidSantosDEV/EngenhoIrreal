#pragma once
#include "GameObject.h"
#include <vector>	
#include "Transform.h"

class UISprite;
class PlayerIMGUI : public GameObject
{
protected:
	std::vector<UISprite*> m_PlayerLives;
	UISprite* m_PlayerHealthBar;
	UISprite* m_HealthbarBack;

	Vector2D startPosLives = Vector2D(20, 350);
public:
	virtual void Start() override;

	void SetPlayerLifeCount(int count);

	void SetPlayerHealth(int current, int max);
};

