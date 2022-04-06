#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "GameObject.h"
#include <glm/gtx/rotate_vector.hpp>
#include <string>
#include "GameEngine.h"

//THIS IS NOT BEING USED

class Player : public GameObject
{
private:
	float speed;
	float rotationalSpeed;
	//this will store the width and length of the player object
	float height;
	float width;
	

public:

	//this is the constructer that takes a particle mass, a particle position and a speed, that will define how much force we add when clicking on a key to move 
	Player(float mass_, glm::vec3 position_, glm::vec3 color_, float speed_, float rotationalSpeed_, int bodyType, float width_, float height_, glm::vec3 orientation_, float coeficientOfRestitution_, float radius=0 );
	//destructor
	~Player();
	//class to check for input and move the player
	void CheckForInput();
	//update that will be runed every frame and will update the physics
	void Update(float);
	//this will be called every frame and will update the visuals position
	void Draw();

	//this function will let me change texture
	void ChangeTexture(unsigned int textureId_);	
};

