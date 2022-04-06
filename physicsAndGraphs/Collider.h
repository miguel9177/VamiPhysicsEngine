#pragma once
#include "glm/glm.hpp"
#include <iostream>

//i have to define this, so that collider contains gameobject and gameobject contains collider, if i
//didnt have this it would create infinite memory, since one would declare one and other another
class GameObject;
struct CollisionInformation;

//this is a parent class of all colliders, it will be overwritten by whatever collider it has
class Collider
{
public:
	//this will be true if its a trigger collider
	bool isTrigger = false;

	//this will store what gameobject has this collider
	GameObject* gameObjectOfCollider;
	//thsi will store the offset collider position (difference from object 0,0,0)
	glm::vec3 offsetOfColliderPosition;

	//thsi will store the offset collider position (difference from object 0,0,0)
	glm::vec3 offsetOfColliderRotation;

	glm::vec3 positionOfCollider;
	glm::vec3 rotationOfCollider;
	
	enum ColliderType
	{
		SPHERECOLLIDER, BOXCOLLIDER, OOBBCOLLIDER, PLANECOLLIDER
	};

	//this will store the current texture of the collider and the initial (this is only used on debug mode)
	unsigned int currentTextureId;
	unsigned int initialTextureId;

	int colliderType;
	~Collider();
	virtual void SetupDraw() = 0;
	virtual void Draw()=0;
	virtual CollisionInformation CollideCheck(Collider&)=0;
	//this will return a float if its a sphere its radius
	virtual float ReturnRadius();
	//this will return a float if its a sphere its radius
	virtual glm::vec3 ReturnSize();

	//this will let me edit the size directly, this is useful for the editing scene so that i can construct the scene by moving and scaling the colider, this is only overwritten by the box collider
	virtual void SetSize(glm::vec3 size_);
	
};

