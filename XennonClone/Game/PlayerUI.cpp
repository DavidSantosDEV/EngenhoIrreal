#include "PlayerUI.h"
#include "TextRendererComponent.h"
#include <sstream>
#include <iomanip>

void PlayerUI::Start()
{
	m_HighScoreText = AddComponent<TextRendererComponent>("Player Health: '", 1.f, Vector2D(225, 20), "png/font8x8.png");
	m_HighScoreText->SetText("Player Score: 100'00");

	m_PlayerName = AddComponent<TextRendererComponent>("Player One", 1.f, Vector2D(10, 20), "png/font8x8.png");
	m_ScoreText = AddComponent<TextRendererComponent>("0000000000", 1.f, Vector2D(10, 50), "png/font16x16.png");
}

void PlayerUI::SetLifeCount(int count)
{

}

void PlayerUI::SetCurrentScore(int Score)
{
	std::stringstream ss;
	ss << std::setw(10) << std::setfill('0') << Score;
	std::string s = ss.str();
	m_ScoreText->SetText(s);
}

void PlayerUI::SetHighScore(int Score)
{
	std::stringstream ss;
	ss << std::setw(10) << std::setfill('0') << Score;
	std::string s = ss.str();
	m_HighScoreText->SetText("High Score: " + s);
}
