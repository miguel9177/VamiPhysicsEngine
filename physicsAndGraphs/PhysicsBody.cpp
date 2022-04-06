#include "PhysicsBody.h"



PhysicsBody::~PhysicsBody()
{
}

void PhysicsBody::AddForceToWhereObjectIsFacing(glm::vec3 forcesToAdd, glm::vec3 positionOfTheForce)
{
    std::cout << "FUNCTION ADDFORCETOWHEREOBJECTISFACING IS NOT OVERWRITTENNED ON THE PARTICLE CLASS, PLS DO NOT ACCESS THIS IN A PARTICLE" << std::endl;
}

/*This will add rotation without moving the object*/
void PhysicsBody::AddRotationalMotionWithoutAddingForce(glm::vec3 forcesToAdd, glm::vec3 positionOfTheForce)
{
}

void PhysicsBody::AddForceWithoutRotation(glm::vec3 forcesToAdd)
{
    std::cout << "AddForceWithoutRotation function from physicsBody is being called without being overwritten (probably calling it, while using a particle instead of a rigidbody)" << std::endl;
}

//this will only be overwritten by the particle
glm::vec3 PhysicsBody::ReturnAngularVelocity()
{
    return glm::vec3(0,0,0);
}

/*this will be overwritten by the physics bodyand its supposed to only be used by it
so only call this if its a rigidbody, but if we do call this for a particle that doesnt have rotation
it will return (0,0,0)
*/
glm::vec3 PhysicsBody::ReturnOrientation()
{
    std::cout << "The Return Orientation hasnt been overwritten (probably using a particle and trying to get orientation" << std::endl;
    return glm::vec3(0,0,0);
}

//this will only be used by the rigidbody
void PhysicsBody::SetAngularVelocity(glm::vec3 angularVelocity_)
{
}

void PhysicsBody::SetOrientation(glm::vec3 position_)
{
    std::cout << "Set orientation is not overwritten, this means you are accessing this function from a particle" << std::endl;
}


