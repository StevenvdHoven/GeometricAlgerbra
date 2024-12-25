#pragma once
#include "GameObject.h"

class ThreeBlade;

class Enemy : public GameObject
{
public:
	Enemy(const ThreeBlade& position);
	virtual ~Enemy();

};
