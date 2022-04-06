#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include <glm/glm.hpp>
#include "PhysicsBody.h"
#include"Particle.h"
#include "RigidBody2D.h"
#include <vector>
#include "Collider.h"


namespace BodyTypeOfGameObject {
	//this will be used to know wicvh body type it is, its necessary to know, since we want to know the inertia depending on the body type
	enum whichBodyType { square = 0, circle = 1, rectangle = 2 };
}
class GameObject
{
protected:
	//this will store the object (cube sphere etc) position and color
	//glm::vec3 position;
	//glm::vec3 color;
	//create a pointer to a particle
	//Particle* particle;

	//this class is basically a template with functions to be overwritted by rigidbody or particles
	PhysicsBody* physicsBody;
	
	//this will store wich body type this gameobject is (if its a sphere etc)
	int bodyTypeOfGameObject;

	//this will store All of the gameObject colliders
	std::vector<Collider*> collidersOfGameObject;
public:
	glm::vec3 g_position;
	//this is going to be used in case the collision explodes and the object leaves the broad phase grid
	glm::vec3 initialPosition;
	glm::vec3 g_scale;
	glm::vec3 g_rotation;
	//if this is true it means it insnt static, so collisions will move him
	bool movable;
	
	//this is going to store the first color ever i use this for me to be able to change color when a collision happens
	glm::vec3 firstColor;
	
	GameObject();
	
	/*this will be used for functions that dont inherit from gameobject, to be able to access the particle of the game object, for example on
	the ForceGenerator function i need to know wich particles the objects has, so that i cann add the gravity force to the game object*/
	PhysicsBody* ReturnPhysicsBody();

	//this will return what collider we are using for this object
	std::vector<Collider*> ReturnColliders();

	//this will return wich body type it is (sphere, rectangle etc)
	int ReturnBodyType();

	//since som objects dont have access to the collider this functiuon will let for example the game engine to call the draw collider function of this object
	void CallDrawFunctionFromColliders();

	//since som objects dont have access to the collider this functiuon will let for example the game engine to call the setupdraw collider function of this object
	void CallSetupDrawFunctionFromColliders();

	//this will do the math necessary for the inertia depending on the body type
	float GetInertiaFromBodyType(int bodyType, float mass_, float width, float height, float radius = 0);

	virtual glm::mat4 ReturnModelMatrix() = 0;

	virtual ~GameObject();

	virtual void Draw()=0;
	virtual void Setup()=0;

	virtual void Update(float);

	virtual void ChangeTexture(unsigned int)=0;

	//this will update the collider positions
	void UpdateColliderPositions();

	//this will be overwritten, and its used to add colliders to game objects
	void AddCollider(Collider*);	
};

