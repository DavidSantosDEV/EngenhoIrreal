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

	std::string GetNumberFormated(int num);

public:
	virtual void Start() override;

	void SetCurrentScore(int Score);

	void SetHighScore(int Score);
};

