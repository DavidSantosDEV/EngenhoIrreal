#include "MediumBullet.h"
#include "AnimationComponent.h"

MediumBullet::MediumBullet()
{
	m_BulletData = BulletData("missile.bmp", 3, 2, 20, "Enemy", 10, 2.f, 100, Vector2D::Up());
	Setup();
}

void MediumBullet::Start()
{
	m_AnimationComponent->PlayAnimation(1, 0, 1, 1, true);
}
