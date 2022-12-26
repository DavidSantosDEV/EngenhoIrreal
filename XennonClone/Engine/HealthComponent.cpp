/*
* - Generic HealthComponent. Supports taking and dealing damage
* - with configurable parameters
* - When Health == 0, OnZeroHealth() method from GameObject is called
************************************************************/

#include "HealthComponent.h"
#include "Log.h"
#include "MathHelper.h"
#include "GameObject.h"


int HealthComponent::TakeDamage(int amount)
{
	if (bIsDead)return 0;
	m_CurrentHealth = MathHelper::ClampInt(m_CurrentHealth - amount, 0, m_MaxHealth);

	OnAnyDamageTaken.Broadcast(amount);
	if (m_CurrentHealth <= 0)
	{

		OnDie.Broadcast();
		bIsDead = true;
	}

	return m_CurrentHealth;
}

void HealthComponent::DealDamage(HealthComponent* otherHealthComponent, int amount)
{
	if (otherHealthComponent == nullptr)
	{
		LOG_ERROR("Health component is nullptr, can't deal damage to them");
		return;
	}

	otherHealthComponent->TakeDamage(amount);
}

void HealthComponent::Heal(int ammount)
{
	m_CurrentHealth = MathHelper::ClampInt(m_CurrentHealth + ammount, 0, m_MaxHealth);
}

void HealthComponent::Revive()
{
	if (!bIsDead)return;
	bIsDead = false;
	m_CurrentHealth = m_MaxHealth;
	OnRevive.Broadcast();
}
