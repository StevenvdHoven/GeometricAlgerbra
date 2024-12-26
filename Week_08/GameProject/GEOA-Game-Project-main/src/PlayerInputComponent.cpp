#include "PlayerInputComponent.h"
#include "BodyComponent.h"
#include "RenderComponent.h"
#include "utils.h"
#include "Collider.h"
#include "GameObject.h"
#include "EnemyComponent.h"
#include <cmath>
#include <algorithm>

PlayerInputComponent::PlayerInputComponent(BodyComponent* pBody, RenderComponent* pRenderer):
	m_pBody{ pBody },
	m_pRenderer{ pRenderer },
	m_PlayerMousePosition{},
	m_Swing{false},
	m_RotationSpeed{0},
	m_Direction{1},
	m_Angle{0},
	m_VelocityForce{}
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
		m_VelocityForce = m_pBody->Velocity.VNorm();
		CaculateDirection(m_pBody->Position,m_pBody->Velocity);

		m_pBody->Velocity = TwoBlade{};
		m_StartRotationPosition = m_pBody->Position;

		m_RotationLine = OneBlade{ 0,1,0,0 } ^ OneBlade{ 0,0,1,0 };
		m_BuildUpEnergy = 0;

		auto playerPos{ m_pBody->Position };
		auto mousePosition{ GetWorldSpaceMouse(m_PlayerMousePosition) };

		playerPos[2] = 0;
		mousePosition[2] = 0;
		auto dir{ TwoBlade::LineFromPoints(playerPos,mousePosition) };
		
		CaculateRotationSpeed(dir.Norm());
	}
}

void PlayerInputComponent::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	if (e.button == SDL_BUTTON_LEFT)
	{
		m_Swing = false;

		float xDir{ m_pBody->Position[0] - m_PreviousPosition[0] };
		float yDir{ m_pBody->Position[1] - m_PreviousPosition[1] };
		float magnituded{ std::sqrtf((xDir * xDir) + (yDir * yDir)) };

		xDir /= magnituded;
		yDir /= magnituded;

		TwoBlade velocity{ xDir,yDir,0,0,0,0 };

		float maxedForce{ std::min(m_VelocityForce * (1 + m_BuildUpEnergy),250.f) };
		m_pBody->Velocity = velocity * maxedForce;

		std::cout << "released force " << maxedForce << std::endl;
	}
}

void PlayerInputComponent::Update(float elapsedSec)
{
	if (m_Swing)
	{
		if(m_BuildUpEnergy <= 1) m_BuildUpEnergy += elapsedSec;
		
		
		// Update the angle
		m_Angle += m_Direction * m_RotationSpeed * (1 + m_BuildUpEnergy) * elapsedSec * 90;

		m_PreviousPosition = m_pBody->Position;

		const ThreeBlade origin{ 0,0,0 };

		auto mousePosition{ GetWorldSpaceMouse(m_PlayerMousePosition) }; // Convert Screenspace to World space
		auto relativePosition{ m_StartRotationPosition - mousePosition }; // Get Relative from mousePosition

		float mousePosNorm{ mousePosition.VNorm() };

		

		TwoBlade translationToMouse{ mousePosition[0], mousePosition[1],255 * m_BuildUpEnergy,0,0,0};

		auto translater{ Motor::Translation(translationToMouse.VNorm(),translationToMouse)};
		auto rotor{ Motor::Rotation(m_Angle,m_RotationLine)};

		auto position{ rotor * relativePosition * ~rotor };
		position = translater * position.Grade3() * ~translater;

		// Update the position
		auto result{ position.Grade3() };
		m_pBody->Position = result;
	}
	else
	{
		
		m_pBody->Velocity[2] = -m_pBody->Position[2];
		
	}
	m_pRenderer->SetColor(Color4f{ m_pBody->Position[2] / 255,1,0 ,1 });

}

void PlayerInputComponent::Draw() const
{
	utils::SetColor(Color4f{ 1,1,0,1 });
	Point2f playerPos{ ThreeBlade::ToPoint2f(m_pBody->Position) };
	playerPos.x += 1270.f * 0.5f;
	playerPos.y += 720.f * 0.5f - 5;

	utils::DrawLine(ThreeBlade::ToPoint2f(m_PlayerMousePosition), playerPos);
	
	const Ellipsef ellipse{ ThreeBlade::ToPoint2f(m_PlayerMousePosition) , 200,200 };
	utils::DrawEllipse(ellipse);


	utils::SetColor(color_blue);
	utils::DrawPoint(ThreeBlade::ToPoint2f(m_PlayerMousePosition), 5.f);

	
}

void PlayerInputComponent::OnCollision(Collider* other, const Collision& collision)
{
	if (m_Swing)
	{
		m_Direction *= -1;
	}
	
	if(other != nullptr)
	{
		auto pGameObject{ other->GetOwner() };
		if (pGameObject == nullptr) return;


		auto enemy{ pGameObject->GetComponent<EnemyComponent>()};
		if (enemy != nullptr)
		{
			enemy->TakeDamage(1);
		}
	}
}

ThreeBlade PlayerInputComponent::GetWorldSpaceMouse(ThreeBlade position)
{
	ThreeBlade worldSpaceMouse{ position };
	worldSpaceMouse[0] -= 1270.f * 0.5f;
	worldSpaceMouse[1] -= 720.f * 0.5f;
	return worldSpaceMouse;
}

void PlayerInputComponent::CaculateDirection(const ThreeBlade& position, const TwoBlade& velocity)
{
	const float x{ position[0] };
	const float y{ position[1] };

	const ThreeBlade& mousePos{ GetWorldSpaceMouse(m_PlayerMousePosition) };

	const bool left{ x < mousePos[0] };
	const bool lower{ y < mousePos[1] };

	const bool velocityRight{ velocity[0] > 0 };
	const bool velocityUp{ velocity[1] > 0 };
	const bool horizantalDominant{ std::abs(velocity[0]) > std::abs(velocity[1]) };

	if (left && lower)
	{
		if(horizantalDominant)
			m_Direction = velocityRight ? -1 : 1;
		else
			m_Direction = velocityUp ? 1 : -1;
		
	}
	else if (!left && lower)
	{
		if (horizantalDominant)
			m_Direction = velocityRight ? -1 : 1;
		else
			m_Direction = velocityUp ? -1 : 1;
	}
	else if (left && !lower)
	{
		if (horizantalDominant)
			m_Direction = velocityRight ? 1 : -1;
		else
			m_Direction = velocityUp ? 1 : -1;
	}
	else if (!left && !lower)
	{
		if (horizantalDominant)
			m_Direction = velocityRight ? 1 : -1;
		else
			m_Direction = velocityUp ? -1 : 1;
	}
}

void PlayerInputComponent::CaculateRotationSpeed(float distance)
{
	const float startPercent = 0.1f;

	const float maxDistance = 200.f;

	// Clamp distance to ensure it's non-negative
	distance = std::max(distance, 0.f);

	if (distance <= maxDistance) {
		// Linear interpolation within the maxDistance range
		float normalizedDistance = distance / maxDistance;
		m_RotationSpeed = startPercent + (1.f - normalizedDistance) * 4.f;
	}
	else {
		// Exponential slowdown beyond maxDistance
		float normalizedDistance = (distance - maxDistance) / maxDistance; // Normalize beyond maxDistance
		m_RotationSpeed = startPercent + std::exp(-normalizedDistance) * 0.1f; // Adjust the multiplier (0.5f) for tuning
	}

	// Ensure rotation speed doesn't drop below a minimum
	m_RotationSpeed = std::max(m_RotationSpeed, 0.01f);
	std::cout << "rotation speed: " << m_RotationSpeed << " with distance: " << distance << std::endl;
}
