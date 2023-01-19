#pragma once
#include "GameObject.h"
#include <vector>	
#include "Transform.h"

class UISprite;
class PlayerIMGUI : public GameObject
{
protected:
	UISprite* m_PlayerLifeOne;
	UISprite* m_PlayerLifeTwo;
	UISprite* m_PlayerLifeThree;
	UISprite* m_PlayerHealthBar;
	UISprite* m_HealthbarBack;

	Vector2D startPosLives = Vector2D(20, 430);
public:
	virtual void Start() override;

	void SetPlayerLifeCount(int count);

	void SetPlayerHealth(int current, int max);
};

