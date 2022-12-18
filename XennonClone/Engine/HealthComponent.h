#pragma once
#include "Component.h"
#include "Delegate.h"

class HealthComponent : public Component
{
public:

	Delegate<> OnHealthZero;

	HealthComponent(int maxHealth) : m_MaxHealth{ maxHealth }, m_CurrentHealth{maxHealth} {};

	/* Returns the health left */
	int TakeDamage(int amount);
	void DealDamage(class HealthComponent* otherHealthComponent, int amount);
	void Heal(int ammount);
private:
	int m_MaxHealth = 100;
	int m_CurrentHealth = 100;
};

