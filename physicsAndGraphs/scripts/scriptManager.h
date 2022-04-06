#pragma once
#include "cameraController.h"
#include "gameSceneConstructor.h"
#include "moveObject.h"
#include "whiteBallController.h"
#include "cueController.h"
#include "addAndRemoveFlyForce.h"
#include "wind.h"
#include "frictionZone.h"
//THIS SCRIPT HAVE FUNCTIONS THAT WILL BE CALLED BY THE GAME ENGINE, END FROM HERE I WILL CALL THE FUNCTIONS FROM OTHER SCRIPTS,
//SO BASICALLY THIS SCRIPTMANAGER IS A COMUNICATION BETWEEN THE GAMEENGINE AND THE GAME ITSELF
class scriptManager
{
public:
	//this is called on the game engine InitEngine function
	static void Start();
	//this is called on the game engine UpdateGame function
	static void Update();
	//this is called on the game engine mouseClickFunction function
	static void OnMouseClick();
	static void OnCollisionEnter();
	static void OnTriggerEnter(Collider* triggerCollider, Collider* collider);
};

