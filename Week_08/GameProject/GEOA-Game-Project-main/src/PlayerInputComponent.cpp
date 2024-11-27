#include "PlayerInputComponent.h"

PlayerInputComponent::PlayerInputComponent(BodyComponent* pBody) :
	Component(), m_pBody{ pBody }
{
}

void PlayerInputComponent::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
}

void PlayerInputComponent::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	
}

void PlayerInputComponent::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
}
