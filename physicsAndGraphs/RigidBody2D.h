#pragma once
#include <glm/gtx/rotate_vector.hpp>
#include <glm/glm.hpp>
#include "PhysicsBody.h"
class RigidBody2D : public PhysicsBody
{
private:
	//VARIABLES FOR THE LINEAR MOTION
	//this is going to store its mass
	float mass;
	//this is going to store its acceleration 
	glm::vec3 linearAcceleration;
	//this is going to store its velocity
	glm::vec3 linearVelocity;
	//this is going to store the forces being applied to the rigidbody
	glm::vec3 totalLinearForce;
	

	//VARIABLES FOR THE ROTATIONAL MOTION
	//this is the measure of inertia (bigger=harder to produce rotational motion)
	float momentOfInertia;
	//this is going to store its angular acceleration 
	glm::vec3 angularAcceleration;
	//this is going to store its angular velocity
	glm::vec3 angularVelocity;
	//this is going to store the forces being applied to the rigidbody
	glm::vec3 torque;

	//value from 0 to 1, 0 means no bounce, 1 means bounce with the same speed it collided
	float coeficientOfRestitution;
	//this will be a value from 0 to 1, the smaller the value the higher the friction, this will only affect collisions
	float friction;

public:
	//this is going to store the rigidbody position
	glm::vec3 position;
	//this is going to store the rigidbody orientation
	glm::vec3 orientation;

	//constructor that assigns every variable (linear motion variables and rotational motion variables
	RigidBody2D(float mass_, glm::vec3 position_, float momentOfInertia_, glm::vec3 orientation_, float coeficientOfRestitution_, float friction_);
	//Destructor
	~RigidBody2D();

	//this will reset all of the forces called once per frame
	void ResetTotalForces();

	//MIGUEL THIS IS ONLY FOR TESTING
	void ResetForcesForCollision();

	//this will add force taking in acount its rotaton
	void AddForce(glm::vec3 forcesToAdd, glm::vec3 positionOfTheForce);
	//this is not currently used on the spheres but it could be used on something else
	void AddForceToWhereObjectIsFacing(glm::vec3 forcesToAdd, glm::vec3 positionOfTheForce = glm::vec3(0, 0, 0));
	//this will rotate the object
	void AddRotationalMotionWithoutAddingForce(glm::vec3 forcesToAdd, glm::vec3 positionOfTheForce);
	//this will add force without taking rotation to consideration (for example gravity)
	void AddForceWithoutRotation(glm::vec3 forcesToAdd);
	
	//this will return the inertia of the rigidbody
	float ReturnInertia();

	void Update(float);

	glm::vec3 ReturnPosition();
	//this returns the velocity, used to draw a line of the movement for example
	glm::vec3 ReturnVelocity();
	//this returns the angular velocity (used for collision response for example)
	glm::vec3 ReturnAngularVelocity();
	//this is going to overwrite the physics body return orientation
	glm::vec3 ReturnOrientation();
	//value from 0 to 1, 0 means no bounce, 1 means bounce with the same speed it collided
	float ReturnCoefficientOfRestitution();	
	int ReturnType();
	float ReturnMass();
	float ReturnFriction();

	//this will let us edit the velocity directily (for example when we do collision response)
	void SetVelocity(glm::vec3 velocity_);
	//this will let us edit the position directily (for example when we fix the interpenetration)
	void SetPosition(glm::vec3 position_);
	//this will let us edit the orientation directily (for example for the pool cue)
    void SetOrientation(glm::vec3 orientation_);
	//this will let us edit the angular velocity directly ( for exampleon collision response)
	void SetAngularVelocity(glm::vec3 angularVelocity_);
};

