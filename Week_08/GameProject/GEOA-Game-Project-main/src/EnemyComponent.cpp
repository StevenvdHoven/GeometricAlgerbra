#include "EnemyComponent.h"

EnemyComponent::EnemyComponent(int health):
	m_Health{health}
{
}

void EnemyComponent::TakeDamage(int dmg)
{
	m_Health -= dmg;
	if (m_Health <= 0)
	{
		Destroy(m_pOwner);
	}
}
