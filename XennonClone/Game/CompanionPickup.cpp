#include "CompanionPickup.h"
#include "IUpgradableShip.h"
#include "Sprite.h"
#include "AnimationComponent.h"

CompanionPickup::CompanionPickup()
{
	SetupPickup("png/PULaser.png",4 ,2,25);
	//m_SpriteComponent->SetScale(0.5f);
}
void CompanionPickup::Start()
{
	m_AnimationComponent->PlayAnimation(0,0 ,1 ,3 , true);

}
void CompanionPickup::CallPickupPower(IUpgradableShip* other)
{
	other->AddCompanion();
}
