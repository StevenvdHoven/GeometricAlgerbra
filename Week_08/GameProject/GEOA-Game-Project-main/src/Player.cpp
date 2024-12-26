#include "Player.h"
#include "RenderComponent.h"
#include "BodyComponent.h"
#include "PlayerInputComponent.h"
#include "Collider.h"

Player::Player()
{
	auto pBody{ std::make_unique<BodyComponent>(ThreeBlade{100,100,0}) };
	pBody->Velocity = TwoBlade{ 100,0,0,0,0,0 };

	auto pRenderer{ std::make_unique<RenderComponent>(pBody.get(),Color4f{0,0,1,1},10) };
	auto pPlayerInput{ std::make_unique<PlayerInputComponent>(pBody.get(),pRenderer.get()) };
	auto pPlayerCollider{ std::make_unique<Collider>(pBody.get(),10) };

	AddComponent(std::move(pBody));
	AddComponent(std::move(pRenderer));
	AddComponent(std::move(pPlayerInput));
	AddComponent(std::move(pPlayerCollider));
}

Player::~Player()
{
}
