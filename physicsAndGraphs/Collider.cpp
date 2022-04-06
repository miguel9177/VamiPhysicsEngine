#include "Collider.h"

Collider::~Collider()
{
}

//if this isnt overwritten by the sphere for example, we will just return 0
float Collider::ReturnRadius()
{
	std::cout << "ERROR RETURN RADIUS FUNCTION WASNT OVERWRITTEN, AND WE ARE CALLING IT FROM SOMEHWERE, PROBABLY FROM SOME COLLISION" << std::endl;
	return 0.0f;
}

glm::vec3 Collider::ReturnSize()
{
	std::cout << "ERROR RETURN SIZE FUNCTION WASNT OVERWRITTEN, AND WE ARE CALLING IT FROM SOMEHWERE, PROBABLY FROM SOME COLLISION" << std::endl;
	return glm::vec3(0,0,0);
}

//this will let me edit the size directly, this is useful for the editing scene so that i can construct the scene by moving and scaling the colider, this is only overwritten by the box collider
void Collider::SetSize(glm::vec3 size_)
{
	std::cout << "SET SIZE IS NOT OVERWRITTEN PROBABLY TRYING TO ACCESS THIS FUNCTION FOR A SPHERE COLLIDER, IN GAME CONSTRUCTOR SCRIPT" << std::endl;
}





