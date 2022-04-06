#pragma once

#include <glm/glm.hpp>

#include <string>
#include "PhysicsBody.h"
//this is a particle class, a particle its basically an object with mass but no size
class Particle : public PhysicsBody
{
private:
	//this is going to store its mass
	float mass;
	//this is going to store its acceleration 
	glm::vec3 acceleration;
	//this is going to store its velocity
	glm::vec3 velocity;
	//this is going to store the forces being applied to the particle
	glm::vec3 totalLinearForce;

	//value from 0 to 1, 0 means no bounce, 1 means bounce with the same speed it collided
	float coeficientOfRestitution;
	//this will be a value from 0 to 1, the higher the value the smaller the friction, this will only affect collisions
	float friction;
public:
	//this is going to store the particle position
	glm::vec3 position;

	//constructer that thakes mass and position, because this are the only variables we define from begining
	Particle(float mass_, glm::vec3 position_, float coeficientOfRestitution_, float friction_);

	//destructor
	~Particle();

	//this will return the mass, since its private
	float ReturnMass();

	//this will return the type of physics body
	int ReturnType();
	
	//this is needed for the collision responses, although this hasnt a inertia since its a particle and not a rigidbody, but it will return 1
	float ReturnInertia();

	//this function will reset all of the forces affecting the particle to 0 
	void ResetTotalForces();
	
	//MIGUEL THIS IS ONLY FOR TESTING
	void ResetForcesForCollision();

	/*this function will add all of the forces affecting the particle
	it has 2 glm but the second is to ignore, we do not fill it*/
	void AddForce(glm::vec3, glm::vec3);

	//this does the same as add force, i have 2 functions trhat do the same, since on the rigid body, this function does something else, and
	//since we have the physicsbody parent class if we call AddForceWithouRotation, we want it to affect the object even if it isnt a rigid body
	void AddForceWithoutRotation(glm::vec3);

	//this is the update function
	void Update(float);

	//this returns the velocity, used to draw a line of the movement for example
	glm::vec3 ReturnVelocity();

	//this returns the velocity, used to draw a line of the movement for example
	glm::vec3 ReturnPosition();
	
	float ReturnFriction();

	//value from 0 to 1, 0 means no bounce, 1 means bounce with the same speed it collided
	float ReturnCoefficientOfRestitution();
	//this will let us edit the velocity directily (for example when we do collision response)
	void SetVelocity(glm::vec3 velocity_);
	//this will let us edit the position directily (for example when we fix the interpenetration)
	void SetPosition(glm::vec3 position_);
};

