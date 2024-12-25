#pragma once
#include "Component.h"
#include "FlyFish.h"

class BodyComponent;
class Collider;
struct Collision;

class PlayerInputComponent : public Component
{
public:
	PlayerInputComponent(BodyComponent* pBody);

	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e) override;
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e) override;
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e) override;
	
	void Update(float elapsedSec) override;
	void Draw() const override;

	void OnCollision(Collider* other, const Collision& collision) override;
private:
	static ThreeBlade GetWorldSpaceMouse(ThreeBlade position);

	void CaculateDirection(const ThreeBlade& position, const TwoBlade& velocity);

	BodyComponent* m_pBody;
	ThreeBlade m_PlayerMousePosition;

	bool m_Swing;
	float m_Direction;
	float m_Angle;
	float m_AngleTimer;
	float m_VelocityForce;
	float m_BuildUpEnergy;

	TwoBlade m_RotationLine;
	ThreeBlade m_StartRotationPosition;
	ThreeBlade m_PreviousPosition;
};
