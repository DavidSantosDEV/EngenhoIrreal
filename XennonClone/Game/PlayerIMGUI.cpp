#include "PlayerIMGUI.h"
#include "UISprite.h"
#include "GameWorld.h"

void PlayerIMGUI::Start()
{
	//const char* spritePath, int columns, int rows, Vector2D drawPosition, float scale, Vector2D sheetCoord
	//m_PlayerLives = AddComponent<UISprite>("png/ship1.png", 7, 1, Vector2D(200,200), 1, Vector2D(0,0));

	m_HealthbarBack = AddComponent<UISprite>("png/healthbarback.png", 1, 1, Vector2D(20, 450), 1.5f, Vector2D(0, 0));
	m_PlayerHealthBar = AddComponent<UISprite>("png/Healthbar.png", 1, 1, Vector2D(20, 450), 1.5f, Vector2D(0, 0));
}

void PlayerIMGUI::SetPlayerLifeCount(int count)
{
	if (m_PlayerLives.size()>count) {
		for (int i = m_PlayerLives.size(); i > count;--i) {
			m_PlayerLives.erase(m_PlayerLives.begin() + i);
		}
	}
	else {

	}
}

void PlayerIMGUI::SetPlayerHealth(int current, int max)
{
	m_PlayerHealthBar->SetXFill((float)current / max);
}
