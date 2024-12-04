#pragma once
#include "FlyFish.h"
#include "Component.h"

class BodyComponent : public Component
{
public: 
	ThreeBlade Position;
	TwoBlade Velocity;

	BodyComponent(GameObject* pOwner, const ThreeBlade& pos);

	virtual void Update(float elaspedSec) override;

	virtual void Draw() const override;

	void Move(const TwoBlade direction);
	void Move(const OneBlade direction);
};
