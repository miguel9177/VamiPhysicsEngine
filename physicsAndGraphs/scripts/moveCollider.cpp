#include "moveCollider.h"
float moveCollider::speed;
Collider* moveCollider::colliderObjectToMove;

void moveCollider::Update()
{
	
	if (ButtonsPressed::specialKeys[GLUT_KEY_UP] == true)
		colliderObjectToMove->offsetOfColliderPosition = colliderObjectToMove->offsetOfColliderPosition + glm::vec3(0, 0, 0.05);
	//if the arrow down is clicked, move the particle bottom
	if (ButtonsPressed::specialKeys[GLUT_KEY_DOWN] == true)
		colliderObjectToMove->offsetOfColliderPosition = colliderObjectToMove->offsetOfColliderPosition + glm::vec3(0, 0, -0.05);
	//if the arrow left is clicked, move the particle left
	if (ButtonsPressed::specialKeys[GLUT_KEY_LEFT] == true)
		colliderObjectToMove->offsetOfColliderPosition = colliderObjectToMove->offsetOfColliderPosition + glm::vec3(-0.05, 0, 0);
	//if the arrow right is clicked, move the particle right
	if (ButtonsPressed::specialKeys[GLUT_KEY_RIGHT] == true)
		colliderObjectToMove->offsetOfColliderPosition = colliderObjectToMove->offsetOfColliderPosition + glm::vec3(0.05, 0, 0);
	//if the user clicked space go up
	if (ButtonsPressed::keys[32] == true)
		colliderObjectToMove->offsetOfColliderPosition = colliderObjectToMove->offsetOfColliderPosition + glm::vec3(0, 0.05, 0);
	//if the user clicked CTRL go down
	if (ButtonsPressed::specialKeys[GLUT_KEY_CTRL_L] == true)
		colliderObjectToMove->offsetOfColliderPosition = colliderObjectToMove->offsetOfColliderPosition + glm::vec3(0, -0.05, 0);
	
	//scale the collider
	if (ButtonsPressed::keys['q'] == true || ButtonsPressed::keys['Q'] == true)
		colliderObjectToMove->SetSize(colliderObjectToMove->ReturnSize() + glm::vec3(0.05, 0, 0));
	if (ButtonsPressed::keys['e'] == true || ButtonsPressed::keys['E'] == true)
		colliderObjectToMove->SetSize(colliderObjectToMove->ReturnSize() - glm::vec3(0.05, 0, 0));
	if (ButtonsPressed::keys['a'] == true || ButtonsPressed::keys['A'] == true)
		colliderObjectToMove->SetSize(colliderObjectToMove->ReturnSize() + glm::vec3(0,0.05, 0));
	if (ButtonsPressed::keys['d'] == true || ButtonsPressed::keys['D'] == true)
		colliderObjectToMove->SetSize(colliderObjectToMove->ReturnSize() - glm::vec3(0, 0.05, 0));
	if (ButtonsPressed::keys['w'] == true || ButtonsPressed::keys['W'] == true)
		colliderObjectToMove->SetSize(colliderObjectToMove->ReturnSize() + glm::vec3(0, 0, 0.05));
	if (ButtonsPressed::keys['s'] == true || ButtonsPressed::keys['S'] == true)
		colliderObjectToMove->SetSize(colliderObjectToMove->ReturnSize() - glm::vec3(0, 0, 0.05));


	//if clicked on i and debug is on, show information about this object
	if (ButtonsPressed::keys['p'] == true || ButtonsPressed::keys['P'] == true && GameEngine::IsDebugModeOn())
	{
		system("cls");
		std::cout << "Collider position: X: " << colliderObjectToMove->offsetOfColliderPosition.x << " Y: " << colliderObjectToMove->offsetOfColliderPosition.y << " Z: " << colliderObjectToMove->offsetOfColliderPosition.z << std::endl;
		std::cout << "Collider Scale: X: " << colliderObjectToMove->ReturnSize().x << " Y: " << colliderObjectToMove->ReturnSize().y << " Z: " << colliderObjectToMove->ReturnSize().z << std::endl;
	}
}
