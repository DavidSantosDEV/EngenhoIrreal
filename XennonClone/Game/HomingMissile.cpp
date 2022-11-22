#include "HomingMissile.h"
#include "GameWorld.h"
#include "Log.h"
#include "PhysicsComponent.h"

HomingMissile::HomingMissile()
{
	m_BulletData = BulletData("enemybullet.bmp", 1, 8, 25, "Player", 10, 2.f, 100, Vector2D::Down());
	Setup();
}

void HomingMissile::Start()
{
	GameObject* p = GameWorld::FindObjectWithTag("Player");
	GameObject* parent = GameWorld::FindObjectWithTag("Loner");
	if (p) 
	{
		Vector2D myPos = parent->GetTransform()->GetPosition();
		Vector2D pPos = p->GetTransform()->GetPosition();
		m_BulletData.moveDirection = (pPos - myPos).Normalize();
	}
}
