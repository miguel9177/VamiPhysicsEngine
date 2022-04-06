#pragma once
#include <vector>
#include "GameObject.h"
//this function will control wich objects receive gravity, or another type of forces
class ForceGenerator 
{
private:
	//this is going to store the amount of gravity force to apply at the objects
	static glm::vec3 gravityForce;
	//this is going to store the amount of flying force to apply at the objects
	static glm::vec3 flyingForce;
	//this is going to store every object to apply gravity force 
	static std::vector<GameObject*> objectsToApplyGravityForce;
	//this is going to store every object to apply force up, just to be able to see things flying XD
	static std::vector<GameObject*> objectsToApplyFlyingForce;

	//this function will loop trough every object and apply the gravity force, its called from the updates objects forces function
	static void ApplyGravityForce();
	//this function will loop trough every object and apply the flying force, its called from the updates objects forces function
	static void ApplyFlyingForce();

public:
	//this is the constructor that will store how much gravity every object stored will receive
	ForceGenerator();
	~ForceGenerator();

	//this functon will be called every frame, and it will all the forces, to every objects assigned to the vectors
	static void UpdateObjectsForces();

	

	//this function will register a new object to receive gravity force
	static void RegisterNewObjectToGravityForce(GameObject* objectToAddGravityForce_);
	//this function will register a new object to receive flying force
	static void RegisterNewObjectToFlyingForce(GameObject* objectToAddGravityForce_);

	//this function will remove an object from the vector array of objects that receive force
	static void RemoveObjectFromReceivingForce(GameObject* objectToRemoveGravityForce_);
	
};

