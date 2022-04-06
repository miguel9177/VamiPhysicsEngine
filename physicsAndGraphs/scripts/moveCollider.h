#pragma once
#include"../GameEngine.h"
#include "../ButtonsPressed.h"
class moveCollider
{
public:
	static float speed;
	static Collider* colliderObjectToMove;
	static void Update();
};

