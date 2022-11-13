#include "Player.h"
#include "Input.h"
#include "Sprite.h"
#include "AnimationComponent.h"

Player::Player()
{
	m_SpriteComponent = &AddComponent<Sprite>("Ship1.bmp", 7, 1, 1.f, 0);
	m_AnimationComponent= &AddComponent<AnimationComponent>(GetComponent<Sprite>(), false, 8.f);
}

Player::~Player()
{
	delete m_SpriteComponent;
	delete m_AnimationComponent;
}

void Player::HandleEvents()
{
	int rightAxisValue = Input::GetRightAxisValue();
	if (rightAxisValue > 0.f)
	{
		//LOG("Right");
		if (!m_AnimationComponent->IsPlayingAnimation(0, 4, 0, 6)) m_AnimationComponent->PlayAnimation(0, 4, 0, 6, false);
	}
	else if (rightAxisValue < 0.f)
	{
		//LOG("Left");
		if (!m_AnimationComponent->IsPlayingAnimation(0,0,0,2)) m_AnimationComponent->PlayAnimation(0, 0, 0, 2, false);
	}
	else
	{
		//LOG("Idle");
		if (!m_AnimationComponent->IsPlayingAnimation(0, 3, 0, 3)) m_AnimationComponent->PlayAnimation(0, 3, 0, 3, true);
	}
}
