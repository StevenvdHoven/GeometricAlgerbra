#include "GameManager.h"


GameManager::GameManager()
{
}

GameManager::~GameManager()
{
	m_Player.release();
}

void GameManager::Init()
{
	m_Player = std::make_unique<Player>();
	
	auto pBody{ std::make_unique<BodyComponent>(ThreeBlade{100,100,0})};
	auto pRenderer{ std::make_unique<RenderComponent>(pBody.get(),Color4f{0,0,1,1},10) };

	auto pPlayerInput{ std::make_unique<PlayerInputComponent>(pBody.get()) };
	pBody->Velocity = TwoBlade{ 100,0,0,0,0,0 };

	auto pPlayerCollider{ std::make_unique<Collider>(pBody.get(),10) };

	m_pComponents.emplace_back(pBody.get());
	m_pComponents.emplace_back(pRenderer.get());
	m_pComponents.emplace_back(pPlayerInput.get());
	m_pComponents.emplace_back(pPlayerCollider.get());

	m_pColliders.emplace_back(pPlayerCollider.get());

	m_Player->AddComponent(std::move(pBody));
	m_Player->AddComponent(std::move(pRenderer));
	m_Player->AddComponent(std::move(pPlayerInput));
	m_Player->AddComponent(std::move(pPlayerCollider));
}

void GameManager::Start()
{
}

void GameManager::Update(float elaspedSec)
{
	for (auto pComponent : m_pComponents)
	{
		pComponent->Update(elaspedSec);
	}

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
				collider->GetOwner()->OnCollision(NULL, collision);
			}
		}
	}
}


