#pragma once
#include "../GameEngine.h"
#include "../ButtonsPressed.h"
#include <vector>

//this script will add and remove the flying and gravity force of the objects outside the  pool table, so that i can demonstrate collisions
class addAndRemoveFlyForce
{
private:
	static bool isFlyingForce;
public:
	//this will store the objects to affeect
	static std::vector<GameObject*> objectsToControl;
	static void Start();
	static void Update();
	static void AddObjects(GameObject* objectToAdd);
	static void AddFlyingForce();
	static void AddGravityForce();
};

