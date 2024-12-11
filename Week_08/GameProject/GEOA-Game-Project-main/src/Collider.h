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

	ThreeBlade GetPosition();
	float GetRadius();

private:
	float m_Radius;
	BodyComponent* m_pBody;
};
