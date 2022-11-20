#pragma once
#include "Component.h"

/*
typedef void(*OnHealthZeroDel)();

template <typename T>
class Delegate
{

};*/

class HealthComponent : public Component
{
public:
	HealthComponent(int maxHealth) : m_MaxHealth{ maxHealth }, m_CurrentHealth{maxHealth} {};

	/* Returns the health left*/
	int TakeDamage(int amount);
	void DealDamage(class HealthComponent* otherHealthComponent, int amount);

	//OnHealthZeroDel OnDie;

private:
	int m_MaxHealth = 100;
	int m_CurrentHealth = 100;
};

