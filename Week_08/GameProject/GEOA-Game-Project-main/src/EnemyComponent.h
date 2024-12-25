#pragma once
#include "Component.h"

class EnemyComponent : public Component
{
public:
	EnemyComponent(int health);

	void TakeDamage(int dmg);

private:
	int m_Health;
};
