#include "BodyComponent.h"
#include "utils.h"

BodyComponent::BodyComponent(GameObject* pOwner,const ThreeBlade& pos):
	Component(pOwner), Position{pos}, Velocity{}
{
}

void BodyComponent::Update(float elaspedSec)
{
	if (Velocity.Norm() > 0)
	{
		OneBlade m{ Velocity };
		m[0] = 0;

		OneBlade n{ Velocity };
		n[0] = n[0] * elaspedSec;

		Motor R = n * m;
		auto result = R * Position * ~R;
		Position = result.Grade3();
	}
}

void BodyComponent::Draw() const
{
	utils::SetColor(color_green);

	const Point2f pos{ ThreeBlade::ToPoint2f(Position) };
	utils::DrawPoint(pos, 10);
}
