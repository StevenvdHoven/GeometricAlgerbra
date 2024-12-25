#include "EnemyManager.h"
#include "GameManager.h"
#include "Enemy.h"

EnemyManager::EnemyManager(GameManager* pGameManager,int width, int height):
	m_pGameManager{ pGameManager }, m_Width{width}, m_Height{height}
{
}

EnemyManager::~EnemyManager()
{

}

void EnemyManager::Update(float elapsedSec)
{
	if (m_Timer < m_SpawnRate)
	{
		m_Timer += elapsedSec;
	}
	else
	{
		m_Timer = 0;
		SpawnEnemy();
	}
}

void EnemyManager::Draw() const
{
}

void EnemyManager::SpawnEnemy()
{
	int x, y;
	GetRandomPosition(x, y);

	auto pEnemy = std::make_unique<Enemy>(ThreeBlade{ static_cast<float>(x),static_cast<float>(y),0 });
	m_SpawnedEnemies.emplace_back(pEnemy.get());
	m_pGameManager->AddGameObject(std::move(pEnemy));
}

void EnemyManager::GetRandomPosition(int& x, int& y)
{
	x = (rand() % m_Width + 1) - m_Width * 0.5f;
	y = (rand() % m_Height + 1) - m_Height * 0.5f;
}
