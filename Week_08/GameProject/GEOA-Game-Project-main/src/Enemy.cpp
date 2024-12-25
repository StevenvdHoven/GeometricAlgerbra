#include "Enemy.h"
#include "BodyComponent.h"
#include "RenderComponent.h"
#include "Collider.h"
#include "EnemyComponent.h"


#define ENEMY_RADIUS 25
#define ENEMY_COLOR Color4f{1,0,0,1}

Enemy::Enemy(const ThreeBlade& position)
{
	auto pBody{ std::make_unique<BodyComponent>(position) };
	auto pRenderer{ std::make_unique<RenderComponent>(pBody.get(),ENEMY_COLOR,ENEMY_RADIUS) };
	auto pCollider{ std::make_unique<Collider>(pBody.get(),ENEMY_RADIUS) };
	auto pEnemyComponent{ std::make_unique<EnemyComponent>(1) };

	AddComponent(std::move(pBody));
	AddComponent(std::move(pRenderer));
	AddComponent(std::move(pCollider));
	AddComponent(std::move(pEnemyComponent));
}

Enemy::~Enemy()
{
	GameObject::~GameObject();
}
