#pragma once
#include "Component.h"

class BodyComponent;

class PlayerInputComponent : public Component
{
public:
	PlayerInputComponent(BodyComponent* pBody);

	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e) override;
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e) override;
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e) override;

private:


	BodyComponent* m_pBody;
};
