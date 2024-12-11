#pragma once
#include "Component.h"
#include "utils.h"

class BodyComponent;

class RenderComponent : public Component
{
public:
	RenderComponent(BodyComponent* pBody, const Color4f& color, float radius) noexcept;

	virtual void Draw() const;

private:

	BodyComponent* m_pBody;
	Color4f m_Color;
	float m_Radius;
};
