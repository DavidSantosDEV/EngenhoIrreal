#include "Player.h"
#include "Input.h"
#include "Sprite.h"
#include "AnimationComponent.h"
#include "GameWorld.h"
#include "PlayerBullet.h"

Player::Player()
{
	m_SpriteComponent = AddComponent<Sprite>("Ship1.bmp", 7, 1, 1.f, 1);
	m_AnimationComponent = AddComponent<AnimationComponent>(GetComponent<Sprite>(), false, 8.f);
}

Player::~Player()
{
	delete m_SpriteComponent;
	delete m_AnimationComponent;
}

void Player::HandleEvents()
{
	Pawn::HandleEvents();

	if (Input::IsFireKeyDown() && m_ShotsTimer >= m_FireRate)
	{
		GameWorld::InstantiateObject<PlayerBullet>()->GetTransform()->SetPosition(CalculateFirePosition());
		m_ShotsTimer = 0.f;
	}
}

void Player::Update(float deltaTime)
{
	m_ShotsTimer += deltaTime;

	Move(deltaTime);
	ChangeAnimationBasedOnInput();

	Pawn::Update(deltaTime);
}

void Player::Move(float deltaTime)
{
	Vector2D movement = (Vector2D(m_InputRightAxis, -m_InputUpAxis));
	movement.Normalize();
	//LOG("X: " << movement.x << " " << "Y: "<< movement.y);
	movement *= m_MoveSpeed;
	GetTransform()->AddPosition(movement * deltaTime);
}

void Player::ChangeAnimationBasedOnInput()
{
	if (m_InputRightAxis > 0.f)
	{
		if (!m_AnimationComponent->IsPlayingAnimation(0, 4, 0, 6)) m_AnimationComponent->PlayAnimation(0, 4, 0, 6, false);
	}
	else if (m_InputRightAxis < 0.f)
	{
		if (!m_AnimationComponent->IsPlayingAnimation(0, 0, 0, 2)) m_AnimationComponent->PlayAnimation(0, 0, 0, 2, false);
	}
	else
	{
		if (!m_AnimationComponent->IsPlayingAnimation(0, 3, 0, 3)) m_AnimationComponent->PlayAnimation(0, 3, 0, 3, true);
	}
}

Vector2D& Player::CalculateFirePosition()
{
	m_FirePosition = m_Transform.GetPosition() + Vector2D(17.f, 0);
	return m_FirePosition;
}

