#include "RigidBody2D.h"



//this constructor will setup every variable from linear force and rotational force
RigidBody2D::RigidBody2D(float mass_, glm::vec3 position_, float momentOfInertia_, glm::vec3 orientation_, float coeficientOfRestitution_, float friction_)
{
	//SET THE LINEAR FORCE VARIABLES
	mass = mass_;
	position = position_;
	linearAcceleration = glm::vec3(0, 0, 0);
	linearVelocity = glm::vec3(0, 0, 0);
	totalLinearForce = glm::vec3(0, 0, 0);
	
	//SET THE ROTATIONAL FORCE VARIABLES
	momentOfInertia = momentOfInertia_;
	orientation = orientation_;
	angularAcceleration = glm::vec3(0, 0, 0);
	angularVelocity = glm::vec3(0, 0, 0);
	torque = glm::vec3(0, 0, 0);

	//value from 0 to 1, 0 means no bounce, 1 means bounce with the same speed it collided
	coeficientOfRestitution = coeficientOfRestitution_;
	//this will be a value from 0 to 1, the smaller the value the higher the friction, this will only affect collisions
	friction = friction_;
}

RigidBody2D::~RigidBody2D()
{
}

//We use this to reset all of the forces affecting the object every frame before forces are added to the object.
void RigidBody2D::ResetTotalForces()
{
	//reset the linear force
	totalLinearForce = glm::vec3(0, 0, 0);
	//reset the rotational force
	torque = glm::vec3(0, 0, 0);
}

void RigidBody2D::ResetForcesForCollision()
{
	linearAcceleration = glm::vec3(0, 0, 0);
	linearVelocity = glm::vec3(0, 0, 0);
	totalLinearForce = glm::vec3(0, 0, 0);

	angularAcceleration = glm::vec3(0, 0, 0);
	angularVelocity = glm::vec3(0, 0, 0);
	torque = glm::vec3(0, 0, 0);
}

//this Adds force when when we send the position of the force has well (collision, etc, basically a force that rotates the rigidbody)
void RigidBody2D::AddForce(glm::vec3 forcesToAdd, glm::vec3 positionOfTheForce = glm::vec3(0,0,0))
{
	totalLinearForce += forcesToAdd;

	//formula is torque = crossProduct of force and distance
	//glm::vec3 distance = glm::vec3(0,0,0) - positionOfTheForce; // get the distance between the gameobject and the position of the force
	//we dont need the distance since this is object coordinates so the distance would be (0,0,0)- positionOf force which is the same as doing othing
	torque += glm::cross(forcesToAdd, positionOfTheForce);
}

void RigidBody2D::AddForceToWhereObjectIsFacing(glm::vec3 forcesToAdd, glm::vec3 positionOfTheForce)
{
	totalLinearForce += forcesToAdd;

	//Rotate the linear force for him 
	totalLinearForce = glm::rotate(totalLinearForce, (orientation.x * glm::pi<float>()) / 180, glm::vec3(1, 0, 0));
	totalLinearForce = glm::rotate(totalLinearForce, (orientation.y * glm::pi<float>()) / 180, glm::vec3(0, 1, 0));
	totalLinearForce = glm::rotate(totalLinearForce, (orientation.z * glm::pi<float>()) / 180, glm::vec3(0, 0, 1));

	//formula is torque = crossProduct of force and distance
	//glm::vec3 distance = glm::vec3(0,0,0) - positionOfTheForce; // get the distance between the gameobject and the position of the force
	//we dont need the distance since this is object coordinates so the distance would be (0,0,0)- positionOf force which is the same as doing othing
	torque += glm::cross(forcesToAdd, positionOfTheForce);
}

//this is going to add rotation without any moving speed
void RigidBody2D::AddRotationalMotionWithoutAddingForce(glm::vec3 forcesToAdd, glm::vec3 positionOfTheForce = glm::vec3(0, 0, 0))
{
	//formula is torque = crossProduct of force and distance
	//glm::vec3 distance = glm::vec3(0,0,0) - positionOfTheForce; // get the distance between the gameobject and the position of the force
	//we dont need the distance since this is object coordinates so the distance would be (0,0,0)- positionOf force which is the same as doing othing
	torque += glm::cross(forcesToAdd, positionOfTheForce);
}

//this is going to add force without taking rotation to consideration (gravity etc)
void RigidBody2D::AddForceWithoutRotation(glm::vec3 forcesToAdd)
{
	totalLinearForce += forcesToAdd;
}

float RigidBody2D::ReturnInertia()
{
	return momentOfInertia;
}

void RigidBody2D::Update(float deltaTime)
{

	//THE FORMULA FOR THIS IS A=F/M; THEN P= P + (V)*DELTATIME; THEN V=V+(A)*DELTATIME 
	//add the aceleration by dividing the force by the mass
	linearAcceleration = totalLinearForce / mass;
	//update the velocity for the next update, by adding the acceleration times deltatime
	linearVelocity = linearVelocity + (linearAcceleration)*deltaTime;
	//change the position of the particle by adding the current velocity times delta time 
	position = position + (linearVelocity)*deltaTime;
	//implementing a very drag force (air resistance) so the velocity lowers over time (until it hits zero and the object finally comes to a stop).
	linearVelocity *= pow(0.6f, deltaTime);

	//this will add the rotational acceleration by dividing the acumulated torque by the inertia
	angularAcceleration = torque / momentOfInertia;
	//update the rotational velocity, by adding the rotational acceleration times delta time
	angularVelocity = angularVelocity + (angularAcceleration)*deltaTime;
	//change the orientation (rotate) by adding the current rotational velocity times deltatime
	orientation = orientation + (angularVelocity)*deltaTime;
	//implement a very basic damping power force so the rotational velocity lowers over time until it its 0
	angularVelocity *= pow(0.6f, deltaTime);

	
}

glm::vec3 RigidBody2D::ReturnPosition()
{
	return position;
}

glm::vec3 RigidBody2D::ReturnVelocity()
{
	return linearVelocity;
}

//this returns the angular velocity (used for collision response for example)
glm::vec3 RigidBody2D::ReturnAngularVelocity()
{
	return angularVelocity;
}

glm::vec3 RigidBody2D::ReturnOrientation()
{
	return orientation;
}

float RigidBody2D::ReturnCoefficientOfRestitution()
{
	return coeficientOfRestitution;
}

int RigidBody2D::ReturnType()
{
	return RigidBodyType::RIGIDBODY;
}

float RigidBody2D::ReturnMass()
{
	return mass;
}

float RigidBody2D::ReturnFriction()
{
	return friction;
}

void RigidBody2D::SetVelocity(glm::vec3 velocity_)
{
	linearVelocity = velocity_;
}
//this will let us edit the position directily (for example when we fix the interpenetration)
void RigidBody2D::SetPosition(glm::vec3 position_)
{
	position = position_;
}

//this will let us edit the position directily (for example to rotate the cue)
void RigidBody2D::SetOrientation(glm::vec3 orientation_)
{
	orientation = orientation_;
}

//this will let us edit the angular velocity directly ( for exampleon collision response)
void RigidBody2D::SetAngularVelocity(glm::vec3 angularVelocity_)
{
	angularVelocity = angularVelocity_;
}
