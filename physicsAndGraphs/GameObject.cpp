#include "GameObject.h"



//constructor that receives nothing, so it sets the particle position to 0, and the mass to 1
GameObject::GameObject()
{
	physicsBody = nullptr;
	
	//color = glm::vec3(0, 0, 0);
	//firstColor = color;
}


/*this will be used for functions that dont inherit from gameobject, to be able to access the physicsbody of the game object, for example on
the ForceGenerator function i need to know wich physicBOdy the objects has, so that i cann add the gravity force to the game object*/
PhysicsBody* GameObject::ReturnPhysicsBody()
{
	return physicsBody;
}

//this will return all of the colliders we are using for this object, its used for example at gameEngine
std::vector<Collider*> GameObject::ReturnColliders()
{
	return collidersOfGameObject;
}

int GameObject::ReturnBodyType()
{
	return bodyTypeOfGameObject;
}

//since som objects dont have access to the collider this functiuon will let for example the game engine to call the draw collider function of this object
void GameObject::CallDrawFunctionFromColliders()
{
	//do a loop trough every collider and draw it
	if (collidersOfGameObject.size() != 0)
	{
		for (int i = 0; i < collidersOfGameObject.size(); i++)
		{
			collidersOfGameObject[i]->Draw();
		}
	}
}

//since som objects dont have access to the collider this functiuon will let for example the game engine to call the setupdraw collider function of this object
void GameObject::CallSetupDrawFunctionFromColliders()
{
	//do a loop trough every collider and setup the drawing
	if (collidersOfGameObject.size() != 0)
	{
		for (int i = 0; i < collidersOfGameObject.size(); i++)
		{
			collidersOfGameObject[i]->SetupDraw();
		}
	}
}

//add a collider to the gameobject, and store withc game object has it, set its position and call the function to setup the drawing
void GameObject::AddCollider(Collider* colliderToAdd)
{
	colliderToAdd->SetupDraw();
	//store wich gameobject the collider stores
	colliderToAdd->gameObjectOfCollider = this;
	colliderToAdd->positionOfCollider = g_position + colliderToAdd->offsetOfColliderPosition;
	initialPosition = g_position;
	collidersOfGameObject.push_back(colliderToAdd);
	
}


//this formula will get the moment of inertia depending on the body type
float GameObject::GetInertiaFromBodyType(int bodyType, float mass_, float width, float height, float radius)
{
	
	switch (bodyType)
	{
		//if its a square do the math for the inertia
	case BodyTypeOfGameObject::square:
		//store that this body type is a square type
		bodyTypeOfGameObject = BodyTypeOfGameObject::square;
		return 1.0f / 12.0f * mass_ * ((height * height) + (width * width));
		break;
		//if its a circle do the math for the inertia 
	case BodyTypeOfGameObject::circle:
		//store that this body type is a circle type
		bodyTypeOfGameObject = BodyTypeOfGameObject::circle;
		return 2.0f / 5.0f * mass_ * (radius * radius);
		break;
		//if its a rectangle do the math for the inertia 
	case BodyTypeOfGameObject::rectangle:
		//store that this body type is a rectangle type
		bodyTypeOfGameObject = BodyTypeOfGameObject::rectangle;
		return 1.0f / 12.0f * mass_ * ((height * height) + (width * width));
		break;
	}
	return 0;
}

//destructor that destroys particle variable, because we used the new keyword
GameObject::~GameObject()
{
	delete physicsBody;
	//delete every collider of this gameobject
	if (collidersOfGameObject.size() != 0)
	{
		//do a loop trough every collider and delete them
		for (int i = 0; i < collidersOfGameObject.size(); i++)
		{
			delete collidersOfGameObject[i];
		}
	}
	
	//delete particle;
}

//this function will be overwritten by non static objects
void GameObject::Update(float deltaTime)
{
}

//this will update the collider position
void GameObject::UpdateColliderPositions()
{
	//change the position of the collider if the game object has moved (it moved above)
	if (collidersOfGameObject.size() != 0)
	{
		//do a loop trough every collider of the gameobject and update its position
		for (int i = 0; i < collidersOfGameObject.size(); i++)
		{
			collidersOfGameObject[i]->positionOfCollider = g_position + collidersOfGameObject[i]->offsetOfColliderPosition;
			//this will update the collider rotation, it will only affect the OOBB
			collidersOfGameObject[i]->rotationOfCollider = g_rotation + collidersOfGameObject[i]->offsetOfColliderRotation;
		}
	}
}

