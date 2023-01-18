#include "HeavyBullet.h"
#include "AnimationComponent.h"

HeavyBullet::HeavyBullet()
{
	m_BulletData = BulletData("png/missile.png", 3, 2, 40, "Enemy", 10, 2.f, 100, Vector2D::Up());
	Setup();
}

void HeavyBullet::Start()
{
	m_AnimationComponent->PlayAnimation(2, 0, 2, 1, true);
}
