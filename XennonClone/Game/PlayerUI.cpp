#include "PlayerUI.h"
#include "TextRendererComponent.h"
#include <sstream>
#include <iomanip>

std::string PlayerUI::GetNumberFormated(int num)
{
	std::stringstream ss;
	ss << std::setw(10) << std::setfill('0') << num;
	std::string s = ss.str();
	return s;
}

void PlayerUI::Start()
{
	m_HighScoreText = AddComponent<TextRendererComponent>("Player Health: '", 1.f, Vector2D(225, 20), "png/font8x8.png");
	m_HighScoreText->SetText("Player Score: 100'00");

	m_PlayerName = AddComponent<TextRendererComponent>("Player One", 1.f, Vector2D(10, 20), "png/font8x8.png");
	m_ScoreText = AddComponent<TextRendererComponent>("0000000000", 1.f, Vector2D(10, 50), "png/font16x16.png");
}

void PlayerUI::SetCurrentScore(int Score)
{

	m_ScoreText->SetText(GetNumberFormated(Score));
}
void PlayerUI::SetHighScore(int Score)
{
	m_HighScoreText->SetText("High Score: " + GetNumberFormated(Score));
}
