#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "GameObject.h"
#include "GameEngine.h"
#include "GraphicsEngine.h"
class Cube : public GameObject
{
private:
	


	unsigned int VAO;
	unsigned int VBO;
	unsigned int IBO; //for triangle indices buffer
	unsigned int textureId; //this is going to store the id of this model
	const char* TextureLocationName; //this is going to store the name of the texture

	unsigned int m_object;
	unsigned int m_buffer;

	glm::mat4 ModelMatrix;

	bool isGridCube;
	
public:	
	//this is the constructer that takes a particle mass, a particle position and a bool to check if the cube is movable
	Cube(const char* TextureLocationName_, glm::vec3 position_, glm::vec3 size_, glm::vec3 rotation_, float mass_, bool movable_, float coeficientOfRestitution_, float friction, bool isGridCube_ = false);
	~Cube();

	glm::mat4 ReturnModelMatrix();
	void SetIDs(unsigned int, unsigned int, unsigned int); // (VAO, VBO, IBO) 
	void updateModelMatrix(unsigned int, float);           //(unsigned int modelViewMatLoc,float d)

	void Setup();//do the setup for the graphics stuff

	//this function will draw the cube every frame
	void Draw();
	//this function is the update method that will run every frame, we only call this on objects that arent static
	void Update(float);
	//this is going to check for input (if the player clicks the arrow keys or not)
	void CheckForInput();
	//this will letr me change the texture
	void ChangeTexture(unsigned int);



};

