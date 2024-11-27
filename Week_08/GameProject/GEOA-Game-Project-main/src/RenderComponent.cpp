#include "RenderComponent.h"
#include "BodyComponent.h"
#include "utils.h"

RenderComponent::RenderComponent(GameObject* pOwner,BodyComponent* pBody) noexcept:
	Component(pOwner),m_pBody(pBody)
{
}

void RenderComponent::Draw() const
{
	Ellipsef circle{ ThreeBlade::ToPoint2f(m_pBody->Position),10,10 };
	utils::SetColor(color_green);
	utils::DrawEllipse(circle);
}
