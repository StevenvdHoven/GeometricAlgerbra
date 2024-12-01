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
	if (e.button == 0)
	{
		m_Swing = true;
		m_Angle = 0;
		m_TempVelocity = m_pBody->Velocity;
		m_pBody->Velocity = OneBlade{};

		Point2f playerPos{ ThreeBlade::ToPoint2f(m_pBody->Position) };
		Point2f mousePos{ ThreeBlade::ToPoint2f(m_PlayerMousePosition) };

		TwoBlade I{ TwoBlade::LineFromPoints(playerPos.x,playerPos.y,1,mousePos.x,mousePos.y,1) };

		
	}
}

void PlayerInputComponent::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	if (e.button == 0)
	{
		m_Swing = false;
	}
}

void PlayerInputComponent::Update(float elapsedSec)
{
	if (m_Swing)
	{

	}
}

void PlayerInputComponent::Draw() const
{
	utils::SetColor(color_blue);
	utils::DrawPoint(ThreeBlade::ToPoint2f(m_PlayerMousePosition), 5.f);
}
