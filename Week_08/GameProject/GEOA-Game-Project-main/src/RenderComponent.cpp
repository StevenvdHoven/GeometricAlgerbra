#include "RenderComponent.h"
#include "BodyComponent.h"




RenderComponent::RenderComponent(BodyComponent* pBody,const Color4f& color, float radius) noexcept:
	m_pBody(pBody), m_Color{color},m_Radius{radius}
{
}

void RenderComponent::Draw() const
{
	const float hRadius{ m_Radius * 0.5f };

	Point2f pos{ ThreeBlade::ToPoint2f(m_pBody->Position) };
	pos.x += WIDTH * 0.5f - hRadius;
	pos.y += HEIGHT * 0.5f - hRadius;
	Ellipsef circle{pos,m_Radius, m_Radius };
	utils::SetColor(m_Color);
	utils::FillEllipse(circle);
}
