#include "GameManager.h"
#include "EnemyManager.h"
#include "Enemy.h"


GameManager::GameManager()
{
	m_pEnemyManager = std::make_unique<EnemyManager>(this, 1280.f, 720.f);
}

GameManager::~GameManager()
{
	m_pEnemyManager.release();
	m_pGameObjects.clear();
	m_pComponents.clear();
	m_pColliders.clear();
}

void GameManager::Init()
{
	auto pPlayer = std::make_unique<Player>();
	

	AddGameObject(std::move(pPlayer));
}

void GameManager::Start()
{
}

void GameManager::Update(float elaspedSec)
{
	m_pEnemyManager->Update(elaspedSec);
	
	for (auto pComponent : m_pComponents)
	{
		pComponent->Update(elaspedSec);
	}

	CheckDestroyedGameObjects();

	UpdateCollisions(elaspedSec);
}

void GameManager::Draw() const
{
	for (auto pComponent : m_pComponents)
	{
		pComponent->Draw();
	}
}

void GameManager::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	for (auto pComponent : m_pComponents)
	{
		pComponent->ProcessKeyDownEvent(e);
	}
}

void GameManager::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	for (auto pComponent : m_pComponents)
	{
		pComponent->ProcessKeyUpEvent(e);
	}
}

void GameManager::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	for (auto pComponent : m_pComponents)
	{
		pComponent->ProcessMouseMotionEvent(e);
	}
}

void GameManager::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	for (auto pComponent : m_pComponents)
	{
		pComponent->ProcessMouseDownEvent(e);
	}
}

void GameManager::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	for (auto pComponent : m_pComponents)
	{
		pComponent->ProcessMouseUpEvent(e);
	}
}
void GameManager::UpdateCollisions(float elapsedSec)
{
	for (auto collider : m_pColliders)
	{
		Collision worldCollision;
		if (collider->CollidesWithWorld(worldCollision))
		{
			collider->Reflect(worldCollision.normal);
			collider->GetOwner()->OnCollision(NULL, worldCollision);
		}

		for (auto other : m_pColliders)
		{
			if (collider == other) continue;

			Collision collision{};
			if (collider->Collide(other, collision))
			{
				collider->Reflect(collision.normal);
				collider->GetOwner()->OnCollision(other, collision);

				auto pBody{ collider->GetOwner()->GetComponent<BodyComponent>() };
				pBody->Update(elapsedSec);
			}
		}
	}
}

void GameManager::CheckDestroyedGameObjects()
{
	for (auto gameObjectPtr : m_pGameObjectDestroyed)
	{
		EraseGameObject(gameObjectPtr);
	}
	m_pGameObjectDestroyed.clear();
}

void GameManager::EraseGameObject(GameObject* pGameObject)
{
	int length{ static_cast<int>(m_pGameObjects.size()) };
	for (int index{ 0 }; index < length; ++index)
	{
		if (m_pGameObjects[index].get() == pGameObject)
		{
			auto pComponents{ pGameObject->GetComponents() };
			for (auto pComponent : pComponents)
			{
				EraseComponent(pComponent);
			}

			m_pGameObjects[index].release();
			m_pGameObjects.erase(m_pGameObjects.begin() + index);
			return;
		}
	}
}

void GameManager::EraseComponent(Component* pComponent)
{
	for (int index{ 0 }; index < m_pColliders.size(); ++index)
	{
		if (m_pColliders[index] == pComponent)
		{
			m_pColliders.erase(m_pColliders.begin() + index);
			break;
		}
	}

	int length{ static_cast<int>(m_pComponents.size()) };
	for (int index{ 0 }; index < length; ++index)
	{
		if (m_pComponents[index] == pComponent)
		{
			m_pComponents.erase(m_pComponents.begin() + index);
			break;
		}		
	}
}

void GameManager::AddGameObject(std::unique_ptr<GameObject>&& pGameObject)
{
	
	auto components{ pGameObject->GetComponents() };
	for (auto& component : components)
	{	
		component->SetManager(this);
		m_pComponents.emplace_back(component);
	}

	Collider* collider{ pGameObject->GetComponent<Collider>() };
	if (collider != nullptr)
	{
		m_pColliders.emplace_back(collider);
	}
	m_pGameObjects.emplace_back(std::move(pGameObject));
	
}

void GameManager::RemoveGameObject(GameObject* pGameObject)
{
	m_pGameObjectDestroyed.emplace_back(pGameObject);
}


