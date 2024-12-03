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
		OneBlade direction{ Velocity };
		direction[0] = direction[0] * elaspedSec;

		Move(direction);
	}
}

void BodyComponent::Draw() const
{
	utils::SetColor(color_green);

	const Point2f pos{ ThreeBlade::ToPoint2f(Position) };
	utils::DrawPoint(pos, 10);
}

void BodyComponent::Move(const OneBlade direction)
{
	OneBlade m{ direction };
	m[0] = 0;

	OneBlade n{ direction };

	Motor R = n * m;
	auto result = R * Position * ~R;
	Position = result.Grade3();
}
