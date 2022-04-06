#include "scriptManager.h"

//create the constructor of the scene basically a script that is gonna create every object from the initial scene
gameSceneConstructor gameSceneConstructorScript;
//create the camera controller
cameraController cameraControllerScript;

void scriptManager::Start()
{
	//activate debug mode, so that we can see debug information
	GameEngine::ActivateOrDeactivateDebugMode(false);
	cameraControllerScript.Start();
	gameSceneConstructorScript.Start();
	addAndRemoveFlyForce::Start();
	
}

void scriptManager::Update()
{
	cameraControllerScript.Update();
	moveObject::Update();
	whiteBallController::Update();
	cueController::Update();
	addAndRemoveFlyForce::Update();
	//moveCollider::Update();
	
	//if we click on d turn debug mode, if x turn off debug mode
	if (ButtonsPressed::keys['z'] || ButtonsPressed::keys['Z'])
	{
		GameEngine::ActivateOrDeactivateDebugMode(true);
	}
	if (ButtonsPressed::keys['x'] || ButtonsPressed::keys['X'])
	{
		GameEngine::ActivateOrDeactivateDebugMode(false);
	}
	
}

void scriptManager::OnMouseClick()
{
	cameraControllerScript.OnMouseClick();
}

void scriptManager::OnCollisionEnter()
{
}

void scriptManager::OnTriggerEnter(Collider* triggerCollider, Collider* collider)
{
	wind::OnTriggerEnter(triggerCollider, collider);
	frictionZone::OnTriggerEnter(triggerCollider, collider);
}
