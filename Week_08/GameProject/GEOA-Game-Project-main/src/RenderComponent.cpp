#include "RenderComponent.h"
#include "BodyComponent.h"




RenderComponent::RenderComponent(BodyComponent* pBody,const Color4f& color, float radius) noexcept:
	m_pBody(pBody), m_Color{color},m_Radius{radius}
{
}

void RenderComponent::Draw() const
{
	Point2f pos{ ThreeBlade::ToPoint2f(m_pBody->Position) };
	pos.x += WIDTH * 0.5f - 5;
	pos.y += HEIGHT * 0.5f - 5;
	Ellipsef circle{pos,10,10 };
	utils::SetColor(m_Color);
	utils::FillEllipse(circle);
}
