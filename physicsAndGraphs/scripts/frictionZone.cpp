#include "frictionZone.h"
float frictionZone::frictionForce;
Collider* frictionZone::frictionTriggerCollider;

void frictionZone::Start(Collider* frictionTriggerCollider_)
{
	frictionTriggerCollider = frictionTriggerCollider_;
	frictionForce = 0.1f;
}

void frictionZone::Update()
{
}

void frictionZone::OnTriggerEnter(Collider* triggerCollider, Collider* collider)
{
	//if the collider is triggering with this trigger, add friction of this trigger
	if (triggerCollider == frictionTriggerCollider)
	{
		glm::vec3 currentVelocity = collider->gameObjectOfCollider->ReturnPhysicsBody()->ReturnVelocity();
		currentVelocity *= pow(frictionForce, GameEngine::currentDeltaTime);
		collider->gameObjectOfCollider->ReturnPhysicsBody()->SetVelocity(currentVelocity);		
	}
}
