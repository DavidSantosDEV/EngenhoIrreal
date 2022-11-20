#include "HomingMissile.h"
#include "GameWorld.h"
#include "Sprite.h"
#include "AnimationComponent.h"
#include "PhysicsComponent.h"
#include "Explosion.h"
#include <cmath>
#include "HealthComponent.h"
#include "CircleCollision.h"

HomingMissile::HomingMissile()
{
	AddComponent<Sprite>("missile.bmp", 2, 4, 2.f, 0);
	AddComponent<AnimationComponent>(GetComponent<Sprite>(), false, 8.f);
	AddComponent<PhysicsComponent>(BodyType::Dynamic, 0, 1, 1);
	GetComponent<PhysicsComponent>()->SetGravityScale(0);
	AddComponent<CircleCollision>(GetComponent<PhysicsComponent>(), 10);
	GetComponent<CircleCollision>()->SetIsTrigger(true);
}

void HomingMissile::EnableMissile()
{
	GameObject* p = GameWorld::FindObjectWithTag("Player");
	if (p) {
		Vector2D myPos = m_Transform.GetPosition();
		Vector2D pPos = p->GetTransform()->GetPosition();
		m_TargetDirection =  pPos- myPos;
	}
	else
	{
		m_TargetDirection = Vector2D::Down();
	}
	GetComponent<Sprite>() -> SetFlipY(m_TargetDirection.y > 0);

	//float angle = atan(m_TargetDirection.y / m_TargetDirection.x);
	//GetComponent<Sprite>()->SetRotation(180+angle);	
	GetComponent<PhysicsComponent>()->SetVelocity(m_TargetDirection * missileSpeed);
}

void HomingMissile::OnTriggerEnter(GameObject* other)
{
	if (other->HasTag("Player")) {
		GameWorld::InstantiateObject<Explosion>()->GetTransform()->SetPosition(m_Transform.GetPosition());
		other->GetComponent<HealthComponent>()->TakeDamage(10);
		GameWorld::DestroyObject(this);
	}
}

void HomingMissile::OnBecameHidden()
{
	GameWorld::DestroyObject(this);
}
