#pragma once
#include "GameObject.h"
#include <vector>
class PlayerUI : public GameObject
{

	class TextRendererComponent* m_HighScoreText;
	TextRendererComponent* m_ScoreText;
	TextRendererComponent* m_PlayerName;


	std::vector<class Sprite> playerHealthCountSprites;
public:
	virtual void Start() override;

	void SetLifeCount(int count);

	void SetCurrentScore(int Score);

	void SetHighScore(int Score);
};

