#include "Particle.h"




/*this constructor will assign every value of the particle, pass mass and position because ts the only values we know when initializing
* this particle, the rest we initialize it to 0, because we will add the forces later
*/
Particle::Particle(float mass_, glm::vec3 position_, float coeficientOfRestitution_, float friction_)
{
	mass = mass_;
	position = position_;
	acceleration = glm::vec3(0, 0, 0);
	velocity = glm::vec3(0, 0, 0);
	totalLinearForce = glm::vec3(0, 0, 0);

	//value from 0 to 1, 0 means no bounce, 1 means bounce with the same speed it collided
	coeficientOfRestitution = coeficientOfRestitution_;
	//this will be a value from 0 to 1, the smaller the value the higher the friction, this will only affect collisions
	friction = friction_;
}

Particle::~Particle()
{
}

//return the mass, since its private
float Particle::ReturnMass()
{
	return mass;
}

int Particle::ReturnType()
{
	return RigidBodyType::PARTICLE;
}

//this is needed for the collision responses, although this hasnt a inertia since its a particle and not a rigidbody, but it will return 1
float Particle::ReturnInertia()
{
	return 1.0f;
}

//We use this to reset the all of the forces affecting the object every frame before forces are added to the object.
void Particle::ResetTotalForces()
{
	totalLinearForce = glm::vec3(0,0,0);
}

void Particle::ResetForcesForCollision()
{
	acceleration = glm::vec3(0, 0, 0);
	velocity = glm::vec3(0, 0, 0);
	totalLinearForce = glm::vec3(0, 0, 0);
}

/*this function will add the forces to the total forces variable, this function will be called more then once to add all of the forces
*It has a second vectore called ignore, which the object really is top ignore, since we wont even call it when constructing it 
* hes just there because physics body add force virtual function needs 2 parameters (forces to add and position of the force), 
* it needs 2 parameters because of the rigidbody
*/
void Particle::AddForce(glm::vec3 forcesToAdd, glm::vec3 IGNORE = glm::vec3(0,0,0))
{
	totalLinearForce += forcesToAdd;
}

void Particle::AddForceWithoutRotation(glm::vec3 forcesToAdd)
{
	totalLinearForce += forcesToAdd;
}

//Update function, receives deltatime to be able to do movement that affects the same not relying on fps
void Particle::Update(float deltaTime)
{
	//THE FORMULA FOR THIS IS A=F/M; THEN P= P + (V)*DELTATIME; THEN V=V+(A)*DELTATIME 
	//add the aceleration by dividing the force by the mass
	acceleration = totalLinearForce / mass;
	//update the velocity for the next update, by adding the acceleration times deltatime
	velocity = velocity + (acceleration)*deltaTime;
	//change the position of the particle by adding the current velocity times delta time 
	position = position + (velocity) * deltaTime;
	//implementing a very basic damping force so the velocity lowers over time (until it hits zero and the object finally comes to a stop).
	velocity *= pow(0.15f, deltaTime);
	
}


//this returns the velocity, used to draw a line of the movement for example
glm::vec3 Particle::ReturnVelocity()
{
	return velocity;
}

glm::vec3 Particle::ReturnPosition()
{
	return position;
}

float Particle::ReturnFriction()
{
	return friction;
}

float Particle::ReturnCoefficientOfRestitution()
{
	return coeficientOfRestitution;
}

void Particle::SetVelocity(glm::vec3 velocity_)
{
	velocity = velocity_;
}
//this will let us edit the position directily (for example when we fix the interpenetration)
void Particle::SetPosition(glm::vec3 position_)
{
	position = position_;
}
