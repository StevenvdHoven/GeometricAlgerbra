#pragma once
#include <vector>

class Enemy;
class GameManager;

class EnemyManager
{
public:
	EnemyManager(GameManager* pGameManager,int width, int height);
	~EnemyManager();

	void Update(float elapsedSec);
	void Draw() const;

	void SpawnEnemy();
	void GetRandomPosition(int& x, int& y);
	
private:
	GameManager* m_pGameManager;

	std::vector<Enemy*> m_SpawnedEnemies;
	int m_MaxEnemies{ 10 };
	float m_Timer{ 0 };
	float m_SpawnRate{5};

	int m_Width;
	int m_Height;

};
