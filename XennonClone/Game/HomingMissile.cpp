#include "HomingMissile.h"
#include "GameWorld.h"
#include "Log.h"
#include "PhysicsComponent.h"
#include "AnimationComponent.h"

HomingMissile::HomingMissile()
{
	m_BulletData = BulletData("png/enemybullet.png", 1, 8, 25, "Player", 10, 2.f, 100, Vector2D::Down());
	Setup();
}

void HomingMissile::Start()
{

	if (m_AnimationComponent->IsPlayingAnimation(0, 0, 0, 7) == false)
	{
		m_AnimationComponent->PlayAnimation(0, 0, 0, 7, true);
	}

	GameObject* p = GameWorld::FindObjectWithTag("Player");
	GameObject* parent = GameWorld::FindObjectWithTag("Loner");
	if (p) 
	{
		Vector2D myPos = parent->GetTransform()->GetPosition();
		Vector2D pPos = p->GetTransform()->GetPosition();
		m_BulletData.moveDirection = (pPos - myPos).Normalize();
	}
}
