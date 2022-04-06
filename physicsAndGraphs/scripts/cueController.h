#pragma once
#include "../GameObject.h"
#include "whiteBallController.h"
//this class will controll the cue position,, and everything associated with the cue
class cueController
{
private:
	//this will store the white ball game object, since we will need to know the position of it to position the cue
	static GameObject* whiteBallGameObject;
	//this is going to store the cue gameobject
	static GameObject* poolCueGameObject;
	//this will store the camera pos, when the animation starts, so that it playes the same anymation until it finishes
	static int currentCameraPosForAnimation;


public:
	//this will have the position on the ball, this means if it hits up down left, it will be capped from -1 to 1 on all axis
	static glm::vec3 cueBallPosition;
	//this will be true if the animation has started, this will be accessed on the whiteball controller
	static bool animationStarted;
	//this will be true when the cue is coming back to kick the ball, and it will let me check if the cue already arrived the ball
	static bool checkForStopAnimation;

	static void Start(GameObject* poolCueGameObject_, GameObject* whiteBallGameObject_);

	static void Update();

	static void InputManager();

	static void AnimationCueShoot();

	static void OnMouseClick();

	static void OnCollisionEnter();

	static void OnTriggerEnter();
	
};

