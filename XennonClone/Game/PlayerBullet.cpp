#include "PlayerBullet.h"
#include "Sprite.h"
#include "AnimationComponent.h"

PlayerBullet::PlayerBullet()
{
	AddComponent<Sprite>("missile.bmp", 2, 4, 2.f, 0);
	m_AnimationComponent = &AddComponent<AnimationComponent>(GetComponent<Sprite>(), false, 8.f);
}

PlayerBullet::~PlayerBullet()
{
	delete m_AnimationComponent;
}

void PlayerBullet::Update(float deltaTime)
{
	m_Transform.AddPosition(Vector2D::Up() * m_MoveSpeed * deltaTime);

	// Sprite Animation
	if (!m_AnimationComponent->IsPlayingAnimation(0, 0, 0, 1)) m_AnimationComponent->PlayAnimation(0, 0, 0, 1, true);

	GameObject::Update(deltaTime);
}

