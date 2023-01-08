#include "PlayerBullet.h"
#include "AnimationComponent.h"

PlayerBullet::PlayerBullet()
{
	m_BulletData = BulletData("missile.bmp", 3, 2, 20, "Enemy", 10, 2.f, 800, Vector2D::Up());
	Setup();
	//m_AnimationComponent->PlayAnimation(0, 0, 0, 1, true);
}

void PlayerBullet::Start()
{
	if (!m_AnimationComponent->IsPlayingAnimation(0, 0, 0, 1)) m_AnimationComponent->PlayAnimation(0, 0, 0, 1, true);

	GameObject::Start();
}

