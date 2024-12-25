#include "GameObject.h"
#include "Component.h"
#include "Collider.h"

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

void GameObject::OnCollision(Collider* other, const Collision& collision)
{
	for (auto& component : m_Components)
	{
		component->OnCollision(other, collision);
	}
}

std::vector<Component*> GameObject::GetComponents() const
{
	std::vector<Component*> components{m_Components.size()};
	
	for (int index{0}; index < components.size(); ++index)
	{
		components[index] = m_Components[index].get();
	}

	return components;
}
