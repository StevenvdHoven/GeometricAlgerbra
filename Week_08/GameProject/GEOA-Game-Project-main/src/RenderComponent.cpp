#include "RenderComponent.h"
#include "BodyComponent.h"
#include "utils.h"

#define WIDTH 1280.f
#define HEIGHT 720.f

RenderComponent::RenderComponent(GameObject* pOwner,BodyComponent* pBody) noexcept:
	Component(pOwner),m_pBody(pBody)
{
}

void RenderComponent::Draw() const
{
	Point2f pos{ ThreeBlade::ToPoint2f(m_pBody->Position) };
	pos.x += WIDTH * 0.5f - 5;
	pos.y += HEIGHT * 0.5f - 5;
	Ellipsef circle{pos,10,10 };
	utils::SetColor(color_green);
	utils::DrawEllipse(circle);
	utils::DrawPoint(pos.x, pos.y, 10);
}
