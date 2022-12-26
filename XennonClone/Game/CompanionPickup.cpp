#include "CompanionPickup.h"
#include "IUpgradableShip.h"
#include "Sprite.h"
CompanionPickup::CompanionPickup()
{
	SetupPickup("pod.bmp",6 ,4,25);
	m_SpriteComponent->SetScale(0.5f);
}
void CompanionPickup::CallPickupPower(IUpgradableShip* other)
{
	other->AddCompanion();
}
