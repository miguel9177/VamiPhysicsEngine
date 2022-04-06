#pragma once
#include "../GameEngine.h"
class wind
{
	//this will store the wind force
	static glm::vec3 windForce;
public:
	//this will store the wind trigger
	static Collider* windTriggerCollider;
	static void Start(Collider* windTriggerCollider_);
	static void Update();
	static void OnTriggerEnter(Collider* triggerCollider, Collider* collider);

};

