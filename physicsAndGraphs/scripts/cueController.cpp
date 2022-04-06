#include "cueController.h"

GameObject* cueController::whiteBallGameObject;
GameObject* cueController::poolCueGameObject;
bool cueController::animationStarted;
bool cueController::checkForStopAnimation;
int cueController::currentCameraPosForAnimation;
glm::vec3 cueController::cueBallPosition;

void cueController::Start(GameObject* poolCueGameObject_, GameObject* whiteBallGameObject_)
{
	//this will store the cue gameobject
	poolCueGameObject = poolCueGameObject_;
	//this will store the whiteball gameobject
	whiteBallGameObject = whiteBallGameObject_;
	animationStarted = false;
	checkForStopAnimation = false;
	//this will be minus one, since no animation is p[laying
	currentCameraPosForAnimation = -1;
	//this will have the position on the ball, this means if it hits up down left, it will be capped from -1 to 1 on all axis
	cueBallPosition = glm::vec3(0);
	
}

void cueController::Update()
{
	//INFORMATION the cueballposition is gonna move the cue, to add effect, its capped to -1 to 1, and i do *0.25 so that visually it doesnt go away from the ball
	//if the move is ready move the cue to the ball
	if (whiteBallController::ReturnMoveReady() && animationStarted == false)
	{
		//if the cameras is on the fornt pos or the top pos
		if (cameraController::currerntCameraPos == cameraController::FRONTPOS || cameraController::currerntCameraPos == cameraController::TOPPOS)
		{
			//this will move the pool to the white ball position
			poolCueGameObject->ReturnPhysicsBody()->SetPosition(glm::vec3(whiteBallGameObject->g_position.x + (cueBallPosition.x * 0.25f), whiteBallGameObject->g_position.y + (cueBallPosition.y * 0.25f), (whiteBallGameObject->g_position.z - 1.8f) + (cueBallPosition.z * 0.25f)));
			poolCueGameObject->ReturnPhysicsBody()->SetOrientation(glm::vec3(90, 90, 0));
		}
		//if the cameras is on the back position the cue accordingly
		else if (cameraController::currerntCameraPos == cameraController::BACKPOS)
		{
			poolCueGameObject->ReturnPhysicsBody()->SetPosition(glm::vec3(whiteBallGameObject->g_position.x + (cueBallPosition.x * 0.25f), whiteBallGameObject->g_position.y + (cueBallPosition.y * 0.25f), (whiteBallGameObject->g_position.z + 1.8f) + (cueBallPosition.z * 0.25f)));
			poolCueGameObject->ReturnPhysicsBody()->SetOrientation(glm::vec3(-90, 0, 0));
		}
		//if the cameras is on the back position the cue accordingly
		else if (cameraController::currerntCameraPos == cameraController::LEFTPOS)
		{
			//this will move the pool to the white ball position
			poolCueGameObject->ReturnPhysicsBody()->SetPosition(glm::vec3((whiteBallGameObject->g_position.x + 1.8f) + (cueBallPosition.z * 0.25f), whiteBallGameObject->g_position.y + (cueBallPosition.y * 0.25f), whiteBallGameObject->g_position.z + (cueBallPosition.x * 0.25f)));
			poolCueGameObject->ReturnPhysicsBody()->SetOrientation(glm::vec3(-90, 0, 90));
		}
		//if the cameras is on the back position the cue accordingly
		else if (cameraController::currerntCameraPos == cameraController::RIGHTPOS)
		{
			//this will move the pool to the white ball position
			poolCueGameObject->ReturnPhysicsBody()->SetPosition(glm::vec3((whiteBallGameObject->g_position.x - 1.8f) + (cueBallPosition.z * 0.25f), whiteBallGameObject->g_position.y + (cueBallPosition.y * 0.25f), whiteBallGameObject->g_position.z + (cueBallPosition.x * 0.25f)));
			poolCueGameObject->ReturnPhysicsBody()->SetOrientation(glm::vec3(-90, 0, -90));
		}

		//DIAGONALS
		//if the cameras is on the back position the cue accordingly
		else if (cameraController::currerntCameraPos == cameraController::DIAGONALBACKLEFT)
		{
			//this will move the pool to the white ball position
			poolCueGameObject->ReturnPhysicsBody()->SetPosition(glm::vec3(whiteBallGameObject->g_position.x + 1.118, whiteBallGameObject->g_position.y, whiteBallGameObject->g_position.z - 1.118) + cueBallPosition * 0.25f);
			poolCueGameObject->ReturnPhysicsBody()->SetOrientation(glm::vec3(0, 45, 90));
		}
		//if the cameras is on the back position the cue accordingly
		else if (cameraController::currerntCameraPos == cameraController::DIAGONALFRONTLEFT)
		{
			//this will move the pool to the white ball position
			poolCueGameObject->ReturnPhysicsBody()->SetPosition(glm::vec3(whiteBallGameObject->g_position.x + 1.118, whiteBallGameObject->g_position.y, whiteBallGameObject->g_position.z + 1.118) + cueBallPosition * 0.25f);
			poolCueGameObject->ReturnPhysicsBody()->SetOrientation(glm::vec3(0, -45, 90));
		}
		//if the cameras is on the back position the cue accordingly
		else if (cameraController::currerntCameraPos == cameraController::DIAGONALBACKRIGHT)
		{
			//this will move the pool to the white ball position
			poolCueGameObject->ReturnPhysicsBody()->SetPosition(glm::vec3(whiteBallGameObject->g_position.x - 1.118f, whiteBallGameObject->g_position.y, whiteBallGameObject->g_position.z - 1.118) + cueBallPosition * 0.25f);
			poolCueGameObject->ReturnPhysicsBody()->SetOrientation(glm::vec3(0, 135, 90));
		}
		//if the cameras is on the back position the cue accordingly
		else if (cameraController::currerntCameraPos == cameraController::DIAGONALFRONTRIGHT)
		{
			//this will move the pool to the white ball position
			poolCueGameObject->ReturnPhysicsBody()->SetPosition(glm::vec3(whiteBallGameObject->g_position.x - 1.118f, whiteBallGameObject->g_position.y, whiteBallGameObject->g_position.z + 1.118f) + cueBallPosition * 0.25f);
			poolCueGameObject->ReturnPhysicsBody()->SetOrientation(glm::vec3(0, -135, 90));
		}
	}
	//make the y stay on the ball height
	poolCueGameObject->ReturnPhysicsBody()->SetPosition(glm::vec3(poolCueGameObject->ReturnPhysicsBody()->ReturnPosition().x, whiteBallGameObject->g_position.y + (cueBallPosition.y * 0.25f), poolCueGameObject->ReturnPhysicsBody()->ReturnPosition().z));

	InputManager();
}

//this will handle all of the keys input
void cueController::InputManager()
{
	//if user clicks up arrow move the cue up
	if (ButtonsPressed::specialKeys[GLUT_KEY_UP])
	{
		cueBallPosition.y += 0.01;
	}
	//if user clicks left arrow move the cue left
	if (ButtonsPressed::specialKeys[GLUT_KEY_LEFT])
	{
		cueBallPosition.x -= 0.01;
	}
	//if user clicks right arrow move the cue right
	if (ButtonsPressed::specialKeys[GLUT_KEY_RIGHT])
	{
		cueBallPosition.x += 0.01;
	}
	//if user clicks down arrow move the cue down
	if (ButtonsPressed::specialKeys[GLUT_KEY_DOWN])
	{
		cueBallPosition.y -= 0.01;
	}

	
	//cap the pos to -1 to 1
	if (cueBallPosition.x < -1)
		cueBallPosition.x = -1;
	else if (cueBallPosition.x > 1)
		cueBallPosition.x = 1;
	else if (cueBallPosition.y < -1)
		cueBallPosition.y = -1;
	else if (cueBallPosition.y > 1)
		cueBallPosition.y = 1;
}

//this will animate the cue 
void cueController::AnimationCueShoot()
{
	//if the animation hasent started move the cue back
	if (animationStarted == false)
	{
		//if the cameras is on the fornt pos or the top pos
		if (cameraController::currerntCameraPos == cameraController::FRONTPOS || cameraController::currerntCameraPos == cameraController::TOPPOS)
		{
			poolCueGameObject->ReturnPhysicsBody()->AddForce(glm::vec3(0, 0, -500.f));
			currentCameraPosForAnimation = cameraController::FRONTPOS;
		}
		//if the cameras is on the back position the cue accordingly
		else if (cameraController::currerntCameraPos == cameraController::BACKPOS)
		{
			poolCueGameObject->ReturnPhysicsBody()->AddForce(glm::vec3(0, 0, 500.f));
			currentCameraPosForAnimation = cameraController::BACKPOS;
		}
		//if the cameras is on the back position the cue accordingly
		else if (cameraController::currerntCameraPos == cameraController::LEFTPOS)
		{
			poolCueGameObject->ReturnPhysicsBody()->AddForce(glm::vec3(500.f, 0, 0));
			currentCameraPosForAnimation = cameraController::LEFTPOS;
		}
		//if the cameras is on the back position the cue accordingly
		else if (cameraController::currerntCameraPos == cameraController::RIGHTPOS)
		{
			poolCueGameObject->ReturnPhysicsBody()->AddForce(glm::vec3(-500.f, 0, 0));
			currentCameraPosForAnimation = cameraController::RIGHTPOS;
		}

		//DIAGONALS
		//if the cameras is on the back position the cue accordingly
		else if (cameraController::currerntCameraPos == cameraController::DIAGONALBACKLEFT)
		{
			//this will move the pool to the white ball position
			poolCueGameObject->ReturnPhysicsBody()->AddForce(glm::vec3(500,0,-500));
			currentCameraPosForAnimation = cameraController::DIAGONALBACKLEFT;
		}
		//if the cameras is on the back position the cue accordingly
		else if (cameraController::currerntCameraPos == cameraController::DIAGONALFRONTLEFT)
		{
			//this will move the pool to the white ball position
			poolCueGameObject->ReturnPhysicsBody()->AddForce(glm::vec3(500,0,500));
			currentCameraPosForAnimation = cameraController::DIAGONALFRONTLEFT;
		}
		//if the cameras is on the back position the cue accordingly
		else if (cameraController::currerntCameraPos == cameraController::DIAGONALBACKRIGHT)
		{
			//this will move the pool to the white ball position
			poolCueGameObject->ReturnPhysicsBody()->AddForce(glm::vec3(-500, 0, -500));
			currentCameraPosForAnimation = cameraController::DIAGONALBACKRIGHT;
		}
		//if the cameras is on the back position the cue accordingly
		else if (cameraController::currerntCameraPos == cameraController::DIAGONALFRONTRIGHT)
		{
			//this will move the pool to the white ball position
			poolCueGameObject->ReturnPhysicsBody()->AddForce(glm::vec3(-500,0,500));
			currentCameraPosForAnimation = cameraController::DIAGONALFRONTRIGHT;
		}
     	
	}

	//if the cameras is on the fornt pos or the top pos
	if (currentCameraPosForAnimation==cameraController::FRONTPOS)
	{
		//tell the code that the animation started so that the cue doesnt move more back
		animationStarted = true;

		//this will get the difference between the pool cue and the white ball game object
		float diffZ = (poolCueGameObject->ReturnPhysicsBody()->ReturnPosition().z - whiteBallGameObject->ReturnPhysicsBody()->ReturnPosition().z);
		//if the cue is at the back move him forward
		if (diffZ < -3 && checkForStopAnimation == false)
		{
			//stop the current force
			poolCueGameObject->ReturnPhysicsBody()->ResetForcesForCollision();
			//move the cue forward to the ball
			poolCueGameObject->ReturnPhysicsBody()->AddForce(glm::vec3(0, 0, 2000.f));
			//since the cue has arrived the back and its going to move forward to the ball we need to let the code know that now, we need to check if the cue arrives on the ball or not
			checkForStopAnimation = true;
		}
		//if the cue is at the ball stop the animation, this if will only run after the cue has moved back and forward
		if (diffZ < 1 && checkForStopAnimation == true)
		{
			//stop the animation
			animationStarted = false;
			//stop the animation
			checkForStopAnimation = false;
			//stop every force
			poolCueGameObject->ReturnPhysicsBody()->ResetForcesForCollision();
		}
	}
	//if the cameras is on the back position the cue accordingly
	else if (currentCameraPosForAnimation == cameraController::BACKPOS)
	{
		//tell the code that the animation started so that the cue doesnt move more back
		animationStarted = true;

		//this will get the difference between the pool cue and the white ball game object
		float diffZ = (poolCueGameObject->ReturnPhysicsBody()->ReturnPosition().z - whiteBallGameObject->ReturnPhysicsBody()->ReturnPosition().z);
		//if the cue is at the back move him forward
		if (diffZ > 3 && checkForStopAnimation == false)
		{
			//stop the current force
			poolCueGameObject->ReturnPhysicsBody()->ResetForcesForCollision();
			//move the cue forward to the ball
			poolCueGameObject->ReturnPhysicsBody()->AddForce(glm::vec3(0, 0, -2000.f));
			//since the cue has arrived the back and its going to move forward to the ball we need to let the code know that now, we need to check if the cue arrives on the ball or not
			checkForStopAnimation = true;
		}
		//if the cue is at the ball stop the animation, this if will only run after the cue has moved back and forward
		if (diffZ < 1.5f && checkForStopAnimation == true)
		{
			//stop the animation
			animationStarted = false;
			//stop the animation
			checkForStopAnimation = false;
			//stop every force
			poolCueGameObject->ReturnPhysicsBody()->ResetForcesForCollision();
		}
	}
	//if the cameras is on the back position the cue accordingly
	else if (currentCameraPosForAnimation == cameraController::LEFTPOS)
	{
		//tell the code that the animation started so that the cue doesnt move more back
		animationStarted = true;

		//this will get the difference between the pool cue and the white ball game object
		float diffX = (poolCueGameObject->ReturnPhysicsBody()->ReturnPosition().x - whiteBallGameObject->ReturnPhysicsBody()->ReturnPosition().x);
		//if the cue is at the back move him forward
		if (diffX > 3 && checkForStopAnimation == false)
		{
			//stop the current force
			poolCueGameObject->ReturnPhysicsBody()->ResetForcesForCollision();
			//move the cue forward to the ball
			poolCueGameObject->ReturnPhysicsBody()->AddForce(glm::vec3(-2000.f, 0, 0));
			//since the cue has arrived the back and its going to move forward to the ball we need to let the code know that now, we need to check if the cue arrives on the ball or not
			checkForStopAnimation = true;
		}
		//if the cue is at the ball stop the animation, this if will only run after the cue has moved back and forward
		if (diffX < 1.5f && checkForStopAnimation == true)
		{
			//stop the animation
			animationStarted = false;
			//stop the animation
			checkForStopAnimation = false;
			//stop every force
			poolCueGameObject->ReturnPhysicsBody()->ResetForcesForCollision();
		}
	}
	//if the cameras is on the back position the cue accordingly
	else if (currentCameraPosForAnimation == cameraController::RIGHTPOS)
	{
		//tell the code that the animation started so that the cue doesnt move more back
		animationStarted = true;

		//this will get the difference between the pool cue and the white ball game object
		float diffX = (poolCueGameObject->ReturnPhysicsBody()->ReturnPosition().x - whiteBallGameObject->ReturnPhysicsBody()->ReturnPosition().x);
		//if the cue is at the back move him forward
		if (diffX < -3 && checkForStopAnimation == false)
		{
			//stop the current force
			poolCueGameObject->ReturnPhysicsBody()->ResetForcesForCollision();
			//move the cue forward to the ball
			poolCueGameObject->ReturnPhysicsBody()->AddForce(glm::vec3(2000.f, 0, 0));
			//since the cue has arrived the back and its going to move forward to the ball we need to let the code know that now, we need to check if the cue arrives on the ball or not
			checkForStopAnimation = true;
		}
		//if the cue is at the ball stop the animation, this if will only run after the cue has moved back and forward
		if (diffX > -1.7f && checkForStopAnimation == true)
		{
			//stop the animation
			animationStarted = false;
			//stop the animation
			checkForStopAnimation = false;
			//stop every force
			poolCueGameObject->ReturnPhysicsBody()->ResetForcesForCollision();
		}
	}
	
	//DIAGONALS
	//if the cameras is on the back position the cue accordingly
	else if (cameraController::currerntCameraPos == cameraController::DIAGONALBACKLEFT)
	{
		//tell the code that the animation started so that the cue doesnt move more back
		animationStarted = true;

		//this will get the difference between the pool cue and the white ball game object
		float diffX = (poolCueGameObject->ReturnPhysicsBody()->ReturnPosition().x - whiteBallGameObject->ReturnPhysicsBody()->ReturnPosition().x);
		//this will get the difference between the pool cue and the white ball game object
		float diffZ = (poolCueGameObject->ReturnPhysicsBody()->ReturnPosition().z - whiteBallGameObject->ReturnPhysicsBody()->ReturnPosition().z);
		//if the cue is at the back move him forward
		if (diffZ < -3 && diffX > 3 && checkForStopAnimation == false)
		{
			//stop the current force
			poolCueGameObject->ReturnPhysicsBody()->ResetForcesForCollision();
			//move the cue forward to the ball
			poolCueGameObject->ReturnPhysicsBody()->AddForce(glm::vec3(-2000.f, 0, 2000.f));
			//since the cue has arrived the back and its going to move forward to the ball we need to let the code know that now, we need to check if the cue arrives on the ball or not
			checkForStopAnimation = true;
		}
		//if the cue is at the ball stop the animation, this if will only run after the cue has moved back and forward
		if (diffZ < 1 && diffX < 1.5f && checkForStopAnimation == true)
		{
			//stop the animation
			animationStarted = false;
			//stop the animation
			checkForStopAnimation = false;
			//stop every force
			poolCueGameObject->ReturnPhysicsBody()->ResetForcesForCollision();
		}
	}
	//if the cameras is on the back position the cue accordingly
	else if (cameraController::currerntCameraPos == cameraController::DIAGONALFRONTLEFT)
	{
		//tell the code that the animation started so that the cue doesnt move more back
		animationStarted = true;

		//this will get the difference between the pool cue and the white ball game object
		float diffX = (poolCueGameObject->ReturnPhysicsBody()->ReturnPosition().x - whiteBallGameObject->ReturnPhysicsBody()->ReturnPosition().x);
		//this will get the difference between the pool cue and the white ball game object
		float diffZ = (poolCueGameObject->ReturnPhysicsBody()->ReturnPosition().z - whiteBallGameObject->ReturnPhysicsBody()->ReturnPosition().z);
		//if the cue is at the back move him forward
		if (diffZ > -3 && diffX > 3 && checkForStopAnimation == false)
		{
			//stop the current force
			poolCueGameObject->ReturnPhysicsBody()->ResetForcesForCollision();
			//move the cue forward to the ball
			poolCueGameObject->ReturnPhysicsBody()->AddForce(glm::vec3(-2000.f, 0, -2000.f));
			//since the cue has arrived the back and its going to move forward to the ball we need to let the code know that now, we need to check if the cue arrives on the ball or not
			checkForStopAnimation = true;
		}
		//if the cue is at the ball stop the animation, this if will only run after the cue has moved back and forward
		if (diffZ > 1 && diffX < 1.5f && checkForStopAnimation == true)
		{
			//stop the animation
			animationStarted = false;
			//stop the animation
			checkForStopAnimation = false;
			//stop every force
			poolCueGameObject->ReturnPhysicsBody()->ResetForcesForCollision();
		}
	}
	//if the cameras is on the back position the cue accordingly
	else if (cameraController::currerntCameraPos == cameraController::DIAGONALBACKRIGHT)
	{
		//tell the code that the animation started so that the cue doesnt move more back
		animationStarted = true;

		//this will get the difference between the pool cue and the white ball game object
		float diffX = (poolCueGameObject->ReturnPhysicsBody()->ReturnPosition().x - whiteBallGameObject->ReturnPhysicsBody()->ReturnPosition().x);
		//this will get the difference between the pool cue and the white ball game object
		float diffZ = (poolCueGameObject->ReturnPhysicsBody()->ReturnPosition().z - whiteBallGameObject->ReturnPhysicsBody()->ReturnPosition().z);
		//if the cue is at the back move him forward
		if (diffZ < -3 && diffX < 3 && checkForStopAnimation == false)
		{
			//stop the current force
			poolCueGameObject->ReturnPhysicsBody()->ResetForcesForCollision();
			//move the cue forward to the ball
			poolCueGameObject->ReturnPhysicsBody()->AddForce(glm::vec3(2000.f, 0, 2000.f));
			//since the cue has arrived the back and its going to move forward to the ball we need to let the code know that now, we need to check if the cue arrives on the ball or not
			checkForStopAnimation = true;
		}
		//if the cue is at the ball stop the animation, this if will only run after the cue has moved back and forward
		if (diffZ > -1 && diffX > -1.5f && checkForStopAnimation == true)
		{
			//stop the animation
			animationStarted = false;
			//stop the animation
			checkForStopAnimation = false;
			//stop every force
			poolCueGameObject->ReturnPhysicsBody()->ResetForcesForCollision();
		}
	}
	//if the cameras is on the back position the cue accordingly
	else if (cameraController::currerntCameraPos == cameraController::DIAGONALFRONTRIGHT)
	{
		//tell the code that the animation started so that the cue doesnt move more back
		animationStarted = true;

		//this will get the difference between the pool cue and the white ball game object
		float diffX = (poolCueGameObject->ReturnPhysicsBody()->ReturnPosition().x - whiteBallGameObject->ReturnPhysicsBody()->ReturnPosition().x);
		//this will get the difference between the pool cue and the white ball game object
		float diffZ = (poolCueGameObject->ReturnPhysicsBody()->ReturnPosition().z - whiteBallGameObject->ReturnPhysicsBody()->ReturnPosition().z);
		//if the cue is at the back move him forward
		if (diffZ > 3 && diffX < -3 && checkForStopAnimation == false)
		{
			//stop the current force
			poolCueGameObject->ReturnPhysicsBody()->ResetForcesForCollision();
			//move the cue forward to the ball
			poolCueGameObject->ReturnPhysicsBody()->AddForce(glm::vec3(2000.f, 0, -2000.f));
			//since the cue has arrived the back and its going to move forward to the ball we need to let the code know that now, we need to check if the cue arrives on the ball or not
			checkForStopAnimation = true;
		}
		//if the cue is at the ball stop the animation, this if will only run after the cue has moved back and forward
		if (diffZ < 1.5f && diffX > -1.5f && checkForStopAnimation == true)
		{
			//stop the animation
			animationStarted = false;
			//stop the animation
			checkForStopAnimation = false;
			//stop every force
			poolCueGameObject->ReturnPhysicsBody()->ResetForcesForCollision();
		}
	}
}

void cueController::OnMouseClick()
{
}

void cueController::OnCollisionEnter()
{
}

void cueController::OnTriggerEnter()
{
}
