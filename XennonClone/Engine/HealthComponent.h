#pragma once
#include "Component.h"
#include "Delegate.h"

class HealthComponent : public Component
{
public:

	Delegate<int> OnAnyDamageTaken;
	Delegate<> OnRevive;
	Delegate<> OnDie;

	HealthComponent(int maxHealth) : m_MaxHealth{ maxHealth }, m_CurrentHealth{maxHealth} {};

	/* Returns the health left */
	int TakeDamage(int amount);
	void DealDamage(class HealthComponent* otherHealthComponent, int amount);
	void Heal(int ammount);
	void Revive();

	bool GetIsAlive() { return !bIsDead; }

	int GetMaxHealth() { return m_MaxHealth; }
	int GetCurrentHealth() { return m_CurrentHealth; }

private:
	bool bIsDead=false;
	int m_MaxHealth = 100;
	int m_CurrentHealth = 100;
};

