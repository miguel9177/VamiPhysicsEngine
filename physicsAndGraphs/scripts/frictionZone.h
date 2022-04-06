#pragma once
#include "../GameEngine.h"
class frictionZone
{
	//this will store the fricion force from (0 to 1)
	static float frictionForce;
public:
	//this will store the wind trigger
	static Collider* frictionTriggerCollider;
	static void Start(Collider* frictionTriggerCollider_);
	static void Update();
	static void OnTriggerEnter(Collider* triggerCollider, Collider* collider);
};

