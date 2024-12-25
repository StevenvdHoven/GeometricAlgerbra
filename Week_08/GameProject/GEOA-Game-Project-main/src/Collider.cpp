#include "Collider.h"
#include "utils.h"



Collider::Collider(BodyComponent* pBody, float radius) noexcept:
	m_pBody{ pBody }, m_Radius{ radius }
{
}

void Collider::Draw() const
{
	const float hRadius{ m_Radius * 0.5f };

	Point2f pos{ ThreeBlade::ToPoint2f(m_pBody->Position) };
	pos.x += WIDTH * 0.5f - hRadius;
	pos.y += HEIGHT * 0.5f - hRadius;
	Ellipsef circle{ pos,m_Radius,m_Radius };
	utils::SetColor(color_green);
	utils::DrawEllipse(circle);

	utils::DrawPoint(pos.x, pos.y, 1);
}

bool Collider::Collide(Collider* other, Collision& collision)
{
	const ThreeBlade& position{ m_pBody->Position };
	const ThreeBlade& otherPosition{ other->GetPosition() };

	const TwoBlade lineBetweenPoints{ TwoBlade::LineFromPoints(position,otherPosition)};
	const float totalRadius{ m_Radius + other->GetRadius() };

	const float distance{ lineBetweenPoints.Norm() };

	const bool collided{ distance <= totalRadius };
	collision.collided = collided;

	if (collided)
	{
		collision.normal = !(lineBetweenPoints ^ OneBlade{-1,0,0,0});
	}

	return collided;
}

bool Collider::CollidesWithWorld(Collision& collision)
{
	const float hWidth{ WIDTH * 0.5f };
	const float hHeight{ HEIGHT * 0.5f };

	const float x{ m_pBody->Position[0] };
	const float y{ m_pBody->Position[1] };

	OneBlade normal{ 0,0,0,0 };

	const bool xLower{ (x - m_Radius) <= -hWidth };
	const bool xHigher{ (x + m_Radius) >= hWidth };

	if (xLower || xHigher)
	{
		normal[1] = xLower ? 1 : -1;
	}
	
	const bool yLower{ (y - m_Radius) <= -hHeight };
	const bool yHigher{ (y + m_Radius) >= hHeight };

	if (yLower || yHigher)
	{
		normal[2] = yLower ? 1 : -1;
	}

	
	collision.normal = normal.Normalized();

	const bool collided{ xLower || xHigher || yLower || yHigher };
	collision.collided = collided;
	return collided;
}

void Collider::Reflect(const OneBlade& normal)
{
	const TwoBlade& velocity{ m_pBody->Velocity };
	m_pBody->Velocity = (normal * velocity * ~normal).Grade2();
}

ThreeBlade Collider::GetPosition()
{
	return m_pBody->Position;
}

float Collider::GetRadius()
{
	return m_Radius;
}
