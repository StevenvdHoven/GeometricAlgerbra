#pragma once
#include <iostream>
#include <algorithm>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>
#include <chrono>
#include "utils.h"
#include "structs.h"
#include "FlyFish.h"
#include <vector>

class Player;
class Component;

class GameManager
{
public:
	GameManager();
	~GameManager();
	
	void Init();
	void Start();
	void Update(float elaspedSec);
	void Draw() const;

	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e);
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e);

	

private:
	std::unique_ptr<Player> m_Player;

	std::vector<Component*> m_pComponents;
};
