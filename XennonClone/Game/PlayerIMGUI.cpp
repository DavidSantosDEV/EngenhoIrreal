#include "PlayerIMGUI.h"
#include "UISprite.h"
#include "GameWorld.h"

void PlayerIMGUI::Start()
{
	m_PlayerLifeOne = AddComponent<UISprite>("png/ship1.png", 7, 1, startPosLives, .5f, Vector2D(0, 0));
	m_PlayerLifeTwo = AddComponent<UISprite>("png/ship1.png", 7, 1, startPosLives + Vector2D(40,0), .5f, Vector2D(0, 0));
	m_PlayerLifeThree = AddComponent<UISprite>("png/ship1.png", 7, 1, startPosLives + Vector2D(80,0), .5f, Vector2D(0, 0));;

	m_HealthbarBack = AddComponent<UISprite>("png/healthbarback.png", 1, 1, Vector2D(20, 450), 1.5f, Vector2D(0, 0));
	m_PlayerHealthBar = AddComponent<UISprite>("png/Healthbar.png", 1, 1, Vector2D(20, 450), 1.5f, Vector2D(0, 0));
}

void PlayerIMGUI::SetPlayerLifeCount(int count)
{
	switch (count)
	{
	case 1:
		m_PlayerLifeOne->SetActive(true);
		m_PlayerLifeTwo->SetActive(false);
		m_PlayerLifeThree->SetActive(false);
		break;
	case 2:
		m_PlayerLifeOne->SetActive(true);
		m_PlayerLifeTwo->SetActive(true);
		m_PlayerLifeThree->SetActive(false);
		break;
	case 3:
		m_PlayerLifeOne->SetActive(true);
		m_PlayerLifeTwo->SetActive(true);
		m_PlayerLifeThree->SetActive(true);
		break;
	case 0:
	default:
		m_PlayerLifeOne->SetActive(false);
		m_PlayerLifeTwo->SetActive(false);
		m_PlayerLifeThree->SetActive(false);
		break;
	}

}

void PlayerIMGUI::SetPlayerHealth(int current, int max)
{
	m_PlayerHealthBar->SetXFill((float)current / max);
}
