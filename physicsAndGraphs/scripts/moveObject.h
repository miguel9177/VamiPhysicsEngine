#pragma once
#include "../GameEngine.h"
#include "../ButtonsPressed.h"
//this will move the object current associated with it
class moveObject
{
public:
	static float speed;
	static GameObject *gameObjectToMove;
	static void Update();
};

