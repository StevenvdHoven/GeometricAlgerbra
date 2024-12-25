#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>

struct Collision;

class Collider;
class GameObject;
class GameManager;

class Component
{
public:
	Component();
	Component(GameObject* pOwner);

	Component(const Component& other):
		m_pOwner{other.m_pOwner}
	{
	}

	virtual void Update(float elaspedSec);

	virtual void Draw() const;

	virtual void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
	virtual void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
	virtual void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
	virtual void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e);
	virtual void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e);

	virtual void OnCollision(Collider* other, const Collision& collision);

	void SetManager(GameManager* gameManager);
	void SetOwner(GameObject* pOwner);
	void Destroy(GameObject* gameObject);
	GameObject* GetOwner();
protected:
	GameObject* m_pOwner;
	GameManager* m_pGameManager;
};
