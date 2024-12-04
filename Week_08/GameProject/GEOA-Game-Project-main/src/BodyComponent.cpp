#include "BodyComponent.h"
#include "utils.h"

BodyComponent::BodyComponent(GameObject* pOwner,const ThreeBlade& pos):
	Component(pOwner), Position{pos}, Velocity{}
{
}

void BodyComponent::Update(float elaspedSec)
{
	if (Velocity.VNorm() > 0)
	{
		TwoBlade direction{ Velocity };
		direction *= elaspedSec;

		Move(direction);
	}
}

void BodyComponent::Draw() const
{
	
}

void BodyComponent::Move(const TwoBlade direction)
{
	auto translater{ Motor::Translation(direction.VNorm(),direction)};
	Position = (translater * Position * ~translater).Grade3();
}

void BodyComponent::Move(const OneBlade direction)
{
	OneBlade m{ direction };
	m[0] = 0;

	OneBlade n{ direction };

	auto R{ n * m };
	Position = (R * Position * ~R).Grade3();
}
