#pragma once

#include "glm/glm.hpp"
#include <iostream>
namespace RigidBodyType {
	//this will be used to know wicvh body type it is, its necessary to know, since we want to know the inertia depending on the body type
	enum whichBodyType { PARTICLE = 0, RIGIDBODY = 1};
}
class PhysicsBody
{
public:
	//destructor
	~PhysicsBody();
	//this will be overwriten by a particle or a rigidbody
	virtual void ResetTotalForces() = 0;
	//this will be overwriten by a particle or a rigidbody
	virtual void ResetForcesForCollision() = 0;
	//this will be overwriten by a rigidbody
	virtual void AddForce(glm::vec3 forcesToAdd, glm::vec3 positionOfTheForce = glm::vec3(0,0,0))=0;
	//this is not currently used on the spheres but it could be used on something else
	virtual void AddForceToWhereObjectIsFacing(glm::vec3 forcesToAdd, glm::vec3 positionOfTheForce = glm::vec3(0, 0, 0));
	//this will be overwriten by a rigidbody
	virtual void AddRotationalMotionWithoutAddingForce(glm::vec3 forcesToAdd, glm::vec3 positionOfTheForce);
	//this will be overwriten by a rigidbody, and will add force without taking rotation to consideration (gravity, etc)
	virtual void AddForceWithoutRotation(glm::vec3 forcesToAdd) = 0;
	
	
	//this will be overwriten by a particle or a rigidbody
	virtual void Update(float) = 0;

	virtual glm::vec3 ReturnVelocity() = 0;
	virtual glm::vec3 ReturnAngularVelocity();
	virtual glm::vec3 ReturnPosition() = 0;
	virtual int ReturnType()=0;
	virtual float ReturnCoefficientOfRestitution() = 0;
	virtual glm::vec3 ReturnOrientation();
	virtual float ReturnMass() = 0;
	//this will be used for the rigidbody
	virtual float ReturnInertia() = 0;
	virtual float ReturnFriction() = 0;

	virtual void SetVelocity(glm::vec3 velocity_) = 0;
	//this is only used by the rigid body, and not by the particle
	virtual void SetAngularVelocity(glm::vec3 angularVelocity_);
	//this will let us edit the position directily (for example when we fix the interpenetration)
	virtual void SetPosition(glm::vec3 position_)=0;
	//this will let us edit the orientation directily (for example for the pool cue)
	virtual void SetOrientation(glm::vec3 orientation_);

};

