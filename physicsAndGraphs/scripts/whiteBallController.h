#pragma once
#include "../ButtonsPressed.h"
#include "../GameObject.h"
#include "cueController.h"
#include "cameraController.h"
//this class will be the one that adds power to the white ball and basically accepts the user input to aim the ball
class whiteBallController
{
private:
	static float speed;
	/*this will be true when the user can move the ball again, i use this on the cue controller for example,
	for it to know if it can play or not, and if it can show the cue*/
	static bool moveReady;
	static bool startShootPower;
	//this will store how much power the shoot gets, it will differ depending on how much time the user holds the space bar
	static float shootPower;

public:
	//this will store the white ball game object
	static GameObject* whiteBallGameObject;

	static void Start(float speed_, GameObject* whiteBallGameObject_);

	static void Update();

	//this will handle every input from the keyboard
	static void InputManager();

	//this will call the animation cue shoot function that is gong to animate the cue, and when the animation stops it will move the ball
	static void MoveWhiteBall();

	static void OnMouseClick();

	static void OnCollisionEnter();

	static void OnTriggerEnter(Collider* triggerCollider, Collider* collider);

	//this will return if we can p[lay agin or not (moveready boolean)
	static bool ReturnMoveReady();
};

