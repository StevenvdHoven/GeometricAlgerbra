#include "Component.h"
#include "GameObject.h"
#include "Collider.h"
#include "GameManager.h"



Component::Component():
	Component(m_pOwner)
{
}

Component::Component(GameObject* pOwner):
	m_pOwner{pOwner}
{
}

void Component::Update(float elaspedSec)
{
}

void Component::Draw() const
{
}

void Component::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
}

void Component::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
}

void Component::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
}

void Component::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
}

void Component::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
}

void Component::OnCollision(Collider* other, const Collision& collision)
{
}

void Component::SetManager(GameManager* gameManager)
{
	m_pGameManager = gameManager;
}

void Component::SetOwner(GameObject* pOwner)
{
	m_pOwner = pOwner;
}

void Component::Destroy(GameObject* gameObject)
{
	m_pGameManager->RemoveGameObject(gameObject);
}

GameObject* Component::GetOwner()
{
	return m_pOwner;
}
