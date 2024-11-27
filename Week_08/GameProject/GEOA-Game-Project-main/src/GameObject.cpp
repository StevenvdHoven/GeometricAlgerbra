#include "GameObject.h"
#include "Component.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
	m_Components.clear();
}

void GameObject::AddComponent(std::unique_ptr<Component>&& pComponent)
{
	pComponent->SetOwner(this);
	m_Components.emplace_back(std::move(pComponent));
}
