#pragma once

//include the game engine class
#include "GameEngine.h"

//include the gameobject class that is going to let me create players, cubes etc
#include "GameObject.h"
//include the player class (children of gameobject class), this will create an object that movec, rotates, and has the inertia calculation
#include "Player.h"
//include the cube class (children of game object class)
#include "Cube.h"
//include the cube class (children of game object class)
#include "Sphere.h"
//include the Model class (children of game object class)
#include "Model.h"

//import the colliders
#include "Collider.h"
#include "SphereCollider.h";
#include "BoxCollider.h";

//include a force generator class that is going to let me add gravity and other forces to objects
#include "ForceGenerator.h"

#include "GL/glut.h"


//Create some objects				//float mass_, glm::vec3 position_, float speed_, float rotationalSpeed_, int bodyType, float width_, float height_, glm::vec3 orientation_, float radius
//GameObject* playerObject = new Player(1.0f		, glm::vec3(0, 0, 0)	, glm::vec3(0,0,1.f),10.f		, 3.f					, 0			  , 2.f			, 2.f			, glm::vec3(0,0,0)		, 0);

//Collider* boxCollider = new BoxCollider(glm::vec3 (2,1,2));
//this object is a particle (doesnt rotate)
//GameObject* cubeObject = new Cube(1.5f, glm::vec3(-2.f, 0.f, 0.f), false, glm::vec3(0, 1.f ,0), glm::vec3(2,1,2), boxCollider);

//Collider* boxCollider2 = new BoxCollider(glm::vec3(2, 1, 2));
//this object is a particle (doesnt rotate)
//GameObject* cubeObject2 = new Cube(1.5f, glm::vec3(-2.f, -2.5f, 0.f), false, glm::vec3(0, 1.f, 0), glm::vec3(2, 1, 2), boxCollider2);


//create a collider for the circle and send it to the circle object
//Collider* circleCollider = new SphereCollider(1.f);
//this object is a particle (doesnt rotate)(mass, pos					,movable, color			,radius, collider
//GameObject* circleObject = new Sphere	  (1.5f, glm::vec3(3.f, 2.f, 0.f), true, glm::vec3(1.f,0,0), 1.f, circleCollider);

//create a collider for the circle and send it to the circle object
//Collider* circleCollider2 = new SphereCollider(1.f);
//this object is a particle (doesnt rotate)(mass, pos					,movable, color			,radius, collider
//GameObject* circleObject2 = new Sphere(1.5f, glm::vec3(3.f, 2.f, 0.f), false, glm::vec3(1.f, 0, 0), 1.f, circleCollider2);

//create a collider for the circle and send it to the circle object
//Collider* circleCollider3 = new SphereCollider(1.f);
//this object is a particle (doesnt rotate)(mass, pos					,movable, color			,radius, collider
//GameObject* circleObject3 = new Sphere(1.5f, glm::vec3(3.f, -2.f, 0), false, glm::vec3(1.f, 0, 0), 1.f, circleCollider3);

//this is going to create a model : const char* ObjFileName, const char* TextureLocationName_, glm::vec3 position_, glm::vec3 scale_, glm::vec3 rotation_
/*Collider* colliderOfModel = new SphereCollider(1.f, glm::vec3(0));
GameObject* myModel = new Model("Objs/myTable.obj", "Textures/grass.bmp", glm::vec3(0, 10, -20), glm::vec3(0.2), glm::vec3(0, 0, 0), 1, true, BodyTypeOfGameObject::square);
//GameObject* myModel = new Model("Objs/myTable.obj", "Textures/grass.bmp", glm::vec3(0, 10, -20), glm::vec3(1), glm::vec3(0, 0, 0), 1, true, BodyTypeOfGameObject::square, colliderOfModel);
GameObject* myModel2 = new Model("Objs/myTable.obj", "Textures/sky.bmp", glm::vec3(70, 30, -90), glm::vec3(0.2), glm::vec3(90, 0, 0), 1, false, BodyTypeOfGameObject::square);

Collider* sphereCollider1 = new SphereCollider(1.f, glm::vec3(10,0,0));
//this object is a particle (doesnt rotate)const char* TextureLocationName_, glm::vec3 position_, glm::vec3 scale_, glm::vec3 rotation_, float mass_, bool movable_
GameObject* sphereObject1 = new Sphere("Textures/wood.jpg"					, glm::vec3(0, 0, -50), 8		, glm::vec3(0), 5, true);

Collider* sphereCollider2 = new SphereCollider(8.1f, glm::vec3(0));
//this object is a particle (doesnt rotate)(mass, pos					,movable, color			,radius, collider
GameObject* sphereObject2 = new Sphere("Textures/wood.jpg", glm::vec3(5, 0, -20), 8, glm::vec3(0), 5, true);

Collider* cubeCollider = new BoxCollider(glm::vec3(2.1f), glm::vec3(0,0, 0));
GameObject* cubeObject = new Cube("Textures/wood.jpg", glm::vec3(0, 0, -20),glm::vec3(2), glm::vec3(0), 5, false);

Collider* cubeCollider2 = new BoxCollider(glm::vec3(2.5f), glm::vec3(0));
GameObject* cubeObject2 = new Cube("Textures/wood.jpg", glm::vec3(5, 20, -20), glm::vec3(2), glm::vec3(0, 45, 0), 5, true);
*/

// Main routine.
int main(int argc, char** argv)
{
	//initialize the engine
	GameEngine::InitEngine(argc, argv, "Vami Physics Engine", 500, 500);
	//this will update setup the camera movement to the one on the constructor
	GraphicsEngine::MoveCamera();
	
	//add the objects to the engine (so it actually knows about the objects!
	//GameEngine::AddGameObject(playerObject);
	//GameEngine::AddGameObject(cubeObject);
	//GameEngine::AddGameObject(cubeObject2);
	//GameEngine::AddGameObject(circleObject);
	//GameEngine::AddGameObject(circleObject2);
	//GameEngine::AddGameObject(circleObject3);
	
	//GameEngine::AddGameObject(sphereObject1);
	//GameEngine::AddGameObject(sphereObject2);
	/*myModel->AddCollider(colliderOfModel);
	GameEngine::AddGameObject(myModel);
	cubeObject->AddCollider(cubeCollider);
	cubeObject2->AddCollider(sphereCollider1);
	cubeObject2->AddCollider(cubeCollider2);
	GameEngine::AddGameObject(cubeObject);
	GameEngine::AddGameObject(cubeObject2);

	//register the objects that are going to get gravity
	GameEngine::forceGenerator->RegisterNewObjectToGravityForce(sphereObject1);
	GameEngine::forceGenerator->RemoveObjectFromReceivingForce(sphereObject1);
	//GameEngine::forceGenerator->RegisterNewObjectToGravityForce(myModel);
	//register the objects that are going to get gravity
	//GameEngine::forceGenerator->RegisterNewObjectToGravityForce(myModel);
	//GameEngine::forceGenerator->RegisterNewObjectToGravityForce(cubeObject);

	//Remove object
	GameEngine::RemoveGameObject(cubeObject2);*/

	GameEngine::StartEngine();
	//Start the engine (which causes the game loop to occur with your functions - Drawing, Updating etc.)	
	return 0;
}