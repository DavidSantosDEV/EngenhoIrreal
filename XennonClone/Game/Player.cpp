#include "Player.h"
#include "Input.h"
#include "Sprite.h"
#include "PhysicsComponent.h"
#include "CircleCollision.h"
#include "AnimationComponent.h"

Player::Player()
{
	m_SpriteComponent = AddComponent<Sprite>("Ship1.bmp", 7, 1, 1.f, 0);
	m_AnimationComponent= AddComponent<AnimationComponent>(*GetComponent<Sprite>(), false, 8.f);
	m_physComp = AddComponent<PhysicsComponent>();
	m_physComp->SetGravityScale(0);
	m_Col = AddComponent<CircleCollision>(m_physComp, 20);
}

Player::~Player()
{
	delete m_SpriteComponent;
	delete m_AnimationComponent;
	delete m_physComp;
	delete m_Col;
}

void Player::Update(float deltaTime) {
	Pawn::Update(deltaTime);
	const float Speed = 3000;
	Vector2D movement = (Vector2D(Input::GetRightAxisValue(), -Input::GetUpAxisValue()));
	movement.Normalize();
	//LOG("X: " << movement.x << " " << "Y: "<< movement.y);
	movement *= Speed;

	m_physComp->SetVelocity(Vector2D(movement));
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

void Player::Start()
{

	//m_physComp->SetPosition(300, 100);
	//m_physComp->SetGravityScale(1);
}
