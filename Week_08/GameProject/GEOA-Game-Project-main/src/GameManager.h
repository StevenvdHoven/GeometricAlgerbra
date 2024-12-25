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

#include "Collider.h"
#include "Player.h"
#include "PlayerInputComponent.h"
class Component;
class EnemyManager;

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
	
	void AddGameObject(std::unique_ptr<GameObject>&& pGameObject);
	void RemoveGameObject(GameObject* pGameObject);

private:
	void UpdateCollisions(float elapsedSec);
	void CheckDestroyedGameObjects();
	void EraseGameObject(GameObject* pGameObject);
	void EraseComponent(Component* pComponent);

	std::unique_ptr<EnemyManager> m_pEnemyManager;
	
	std::vector<std::unique_ptr<GameObject>> m_pGameObjects;
	std::vector<GameObject*> m_pGameObjectDestroyed;

	std::vector<Component*> m_pComponents;
	std::vector<Collider*> m_pColliders;
};
