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
		m_AngleTimer = 0;
		m_TempVelocity = m_pBody->Velocity;
		m_pBody->Velocity = TwoBlade{};
		m_StartRotationPosition = m_pBody->Position;

		m_RotationLine = OneBlade{ 0,1,0,0 } ^ OneBlade{ 0,0,1,0 };
	}
}

void PlayerInputComponent::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	if (e.button == SDL_BUTTON_LEFT)
	{
		m_Swing = false;

		auto rotor{ Motor::Rotation(m_Angle,m_RotationLine) };
		auto result{ rotor * m_TempVelocity * ~rotor };
		m_pBody->Velocity = result.Grade2();

	}
}

void PlayerInputComponent::Update(float elapsedSec)
{
	if (m_Swing)
	{
		// Update the angle
		m_Angle += elapsedSec * 90;

		const ThreeBlade origin{ 0,0,0 };

		auto mousePosition{ GetWorldSpaceMouse(m_PlayerMousePosition) }; // Convert Screenspace to World space
		auto relativePosition{ m_StartRotationPosition - mousePosition }; // Get Relative from mousePosition

		Point2f mousePos{ ThreeBlade::ToPoint2f(mousePosition) };
		float mousePosNorm{ mousePosition.VNorm() };

		TwoBlade translationToMouse{ mousePosition[0], mousePosition[1],0,0,0,0};

		auto translater{ Motor::Translation(translationToMouse.VNorm(),translationToMouse)};
		auto rotor{ Motor::Rotation(m_Angle,m_RotationLine)};

		auto position{ rotor * relativePosition * ~rotor };
		position = translater * position.Grade3() * ~translater;

		// Update the position
		auto result{ position.Grade3() };
		m_pBody->Position = result;

		//OneBlade direction{ mousePosNorm / 2,mousePosition[0] / mousePosNorm, mousePosition[1] / mousePosNorm,0 };
		//m_pBody->Move(direction);
	}
}

void PlayerInputComponent::Draw() const
{
	utils::SetColor(Color4f{ 1,1,0,1 });
	Point2f playerPos{ ThreeBlade::ToPoint2f(m_pBody->Position) };
	playerPos.x += 1270.f * 0.5f;
	playerPos.y += 720.f * 0.5f - 5;

	utils::DrawLine(ThreeBlade::ToPoint2f(m_PlayerMousePosition), playerPos);
	
	utils::SetColor(color_blue);
	utils::DrawPoint(ThreeBlade::ToPoint2f(m_PlayerMousePosition), 5.f);

	
}

ThreeBlade PlayerInputComponent::GetWorldSpaceMouse(ThreeBlade position)
{
	ThreeBlade worldSpaceMouse{ position };
	worldSpaceMouse[0] -= 1270.f * 0.5f;
	worldSpaceMouse[1] -= 720.f * 0.5f;
	return worldSpaceMouse;
}
