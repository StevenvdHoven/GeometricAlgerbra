#pragma once
#include "Component.h"

class BodyComponent;

class RenderComponent : public Component
{
public:
	RenderComponent(GameObject* pOwner, BodyComponent* pBody) noexcept;

	virtual void Draw() const;

private:

	BodyComponent* m_pBody;
};
