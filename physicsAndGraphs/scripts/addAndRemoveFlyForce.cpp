#include "addAndRemoveFlyForce.h"

//this will be true if we are in flying force
bool addAndRemoveFlyForce::isFlyingForce;
//this will store evry object to affect
std::vector<GameObject*> addAndRemoveFlyForce::objectsToControl;


void addAndRemoveFlyForce::Start()
{
	//it will store at the flying force
	isFlyingForce = false;
}

void addAndRemoveFlyForce::Update()
{
	//if we click f add graviot or flying force depending on the current force
	if (ButtonsPressed::keys['f'] || ButtonsPressed::keys['F'])
	{
		if (isFlyingForce)
			AddGravityForce();
		else
			AddFlyingForce();
	}

}

//add an object to be affected
void addAndRemoveFlyForce::AddObjects(GameObject* objectToAdd)
{
	objectsToControl.push_back(objectToAdd);
}

//this will go trough every object and add flyiung force
void addAndRemoveFlyForce::AddFlyingForce()
{
	for (int i = 0; i < objectsToControl.size(); i++)
	{
		ForceGenerator::RemoveObjectFromReceivingForce(objectsToControl[i]);
		ForceGenerator::RegisterNewObjectToFlyingForce(objectsToControl[i]);
	}
	isFlyingForce = true;
}
//this will go trough every object and add Gravity force
void addAndRemoveFlyForce::AddGravityForce()
{
	for (int i = 0; i < objectsToControl.size(); i++)
	{
		ForceGenerator::RemoveObjectFromReceivingForce(objectsToControl[i]);
		ForceGenerator::RegisterNewObjectToGravityForce(objectsToControl[i]);
	}
	isFlyingForce = false;
}


