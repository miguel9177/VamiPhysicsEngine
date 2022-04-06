#include "gameSceneConstructor.h"

//this is going to create a model : const char* ObjFileName, const char* TextureLocationName_, glm::vec3 position_, glm::vec3 scale_, glm::vec3 rotation_

//START OF POOL GAME SCENE BUILDER
Collider* colliderOfSphereRb1 = new SphereCollider(0.32f, glm::vec3(0));
GameObject* sphereRb1 = new SphereRigidBody("Textures/RedBallTexture.png", glm::vec3(7.82f + 2.367f, -0.7f, 6.16f + 16.849f), 0.29f, glm::vec3(0), 0.01f, true,0.99f, 0.9f);

Collider* colliderOfSphereRb2 = new SphereCollider(0.32f, glm::vec3(0));
GameObject* sphereRb2 = new SphereRigidBody("Textures/GreenBallTexture.png", glm::vec3(7.17f + 2.367f, -0.7f, 6.16f + 16.849f), 0.29f, glm::vec3(0), 0.01f, true, 0.99f, 0.9f);

Collider* colliderOfSphereRb3 = new SphereCollider(0.32f, glm::vec3(0));
GameObject* sphereRb3 = new SphereRigidBody("Textures/RedBallTexture.png", glm::vec3(6.52f + 2.367f, -0.7f, 6.16f + 16.849f), 0.29f, glm::vec3(0), 0.01f, true, 0.99f, 0.9f);

Collider* colliderOfSphereRb4 = new SphereCollider(0.32f, glm::vec3(0));
GameObject* sphereRb4 = new SphereRigidBody("Textures/GreenBallTexture.png", glm::vec3(5.87f + 2.367f, -0.7f, 6.16f + 16.849f), 0.29f, glm::vec3(0), 0.01f, true, 0.99f, 0.9f);

Collider* colliderOfSphereRb5 = new SphereCollider(0.32f, glm::vec3(0));
GameObject* sphereRb5 = new SphereRigidBody("Textures/RedBallTexture.png", glm::vec3(5.22f + 2.367f, -0.7f, 6.16f + 16.849f), 0.29f, glm::vec3(0), 0.01f, true, 0.99f, 0.9f);

Collider* colliderOfSphereRb6 = new SphereCollider(0.32f, glm::vec3(0));
GameObject* sphereRb6 = new SphereRigidBody("Textures/GreenBallTexture.png", glm::vec3(7.495f + 2.367f, -0.7f, 5.51f + 16.849f), 0.29f, glm::vec3(0), 0.01f, true, 0.99f, 0.9f);

Collider* colliderOfSphereRb7 = new SphereCollider(0.32f, glm::vec3(0));
GameObject* sphereRb7 = new SphereRigidBody("Textures/RedBallTexture.png", glm::vec3(6.845f + 2.367f, -0.7f, 5.51f + 16.849f), 0.29f, glm::vec3(0), 0.01f, true, 0.99f, 0.9f);

Collider* colliderOfSphereRb8 = new SphereCollider(0.32f, glm::vec3(0));
GameObject* sphereRb8 = new SphereRigidBody("Textures/GreenBallTexture.png", glm::vec3(6.195f + 2.367f, -0.7f, 5.51f + 16.849f), 0.29f, glm::vec3(0), 0.01f, true, 0.99f, 0.9f);

Collider* colliderOfSphereRb9 = new SphereCollider(0.32f, glm::vec3(0));
GameObject* sphereRb9 = new SphereRigidBody("Textures/RedBallTexture.png", glm::vec3(5.545f + 2.367f, -0.7f, 5.51f + 16.849f), 0.29f, glm::vec3(0), 0.01f, true, 0.99f, 0.9f);

Collider* colliderOfSphereRb10 = new SphereCollider(0.32f, glm::vec3(0));
GameObject* sphereRb10 = new SphereRigidBody("Textures/GreenBallTexture.png", glm::vec3(7.17f + 2.367f, -0.7f, 4.86f + 16.849f), 0.29f, glm::vec3(0), 0.01f, true, 0.99f, 0.9f);

Collider* colliderOfSphereRb11 = new SphereCollider(0.32f, glm::vec3(0));
GameObject* sphereRb11 = new SphereRigidBody("Textures/BlackBallTexture.png", glm::vec3(6.52f + 2.367f, -0.7f, 4.86f + 16.849f), 0.29f, glm::vec3(0), 0.01f, true, 0.99f, 0.9f);

Collider* colliderOfSphereRb12 = new SphereCollider(0.32f, glm::vec3(0));
GameObject* sphereRb12 = new SphereRigidBody("Textures/GreenBallTexture.png", glm::vec3(5.87f + 2.367f, -0.7f, 4.86f + 16.849f), 0.29f, glm::vec3(0), 0.01f, true, 0.99f, 0.9f);

Collider* colliderOfSphereRb13 = new SphereCollider(0.32f, glm::vec3(0));
GameObject* sphereRb13 = new SphereRigidBody("Textures/RedBallTexture.png", glm::vec3(6.845f + 2.367f, -0.7f, 4.21f + 16.849f), 0.29f, glm::vec3(0), 0.01f, true, 0.99f, 0.9f);

Collider* colliderOfSphereRb14 = new SphereCollider(0.32f, glm::vec3(0));
GameObject* sphereRb14 = new SphereRigidBody("Textures/GreenBallTexture.png", glm::vec3(6.195f + 2.367f, -0.7f, 4.21f + 16.849f), 0.29f, glm::vec3(0), 0.01f, true, 0.99f, 0.9f);

Collider* colliderOfSphereRb15 = new SphereCollider(0.32f, glm::vec3(0));
GameObject* sphereRb15 = new SphereRigidBody("Textures/RedBallTexture.png", glm::vec3(6.52f + 2.367f, -0.7f, 3.56f + 16.849f), 0.29f, glm::vec3(0), 0.01f, true, 0.99f, 0.9f);


Collider* colliderOfWhiteBall = new SphereCollider(0.32f, glm::vec3(0));
GameObject* whiteBall = new SphereRigidBody("Textures/WhiteBallTexture.png", glm::vec3(6.52f + 2.367f, -0.7f, 10.4f), 0.29f, glm::vec3(0), 0.02f, true, 0.99f, 0.9f);

//Collider* colliderOfTableBase = new BoxCollider(glm::vec3(5.1, 1, 11.5), glm::vec3(0, 5.78, -0.f));
Collider* colliderOfTableBase = new PlaneCollider(glm::vec2(5.1f, 11.5f), glm::vec3(0, 6.8, 0));
Collider* colliderOfTableFrontLeft = new BoxCollider(glm::vec3(1, 2.85, 4.69997), glm::vec3(6, 5.78, 5.35));
Collider* colliderOfTableBackLeft = new BoxCollider(glm::vec3(1, 2.86, 4.69997), glm::vec3(6, 5.78, -5.35));
Collider* colliderOfTableFront = new BoxCollider(glm::vec3(4.2f, 1.8, 1.099), glm::vec3(0.04, 6.98, 12));
Collider* colliderOfTableBack = new BoxCollider(glm::vec3(4.2f, 1.8, -1.099), glm::vec3(0.04, 6.98, -12));
Collider* colliderOfTableFrontRight = new BoxCollider(glm::vec3(1, 2.85, 4.69997), glm::vec3(-6, 5.78, 5.35));
Collider* colliderOfTableBackRight = new BoxCollider(glm::vec3(1, 2.85, 4.69997), glm::vec3(-6, 5.78, -5.35));
//trigger collider to add wind
Collider* boxTriggerToAddWind = new BoxCollider(glm::vec3(0.5f,0.1, 1), glm::vec3(0.04, 6.96, 9.5f));
//trigger collider to add friction zone
Collider* boxTriggerToAddFrictionZone = new BoxCollider(glm::vec3(0.5f, 0.1, 1), glm::vec3(0.04, 6.96, -6.5f));
GameObject* poolTable = new Model("Objs/poolTableUpdated.obj", "Textures/grass.bmp", glm::vec3(8.943f, -14.973f, 14.574f), glm::vec3(0.2), glm::vec3(0), 99999, false, BodyTypeOfGameObject::rectangle, 0.5f, 0.95f);

//the cue position is changed on the cueController
GameObject* cue = new Model("Objs/PoolCue.obj", "Textures/Cue.png", glm::vec3(0, 0, 0), glm::vec3(2), glm::vec3(90,90,0), 1, true, BodyTypeOfGameObject::rectangle, 0.9f, 0.9f);

//this will be used to stop objects from flying more
Collider* colliderOfFlyingPlane = new PlaneCollider(glm::vec2(5.1f, 11.5f), glm::vec3(0, -0.1f, 0));
GameObject* flyingPlane = new Cube("Textures/WhiteBallTexture.png", glm::vec3(8.887, 2.469f, 37.34f), glm::vec3(5.1f ,0, 11.5f), glm::vec3(0), 0.02f, false, 0.99f, 0.9f);

//this will be used to stop objects from flying more
Collider* colliderOfGroundFlyingPlane = new PlaneCollider(glm::vec2(5.1f, 11.5f), glm::vec3(0, -0.1f, 0));
GameObject* groundFlyingPlane = new Cube("Textures/WhiteBallTexture.png", glm::vec3(8.887, -6.f, 37.34f), glm::vec3(5.1f, 0, 11.5f), glm::vec3(0), 0.02f, false, 0.99f, 0.9f);

//Cube in midle of table
Collider* colliderOfBoxInMidleOfTable = new BoxCollider(glm::vec3(1, 1, 1), glm::vec3(0));
GameObject* boxInMidleOfTable = new Cube("Textures/WhiteBallTexture.png", glm::vec3(8.887, -6.f, 37.34f), glm::vec3(1), glm::vec3(0), 0.1f, true, 0.5f, 0.9f);

//Sphere in midle of table
Collider* colliderOfSphereInMidleOfTable = new SphereCollider(1, glm::vec3(0));
GameObject* SphereInMidleOfTable = new SphereRigidBody("Textures/WhiteBallTexture.png", glm::vec3(5, -6.f, 37.34f), 1, glm::vec3(0), 0.1f, true, 0.5f, 0.9f);

//Collider* colliderOfPlane = new PlaneCollider(glm::vec2(2),glm::vec3(0));
//GameObject* planeTest = new SphereRigidBody("Textures/WhiteBallTexture.png", glm::vec3(6.52f + 2.367f,10.f, 10.4f), 0.29f, glm::vec3(0), 0.02f, true, 0.99f, 0.9f);
//Collider* colliderOfPlane2 = new PlaneCollider(glm::vec2(2), glm::vec3(0));
//GameObject* planeTest2 = new SphereRigidBody("Textures/WhiteBallTexture.png", glm::vec3(6.52f + 2.367f, -7.f, 10.4f), 0.29f, glm::vec3(0), 0.02f, true, 0.99f, 0.9f);

void gameSceneConstructor::Start()
{
	SkyBox::Init("Textures/wall.png", "Textures/wood.jpg");

	//planeTest->AddCollider(colliderOfPlane);
	//GameEngine::AddGameObject(planeTest);
	//ForceGenerator::RegisterNewObjectToGravityForce(planeTest);

	//planeTest2->AddCollider(colliderOfPlane2);
	//GameEngine::AddGameObject(planeTest2);

	flyingPlane->AddCollider(colliderOfFlyingPlane);
	GameEngine::AddGameObject(flyingPlane);

	groundFlyingPlane->AddCollider(colliderOfGroundFlyingPlane);
	GameEngine::AddGameObject(groundFlyingPlane);

	boxInMidleOfTable->AddCollider(colliderOfBoxInMidleOfTable);
	GameEngine::AddGameObject(boxInMidleOfTable);
	ForceGenerator::RegisterNewObjectToGravityForce(boxInMidleOfTable);

	SphereInMidleOfTable->AddCollider(colliderOfSphereInMidleOfTable);
	GameEngine::AddGameObject(SphereInMidleOfTable);
	ForceGenerator::RegisterNewObjectToGravityForce(SphereInMidleOfTable);

	GameEngine::AddGameObject(cue);

	sphereRb1->AddCollider(colliderOfSphereRb1);
	GameEngine::AddGameObject(sphereRb1);
	ForceGenerator::RegisterNewObjectToGravityForce(sphereRb1);

	sphereRb2->AddCollider(colliderOfSphereRb2);
	GameEngine::AddGameObject(sphereRb2);
	ForceGenerator::RegisterNewObjectToGravityForce(sphereRb2);

	sphereRb3->AddCollider(colliderOfSphereRb3);
	GameEngine::AddGameObject(sphereRb3);
	ForceGenerator::RegisterNewObjectToGravityForce(sphereRb3);

	sphereRb4->AddCollider(colliderOfSphereRb4);
	GameEngine::AddGameObject(sphereRb4);
	ForceGenerator::RegisterNewObjectToGravityForce(sphereRb4);

	sphereRb5->AddCollider(colliderOfSphereRb5);
	GameEngine::AddGameObject(sphereRb5);
	ForceGenerator::RegisterNewObjectToGravityForce(sphereRb5);

	sphereRb6->AddCollider(colliderOfSphereRb6);
	GameEngine::AddGameObject(sphereRb6);
	ForceGenerator::RegisterNewObjectToGravityForce(sphereRb6);

	sphereRb7->AddCollider(colliderOfSphereRb7);
	GameEngine::AddGameObject(sphereRb7);
	ForceGenerator::RegisterNewObjectToGravityForce(sphereRb7);

	sphereRb8->AddCollider(colliderOfSphereRb8);
	GameEngine::AddGameObject(sphereRb8);
	ForceGenerator::RegisterNewObjectToGravityForce(sphereRb8);

	sphereRb9->AddCollider(colliderOfSphereRb9);
	GameEngine::AddGameObject(sphereRb9);
	ForceGenerator::RegisterNewObjectToGravityForce(sphereRb9);

	sphereRb10->AddCollider(colliderOfSphereRb10);
	GameEngine::AddGameObject(sphereRb10);
	ForceGenerator::RegisterNewObjectToGravityForce(sphereRb10);

	sphereRb11->AddCollider(colliderOfSphereRb11);
	GameEngine::AddGameObject(sphereRb11);
	ForceGenerator::RegisterNewObjectToGravityForce(sphereRb11);

	sphereRb12->AddCollider(colliderOfSphereRb12);
	GameEngine::AddGameObject(sphereRb12);
	ForceGenerator::RegisterNewObjectToGravityForce(sphereRb12);
	
	sphereRb13->AddCollider(colliderOfSphereRb13);
	GameEngine::AddGameObject(sphereRb13);
	ForceGenerator::RegisterNewObjectToGravityForce(sphereRb13);

	sphereRb14->AddCollider(colliderOfSphereRb14);
	GameEngine::AddGameObject(sphereRb14);
	ForceGenerator::RegisterNewObjectToGravityForce(sphereRb14);

	sphereRb15->AddCollider(colliderOfSphereRb15);
	GameEngine::AddGameObject(sphereRb15);
	ForceGenerator::RegisterNewObjectToGravityForce(sphereRb15);

	whiteBall->AddCollider(colliderOfWhiteBall);
	GameEngine::AddGameObject(whiteBall);
	ForceGenerator::RegisterNewObjectToGravityForce(whiteBall);
	
	poolTable->AddCollider(colliderOfTableBase);
	poolTable->AddCollider(colliderOfTableFrontLeft);
	poolTable->AddCollider(colliderOfTableBackLeft);
	poolTable->AddCollider(colliderOfTableFront);
	poolTable->AddCollider(colliderOfTableBack);
	poolTable->AddCollider(colliderOfTableFrontRight);
	poolTable->AddCollider(colliderOfTableBackRight);
	//tell the box that he is a trigger
	boxTriggerToAddWind->isTrigger = true;
	poolTable->AddCollider(boxTriggerToAddWind);
	//tell the box that he is a trigger
	boxTriggerToAddFrictionZone->isTrigger = true;
	poolTable->AddCollider(boxTriggerToAddFrictionZone);
	GameEngine::AddGameObject(poolTable);

	//assign values for multiple scripts
	ScriptsInitialiazer();
	
}

void gameSceneConstructor::ScriptsInitialiazer()
{
	//make me move this object by arrow keys
	moveObject::gameObjectToMove = whiteBall;
	moveObject::speed = 10.f;
	//assign the white ball to camera controller, so that the camera can move to the white ball position
	cameraController::whiteBall = whiteBall;
	whiteBallController::Start(57, whiteBall);
	cueController::Start(cue, whiteBall);
	//tell the wind script wich collider is the trigger
	wind::Start(boxTriggerToAddWind);
	//tell the wind script wich collider is the trigger
	frictionZone::Start(boxTriggerToAddFrictionZone);
	//make me move this object by arrow keys
	//moveCollider::colliderObjectToMove = colliderOfFlyingPlane;

	addAndRemoveFlyForce::AddObjects(boxInMidleOfTable);
	addAndRemoveFlyForce::AddObjects(SphereInMidleOfTable);
}

