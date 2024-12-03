#include "PlayerInputComponent.h"
#include "BodyComponent.h"
#include "utils.h"

PlayerInputComponent::PlayerInputComponent(BodyComponent* pBody) :
	Component(), 
	m_pBody{ pBody },
	m_PlayerMousePosition{},
	m_Swing{false},
	m_Angle{0},
	m_RotationMotor{},
	m_TempVelocity{}
{
}

void PlayerInputComponent::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	if (m_Swing) return;

	m_PlayerMousePosition[0] = e.x;
	m_PlayerMousePosition[1] = e.y;
}

void PlayerInputComponent::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	if (e.button == SDL_BUTTON_LEFT)
	{
		m_Swing = true;
		m_Angle = 0;
		m_TempVelocity = m_pBody->Velocity;
		m_pBody->Velocity = OneBlade{};
		m_StartRotationPosition = m_pBody->Position;

		Point2f playerPos{ ThreeBlade::ToPoint2f(m_pBody->Position) };
		Point2f mousePos{ ThreeBlade::ToPoint2f(m_PlayerMousePosition) };

		m_RotationLine = OneBlade{mousePos.x,1,0,0} ^ OneBlade{mousePos.y,0,1,0};
		m_RotationLine.Normalize();
	}
}

void PlayerInputComponent::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	if (e.button == SDL_BUTTON_LEFT)
	{
		m_Swing = false;
		float force{ m_TempVelocity.Norm() };
		
		auto r{ (std::cos(m_Angle * 0.5f) - std::sin(m_Angle * 0.5f)) * m_RotationLine };
		auto result{ r * m_TempVelocity * ~r };
		m_pBody->Velocity = result.Grade1();
		m_pBody->Velocity.Normalize();
		m_pBody->Velocity *= force;

	}
}

void PlayerInputComponent::Update(float elapsedSec)
{
	if (m_Swing)
	{
		// Update the angle
		m_Angle += elapsedSec;

		// Construct the rotor
		auto rotor = (std::cos(m_Angle * 0.5f) - std::sin(m_Angle * 0.5f)) * m_RotationLine;

		// Define translation motors
		auto playerPos = m_pBody->Position; // Already a ThreeBlade
		auto toOrigin = (1 - 0.5f) * playerPos;
		auto backToPosition = (1 + 0.5f) * playerPos;

		// Translate to origin
		auto translatedStart = toOrigin * m_StartRotationPosition * ~toOrigin;

		// Rotate around origin
		auto rotated = rotor * translatedStart * ~rotor;

		// Translate back to the original position
		auto finalPosition = backToPosition * rotated * ~backToPosition;

		// Update the position
		m_pBody->Position = finalPosition.Grade3();
	}
}

void PlayerInputComponent::Draw() const
{
	utils::SetColor(color_blue);
	utils::DrawPoint(ThreeBlade::ToPoint2f(m_PlayerMousePosition), 5.f);
}
