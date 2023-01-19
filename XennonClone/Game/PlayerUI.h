#pragma once
#include "GameObject.h"
#include <vector>
#include <string>


class PlayerUI : public GameObject
{
protected:
	class TextRendererComponent* m_HighScoreText;
	TextRendererComponent* m_ScoreText;
	TextRendererComponent* m_PlayerName;

	std::vector<class Sprite> playerHealthCountSprites;

	std::string GetNumberFormated(int num);

public:


	virtual void Start() override;

	void SetLifeCount(int count);

	void SetCurrentScore(int Score);

	void SetPlayerHealthBar(int current, int max);

	void SetHighScore(int Score);
};

