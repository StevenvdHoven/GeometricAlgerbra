#pragma once
#include "Component.h"
#include <iostream>
#include <vector>

class Collider;
struct Collision;

class GameObject
{

public:
	GameObject();
	virtual ~GameObject();

	void AddComponent(std::unique_ptr<Component>&& pComponent);
	virtual void OnCollision(Collider* other, const Collision& collision);

	template<typename ComponentType>
	void RemoveComponent();


	template<typename ComponentType>
	ComponentType* GetComponent();

	template<typename ComponentType>
	bool HasComponent();


private:
	std::vector<std::unique_ptr<Component>> m_Components;
};

template<typename ComponentType>
inline void GameObject::RemoveComponent()
{
	for (int index{ 0 }; index < m_Components.size(); ++index)
	{
		ComponentType* type{ dynamic_cast<ComponentType>(m_Components[index].get())};
		if (type != nullptr)
		{
			m_Components.erase(m_Components.begin() + index);
			return;
		}
	}
}

template<typename ComponentType>
inline ComponentType* GameObject::GetComponent()
{
	for (auto& pComponent : m_Components)
	{
		ComponentType* type{ dynamic_cast<ComponentType>(pComponent.get()) };
		if (type != nullptr) return type;
	}
	return nullptr;
}

template<typename ComponentType>
inline bool GameObject::HasComponent()
{
	for (auto& pComponent : m_Components)
	{
		ComponentType* type{ dynamic_cast<ComponentType>(pComponent.get()) };
		if (type != nullptr) return true;
	}
	return false;
}
