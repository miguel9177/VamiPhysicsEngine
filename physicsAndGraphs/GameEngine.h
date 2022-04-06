#pragma once
#include<vector>
#include "GameObject.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "ForceGenerator.h"
#include <iostream>
#include "GraphicsEngine.h"
#include "FieldObject.h"
#include "SkyBox.h"
//this is the script that calls the scripts functions for the gameplay
#include "scripts/scriptManager.h"
#include <list>
#pragma comment(lib, "glew32.lib") 



//this will store the collision information
struct CollisionInformation
{
	//i have this bollean for me to be able to check if it collided or not, and rturn this type aswell, for example at sphere collider collision information
	bool collided;
	Collider* colliders[2];
	glm::vec3 collisionPoint;
	glm::vec3 collisionNormal;
	float penetrationDepth;

};

//this is the grid for the broad phase, it will store wich objects are in which gridspace
struct CollisionGrid
{
	//this is going to store what objects are in this grid space
	std::vector<Collider*> collidersOnThisGridSpace;

	//store the position of the grid square
	float xPos;
	float yPos;

	//this will store the pos of the square using the xmin ymin, like this we have the grid pos and the size
	float xMin;
	float yMin;
	float xMax;
	float yMax;
	//this will be null if we are not in debug mode, if it is it will fill it with a cube representing this grid square
	GameObject* debugGridCube;
	
};

class GameEngine
{
private:
	/*
		WE USE STATIC SO THAT THIS VARIABLE IS A VARIABLE OF THE ENTIRE CLASS RATHER THAN FOR THE INSTANCE OF THE CLASS,
		WE ALSO DO THIS BECAUSE DRAW GAME FUNCTION IS STATIC AND IT CAN ONLY USE STATIC VARIABLES
	*/
	//a way to store and accesss created objects in the game world
	static std::vector<GameObject*> objects;
	static std::vector<Collider*> colliders;

	
	//create a vector of collision Information
	static std::vector<CollisionInformation> collisionInformations;

	//create a vector of collision Information
	static std::vector<std::vector<CollisionGrid>> broadPhaseGrid;

	//this will store the size of each grid size
	static float sizeOfEachGridSquare;

	//To work out delta time in between updates
	static int oldTimeSinceStart;
	//To work out delta time in between updates
	static int newTimeSinceStart;
	//this will be true if we are in debug mode
	static bool debugMode;
	//	WE USE STATIC SO THATE THIS FUCNTIONS IS A FUNCTION OF THE ENTIRE CLASS RATHER THAN FOR THE INSTANCE OF THE CLASS
	//update the objects and work out deltaTime between frames
	static void UpdateGame();

	//this will do the collision checking and it will be called o the update game function
	static void CheckCollision();

	//Draw all objects to the screen (will be called every frame probably)
	static void DrawGame();
	//delete the objects afterwards
	static void CleanupEngine();
	//the function to alter the window contents if the screen changes shape
	static void ResizeWindow(int w, int h);
	//this function will be called when the mouse clicks
	static void mouseClickFunction(int button, int state, int x, int y);
	static void mouseMoveFunction(int x, int y);
	//thsi will do the calculation of the collisions
	static void CollisionResolution();

	//this will do the broad phase for the collision
	static void BroadPhase();
	//this will create the grid for the broad phase
	static void InitBroadPhaseGrid();
	//this will check in which range the collider is, with this it will optimize the big o of the broadphase,
	//it will return a vector2 int since it will return where the collider starts and ends, with this we will be able to skip entire rows if we know the collider isnt on that range
	static glm::u8vec2 BroadPhaseCheckColliderIsInWichRowRange(Collider* colliderTocheck);
	//this will check in which range the collider is, with this it will optimize the big o of the broadphase,
	//it will return a vector2 int since it will return where the collider starts and ends, with this we will be able to skip entire columns if we know the collider isnt on that range
	static glm::u8vec2 BroadPhaseCheckColliderIsInWichColumnRange(Collider* colliderTocheck);
	//this function will add the colliders to the broad phase grid, it runs after we check where the collider is in terms of column and row of the grid 
	static void BroadPhaseAddCollidersToGrids(Collider* colliderTocheck, glm::u8vec2 wichRowsTheColliderIs_, glm::u8vec2 wichColumnsTheColliderIs_);
public:
	//create a variable that is going to call the update of the forcegenerator (add gravity etc)
	static ForceGenerator* forceGenerator;
	
	static float currentDeltaTime;

	//The function to set up/initialize opengl and GLUT and the function to get things ready (but not run).
	static void InitEngine(int argc, char** argv, const char* windowTitle, int width, int height);
	//A way to add objects to the game world.
	static void AddGameObject(GameObject*);
	//A way to remove game objects from the game world.
	static void RemoveGameObject(GameObject*);
	//Start the game world
	static void StartEngine();
	//this will return if the game engine is on debug mode or not
	static bool IsDebugModeOn();
	//this will activate or deactivate debug mode
	static void ActivateOrDeactivateDebugMode(bool);
	//constructor
	GameEngine();
};

