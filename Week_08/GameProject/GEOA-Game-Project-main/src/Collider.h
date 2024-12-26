#pragma once
#include "Component.h"
#include "BodyComponent.h"

struct Collision
{
	bool collided;
	OneBlade normal;
};

class Collider : public Component
{
public:
	Collider(BodyComponent* pBody,float radius) noexcept;

	virtual void Draw() const;

	bool Collide(Collider* other, Collision& collision);
	bool CollidesWithWorld(Collision& collision);

	void Reflect(const OneBlade& normal);

	ThreeBlade GetPosition() const;
	float GetRadius() const;

private:
	float m_Radius;
	BodyComponent* m_pBody;
};
