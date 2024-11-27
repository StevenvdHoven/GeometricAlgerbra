#include "GameManager.h"
#include "Player.h"

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
	
	auto pBody{ std::make_unique<BodyComponent>(m_Player.get(),ThreeBlade{100,100,10})};
	auto pRenderer{ std::make_unique<RenderComponent>(m_Player.get(),pBody.get())};

	pBody->Velocity = OneBlade{ 10,1,0,0 };

	m_pComponents.emplace_back(pBody.get());
	m_pComponents.emplace_back(pRenderer.get());

	m_Player->AddComponent(std::move(pBody));
	m_Player->AddComponent(std::move(pRenderer));
}

void GameManager::Start()
{
}

void GameManager::Update(float elaspedSec)
{
	for (auto& pComponent : m_pComponents)
	{
		pComponent->Update(elaspedSec);
	}
}

void GameManager::Draw() const
{
	for (auto& pComponent : m_pComponents)
	{
		pComponent->Draw();
	}
}

void GameManager::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	for (auto& pComponent : m_pComponents)
	{
		pComponent->ProcessKeyDownEvent(e);
	}
}

void GameManager::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	for (auto& pComponent : m_pComponents)
	{
		pComponent->ProcessKeyUpEvent(e);
	}
}

void GameManager::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	for (auto& pComponent : m_pComponents)
	{
		pComponent->ProcessMouseMotionEvent(e);
	}
}

void GameManager::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	for (auto& pComponent : m_pComponents)
	{
		pComponent->ProcessMouseDownEvent(e);
	}
}

void GameManager::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	for (auto& pComponent : m_pComponents)
	{
		pComponent->ProcessMouseUpEvent(e);
	}
}

