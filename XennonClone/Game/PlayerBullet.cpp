#include "PlayerBullet.h"

PlayerBullet::PlayerBullet()
{
	m_BulletData = BulletData("missile.bmp", 4, 2, 20, "Enemy", 10, 2.f, 800, Vector2D::Up());
	Setup();
}

