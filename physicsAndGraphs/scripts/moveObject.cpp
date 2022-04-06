#include "moveObject.h"
float moveObject::speed;
GameObject* moveObject::gameObjectToMove;
//bool a = false;
void moveObject::Update()
{
	/*if (a == false)
		gameObjectToMove->ReturnPhysicsBody()->AddForce(glm::vec3(-200.f, 0, 0));

	a = true;*/
	if (gameObjectToMove == nullptr)
		return;

	if (gameObjectToMove->movable == false)
	{
		return;
	}
	if (ButtonsPressed::keys['w'] == true || ButtonsPressed::keys['W'] == true)
		gameObjectToMove->ReturnPhysicsBody()->AddForce(glm::vec3(0, 0, -speed * gameObjectToMove->ReturnPhysicsBody()->ReturnMass()), glm::vec3(0, 0, 0));
	//if the arrow down is clicked, move the particle bottom
	if (ButtonsPressed::keys['s'] == true || ButtonsPressed::keys['S'] == true)
		gameObjectToMove->ReturnPhysicsBody()->AddForce(glm::vec3(0, 0, speed * gameObjectToMove->ReturnPhysicsBody()->ReturnMass()), glm::vec3(0, 0, 0));
	//if the arrow left is clicked, move the particle left
	if (ButtonsPressed::keys['a'] == true || ButtonsPressed::keys['A'] == true)
		gameObjectToMove->ReturnPhysicsBody()->AddForce(glm::vec3(-speed * gameObjectToMove->ReturnPhysicsBody()->ReturnMass(), 0, 0), glm::vec3(0, 0, 0));
	//if the arrow right is clicked, move the particle right
	if (ButtonsPressed::keys['d'] == true || ButtonsPressed::keys['D'] == true)
		gameObjectToMove->ReturnPhysicsBody()->AddForce(glm::vec3(speed * gameObjectToMove->ReturnPhysicsBody()->ReturnMass(), 0, 0), glm::vec3(0, 0, 0));
	//if the user clicked space go up
	/*if (ButtonsPressed::keys[32] == true)
		gameObjectToMove->ReturnPhysicsBody()->AddForce(glm::vec3(0, speed * gameObjectToMove->ReturnPhysicsBody()->ReturnMass(), 0), glm::vec3(0, 0, 0));
	//if the user clicked CTRL go down
	if (ButtonsPressed::specialKeys[GLUT_KEY_CTRL_L] == true)
		gameObjectToMove->ReturnPhysicsBody()->AddForce(glm::vec3(0, -speed * gameObjectToMove->ReturnPhysicsBody()->ReturnMass(), 0), glm::vec3(0, 0, 0));
	*/
	//THIS WILL MAKE THE PLAYER ROTATE
	//if the q key is clicked, rotate the particle left (anti clockwise, on the z axis)  
	/*if (ButtonsPressed::keys['q'] || ButtonsPressed::keys['Q'] == true)
		gameObjectToMove->ReturnPhysicsBody()->AddRotationalMotionWithoutAddingForce(glm::vec3(speed * gameObjectToMove->ReturnPhysicsBody()->ReturnMass(), 0, 0), glm::vec3(1, 1, 0));
	if (ButtonsPressed::keys['e'] || ButtonsPressed::keys['E'] == true)
		gameObjectToMove->ReturnPhysicsBody()->AddRotationalMotionWithoutAddingForce(glm::vec3(-speed * gameObjectToMove->ReturnPhysicsBody()->ReturnMass(), 0, 0), glm::vec3(1, 1, 0));

	//if the q key is clicked, rotate the particle left (anti clockwise, on the y axis)  
	if (ButtonsPressed::keys['r'] || ButtonsPressed::keys['R'] == true)
		gameObjectToMove->ReturnPhysicsBody()->AddRotationalMotionWithoutAddingForce(glm::vec3(-speed * gameObjectToMove->ReturnPhysicsBody()->ReturnMass(), 0, 0), glm::vec3(1, 0, 1));
	if (ButtonsPressed::keys['t'] || ButtonsPressed::keys['T'] == true)
		gameObjectToMove->ReturnPhysicsBody()->AddRotationalMotionWithoutAddingForce(glm::vec3(speed * gameObjectToMove->ReturnPhysicsBody()->ReturnMass(), 0, 0), glm::vec3(1, 0, 1));

	//if the q key is clicked, rotate the particle left (anti clockwise  
	if (ButtonsPressed::keys['y'] || ButtonsPressed::keys['Y'] == true)
		gameObjectToMove->ReturnPhysicsBody()->AddRotationalMotionWithoutAddingForce(glm::vec3(-speed * gameObjectToMove->ReturnPhysicsBody()->ReturnMass(), 0, 0), glm::vec3(0, 1, 1));
	if (ButtonsPressed::keys['u'] || ButtonsPressed::keys['U'] == true)
		gameObjectToMove->ReturnPhysicsBody()->AddRotationalMotionWithoutAddingForce(glm::vec3(speed * gameObjectToMove->ReturnPhysicsBody()->ReturnMass(), 0, 0), glm::vec3(0, 1, 1));
	*/


	//if clicked on i and debug is on, show information about this object
	if (ButtonsPressed::keys['p'] == true || ButtonsPressed::keys['P'] == true && GameEngine::IsDebugModeOn())
	{
		system("cls");
		std::cout << "Model position: X: " << gameObjectToMove->g_position.x<< "Y: " << gameObjectToMove->g_position.y << "Z: " << gameObjectToMove->g_position.z << std::endl;
		std::cout << "Model Rotation: X: " << gameObjectToMove->g_rotation.x << "Y: " << gameObjectToMove->g_rotation.y << "Z: " << gameObjectToMove->g_rotation.z << std::endl;
	}
}


