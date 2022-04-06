#include "whiteBallController.h"

GameObject* whiteBallController::whiteBallGameObject;
float whiteBallController::speed;
bool whiteBallController::moveReady;
float whiteBallController::shootPower;
bool whiteBallController::startShootPower;

void whiteBallController::Start(float speed_, GameObject* whiteBallGameObject_)
{
	whiteBallGameObject = whiteBallGameObject_;
	speed = speed_;
	//this will store how much power the shoot gets, it will differ depending on how much time the user holds the space bar
	shootPower = 0;
	startShootPower = false;
}

void whiteBallController::Update()
{
	
	//if the move is ready and the ball is stopped, move the camera to the white ball position
	if (moveReady == false && std::fabs(whiteBallGameObject->ReturnPhysicsBody()->ReturnVelocity().x) < 0.1f && std::fabs(whiteBallGameObject->ReturnPhysicsBody()->ReturnVelocity().z) < 0.1f)
		cameraController::MoveCameraToWhiteBallPos();

	//if the ball stoped tell the code that we can play again
	if (std::fabs(whiteBallGameObject->ReturnPhysicsBody()->ReturnVelocity().x) < 0.1f && std::fabs(whiteBallGameObject->ReturnPhysicsBody()->ReturnVelocity().z) < 0.1f)
		moveReady = true; //tell the code that we currently can move, this will be accessedd by other scripts
	
	//if the ball is moving tell the code that the move is not ready
	else
		moveReady = false;

	//this will handle every input from the keyboard
	InputManager();
	
}

//this will handle every input from the keyboard
void whiteBallController::InputManager()
{
	//if clikced on space and the ball has stopped, or the animation started we want it to call the function that is going to do the cue animation and then move the ball
	if (ButtonsPressed::keys[32] && moveReady == true || cueController::animationStarted == true)
	{
		if(shootPower<1.f)
			shootPower += 0.3 * GameEngine::currentDeltaTime;

		if(startShootPower==true)
			MoveWhiteBall();
	}
	else if(shootPower!=0.f)
	{
		
		startShootPower = true;
		//since we are not pressing space, or the move isnt ready we reset the shot power
		MoveWhiteBall();
	}
	
}

//this will call the animation cue shoot function that is gong to animate the cue, and when the animation stops it will move the ball
void whiteBallController::MoveWhiteBall()
{
	//this will call the animation cue shoot function that is gong to animate the cue
	cueController::AnimationCueShoot();
	//if the animation stoped, move the ball
	if (cueController::animationStarted == false)
	{
		std::cout << "the shoot power is " << shootPower << " (from 0 to 1)" << std::endl;
		//depending on the camera position move the ball accordingly to that direction
		if (cameraController::currerntCameraPos == cameraController::FRONTPOS || cameraController::currerntCameraPos == cameraController::TOPPOS)
		{
			whiteBallGameObject->ReturnPhysicsBody()->AddForce(glm::vec3(0, 0, speed * shootPower), glm::vec3(-cueController::cueBallPosition.x, -cueController::cueBallPosition.y, cueController::cueBallPosition.z));
			startShootPower = false;
			shootPower = 0.f;
		}

		else if (cameraController::currerntCameraPos == cameraController::BACKPOS)
		{
			whiteBallGameObject->ReturnPhysicsBody()->AddForce(glm::vec3(0, 0, -speed * shootPower), glm::vec3(cueController::cueBallPosition));
			startShootPower = false;
			shootPower = 0.f;
		}
		else if (cameraController::currerntCameraPos == cameraController::LEFTPOS)
		{
			whiteBallGameObject->ReturnPhysicsBody()->AddForce(glm::vec3(-speed * shootPower, 0, 0), glm::vec3(cueController::cueBallPosition));
			startShootPower = false;
			shootPower = 0.f;
		}
		else if (cameraController::currerntCameraPos == cameraController::RIGHTPOS)
		{
			whiteBallGameObject->ReturnPhysicsBody()->AddForce(glm::vec3(speed * shootPower, 0, 0), glm::vec3(cueController::cueBallPosition));
			startShootPower = false;
			shootPower = 0.f;
		}
		//DIAGONALS
		else if (cameraController::currerntCameraPos == cameraController::DIAGONALBACKLEFT)
		{
			whiteBallGameObject->ReturnPhysicsBody()->AddForce(glm::vec3(-speed * shootPower, 0, speed * shootPower), glm::vec3(cueController::cueBallPosition));
			startShootPower = false;
			shootPower = 0.f;
		}
		else if (cameraController::currerntCameraPos == cameraController::DIAGONALFRONTLEFT)
		{
			whiteBallGameObject->ReturnPhysicsBody()->AddForce(glm::vec3(-speed * shootPower, 0, -speed * shootPower), glm::vec3(cueController::cueBallPosition));
			startShootPower = false;
			shootPower = 0.f;
		}
		else if (cameraController::currerntCameraPos == cameraController::DIAGONALBACKRIGHT)
		{
			whiteBallGameObject->ReturnPhysicsBody()->AddForce(glm::vec3(speed * shootPower, 0, speed * shootPower), glm::vec3(cueController::cueBallPosition));
			startShootPower = false;
			shootPower = 0.f;
		}
		else if (cameraController::currerntCameraPos == cameraController::DIAGONALFRONTRIGHT)
		{
			whiteBallGameObject->ReturnPhysicsBody()->AddForce(glm::vec3(speed, 0, -speed), glm::vec3(cueController::cueBallPosition));
			startShootPower = false;
			shootPower = 0.f;
		}

		//cameraController::MoveCameraToTopView();
	}
}

void whiteBallController::OnMouseClick()
{
}

void whiteBallController::OnCollisionEnter()
{
}

void whiteBallController::OnTriggerEnter(Collider* triggerCollider, Collider* collider)
{
	
}

bool whiteBallController::ReturnMoveReady()
{
	return moveReady;
}

