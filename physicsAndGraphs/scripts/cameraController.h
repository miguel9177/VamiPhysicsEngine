#pragma once
#include "../GameEngine.h"
#include "../ButtonsPressed.h"
#include "gameSceneConstructor.h"
class cameraController
{
private:
	//this will be true if the mouse is being dragged
	static bool isDragging;
	//this will store the pos of when we started dragging
	static glm::vec2 initialMousePos;
	//this will store the initial pos of the camera to be looking at the ball
	static glm::vec3 initialWhiteBallCameraPos;
	//this will store the current pos of the camera to be looking at the white ball
	static glm::vec3 currentWhiteBallCameraPos;
	//this will true on the first loop and false on the rest, i do this because the start doenst let me access the white ball object, since its not been assigned yet
	static bool firstTimeOnLoop;
	static float initialCameraPitch;
	static float initialCameraYaw;

	
	static void RotateCamera();
	//this will manage the key inputs for the camera
	static void InputManager();
	//this will move the camera to the right of the white ball
	static void MoveCameraToWhiteBallRightPos();
	//this will move the camera to the left of the white ball
	static void MoveCameraToWhiteBallLeftPos();
	//this will move the camera to the back of the white ball
	static void MoveCameraToWhiteBallBackPos();

	//this will move the camera to the diagonal
	static void MoveCameraToWhiteBallDiagonalBackLeftPos();
	//this will move the camera to the diagonal
	static void MoveCameraToWhiteBallDiagonalFrontLeftPos();
	//this will move the camera to the diagonal
	static void MoveCameraToWhiteBallDiagonalBackRightPos();
	//this will move the camera to the diagonal
	static void MoveCameraToWhiteBallDiagonalFrontRightPos();


public:
	//this is all of the possible camera positions
	static enum cameraPositions { FRONTPOS, RIGHTPOS, LEFTPOS, BACKPOS, TOPPOS, DIAGONALBACKLEFT, DIAGONALFRONTLEFT, DIAGONALBACKRIGHT, DIAGONALFRONTRIGHT };
	//this will store the white ball, its assigned on the game scene constructor
	static GameObject* whiteBall;
	//this will store the current camera pos
	static unsigned int currerntCameraPos;

	//this will move the camera to the top view
	static void MoveCameraToTopView();
	//this will move the camera to the ball pos, this will be accessed by the cue controller for it to move to the ball when tthe animation of the cue finishes
	static void MoveCameraToWhiteBallPos();

	static void Start();
	static void Update();
	static void OnMouseClick();
};

