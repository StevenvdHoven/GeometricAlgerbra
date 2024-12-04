#pragma once
#include "Component.h"
#include "FlyFish.h"

class BodyComponent;

class PlayerInputComponent : public Component
{
public:
	PlayerInputComponent(BodyComponent* pBody);

	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e) override;
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e) override;
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e) override;
	
	void Update(float elapsedSec) override;
	void Draw() const override;
private:
	static ThreeBlade GetWorldSpaceMouse(ThreeBlade position);

	BodyComponent* m_pBody;
	ThreeBlade m_PlayerMousePosition;

	bool m_Swing;
	float m_Angle;
	float m_AngleTimer;
	Motor m_RotationMotor;
	TwoBlade m_TempVelocity;
	TwoBlade m_RotationLine;
	ThreeBlade m_StartRotationPosition;
};
