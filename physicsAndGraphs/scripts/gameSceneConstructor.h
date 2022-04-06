#pragma once
#include "../Collider.h"
#include "../SphereCollider.h"
#include "../BoxCollider.h"
#include "../PlaneCollider.h"

#include "../GameObject.h"
#include "../Model.h"
#include "../Sphere.h"
#include "../SphereRigidBody.h"
#include "../Cube.h"

#include "../GameEngine.h"

#include "moveCollider.h"
//this is gonna add every object that is on the start of the scene
class gameSceneConstructor
{
private:
	void ScriptsInitialiazer();
public:
	void Start();
	
};

