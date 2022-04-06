#include "ForceGenerator.h"

//THIS IS NEEDED BECAUSE WE DECLARED THIS VARIABLES AS STATIC, AND THEY NEED TO BE DEFIEND ON THE CPP
glm::vec3 ForceGenerator::gravityForce;
glm::vec3 ForceGenerator::flyingForce;
std::vector<GameObject*> ForceGenerator::objectsToApplyFlyingForce;
std::vector<GameObject*> ForceGenerator::objectsToApplyGravityForce;

//the constructor, that takes how much gravity force every object receives
ForceGenerator::ForceGenerator()
{
	//store the amount of gravity that every object using this force generator will receive
	gravityForce = glm::vec3(0,-15.f,0);
	//store the amount of flying force that every object using this force generator will receive
	flyingForce = glm::vec3(0, 1.0f, 0);
}


ForceGenerator::~ForceGenerator()
{   
	
}

//this function will be called every frame and will called the forces functions
void ForceGenerator::UpdateObjectsForces()
{
	//call every forces to apply
	ApplyGravityForce();
	ApplyFlyingForce();
}

//this function will loop trough every object and apply the gravity force, its called from the updates objects forces function
void ForceGenerator::ApplyGravityForce()
{
	//do a loop to add gravity to every object registered to receive gravity
	for (int i = 0; i < objectsToApplyGravityForce.size(); ++i)
	{
		//this will add a gravity force to the particle, so it adds gravity force multiplyed by the Mass
		objectsToApplyGravityForce[i]->ReturnPhysicsBody()->AddForceWithoutRotation(gravityForce * objectsToApplyGravityForce[i]->ReturnPhysicsBody()->ReturnMass());
	}
}

//this function will loop trough every object and apply the flying force, its called from the updates objects forces function
void ForceGenerator::ApplyFlyingForce()
{
	//do a loop to add flying force to every object registered to receive flying
	for (int i = 0; i < objectsToApplyFlyingForce.size(); ++i)
	{
		//this will add a flying force to the particle
		objectsToApplyFlyingForce[i]->ReturnPhysicsBody()->AddForceWithoutRotation(flyingForce);
	}
}

//this function will register a new object to receive gravity, so from now on that object will be affected by gravity
void ForceGenerator::RegisterNewObjectToGravityForce(GameObject* objectToAddGravityForce_)
{
	//add the object received to the objects that receives gravity
	objectsToApplyGravityForce.push_back(objectToAddGravityForce_);
}

//this function will register a new object to receive flying force
void ForceGenerator::RegisterNewObjectToFlyingForce(GameObject* objectToAddFlyingForce_)
{
	//add the object received to the objects that receives flying force
	objectsToApplyFlyingForce.push_back(objectToAddFlyingForce_);
}


//this function will remove an object from the vector array of objects that receive force
void ForceGenerator::RemoveObjectFromReceivingForce(GameObject* objectToRemoveForce_)
{
	//THIS IF AND ELSE WILL REMOVE AN OBJECT FROM RECEIVING FORCE IN THE MOST EFFICIAN MODE I COULD FIND, BY ONLY RUNNING ON FOR, FOR THE 2 FORCES AVAILABLE
	/*i start by checking wich force as more elements (now we know wich .size to use on the for loop), then i need to check if the loop has a size of the current item
	since we dont know if it has, because we could be using the objects to apply gravity force size or the applying force, and they probably have different sizes, if i dont do this checking
	before checking if its the correct gameobject it will give me an error of out of bouds, because i cannot chack if a item exists at an unexisting index*/
	if (objectsToApplyGravityForce.size() >= objectsToApplyFlyingForce.size()) 
	{
		//since the biggest is objects to apply gravity force, we use its size for the loop
		for (int i = 0; i < objectsToApplyGravityForce.size(); i++)
		{
			//if this vector has the gameobject to remove, remove it
			if (objectsToApplyGravityForce[i] == objectToRemoveForce_)
			{
				objectsToApplyGravityForce.erase(objectsToApplyGravityForce.begin() + i);
			}
			//if this vector has more size then the current index (to avoid out of bounds errors), and it has the game object to remove, remove it
			if (objectsToApplyFlyingForce.size()>i && objectsToApplyFlyingForce[i] == objectToRemoveForce_)
			{
				objectsToApplyFlyingForce.erase(objectsToApplyFlyingForce.begin() + i);
			}
		}
	}
	//since objects to aplly flying force is bigger then objects to apply gravity force
	else
	{
		//since the biggest is objects to apply flying force, we use its size for the loop
		for (int i = 0; i < objectsToApplyFlyingForce.size(); i++)
		{
			//if this vector has more size then the current index (to avoid out of bounds errors), and it has the game object to remove, remove it
			if (objectsToApplyGravityForce.size() > i && objectsToApplyGravityForce[i] == objectToRemoveForce_)
			{
				objectsToApplyGravityForce.erase(objectsToApplyGravityForce.begin() + i);
			}
			//if this vector has the gameobject to remove, remove it
			if (objectsToApplyFlyingForce[i] == objectToRemoveForce_)
			{
				objectsToApplyFlyingForce.erase(objectsToApplyFlyingForce.begin() + i);
			}
		}
	}
}

