#include "ButtonsPressed.h"
/*these are static so only one copy of these variables exists on the app, the child class all have access to this copy
and this willcreate the one instance the class holds.*/
std::map<char, bool> ButtonsPressed::keys;
std::map<int, bool> ButtonsPressed::specialKeys;

bool ButtonsPressed::leftMouseButton;
bool ButtonsPressed::rightMouseButton;
bool ButtonsPressed::middleMouseButton;

glm::vec2 ButtonsPressed::mousePos;

bool ButtonsPressed::IsLeftMouseButtonClicking()
{
	return leftMouseButton;
}

bool ButtonsPressed::IsRightMouseButtonClicking()
{
	return rightMouseButton;
}

bool ButtonsPressed::IsMiddleMouseButtonClicking()
{
	return middleMouseButton;
}

glm::vec2 ButtonsPressed::ReturnMousePos()
{
	return mousePos;
}

void ButtonsPressed::SetLeftMouseButtonClicking(bool isClicking)
{
	leftMouseButton=isClicking;
}

void ButtonsPressed::SetRightMouseButtonClicking(bool isClicking)
{
	rightMouseButton = isClicking;
}

void ButtonsPressed::SetMiddleMouseButtonClicking(bool isClicking)
{
	middleMouseButton = isClicking;
}

void ButtonsPressed::SetMousePos(glm::vec2 positionOfMouse_)
{
	mousePos = positionOfMouse_;
}
