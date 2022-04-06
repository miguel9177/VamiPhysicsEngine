#include "wind.h"
Collider* wind::windTriggerCollider;
glm::vec3 wind::windForce;

void wind::Start(Collider* windTriggerCollider_)
{
	windTriggerCollider = windTriggerCollider_;
	windForce = glm::vec3(0.03f, 0, 0);
}

void wind::Update()
{
}

void wind::OnTriggerEnter(Collider* triggerCollider, Collider* collider)
{
	if (triggerCollider == windTriggerCollider)
	{
		//we do dividing by, since the heviar it is the less it suffers from the wind
		collider->gameObjectOfCollider->ReturnPhysicsBody()->AddForceWithoutRotation((windForce * GameEngine::currentDeltaTime) / collider->gameObjectOfCollider->ReturnPhysicsBody()->ReturnMass());
	}
}
