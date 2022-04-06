#pragma once
#include"Collider.h"
#include<GL/glew.h>
#include<GL/freeglut.h>
#include<glm/glm.hpp>
#include "GameEngine.h"
#include "ColliderFunctions.h"
class BoxCollider : public Collider
{
private:
	
	
	glm::vec3 size;

	//Graphics STUFF
	unsigned int VAO;//this is the vaoid stored for the opengl
	unsigned int VBO;//this is the vboid stored for the opengl
	unsigned int IBO; //for triangle indices buffer

	//this is going to store wich vao and vbo we are on the graphics engine, so we then can access our object with ease
	unsigned int m_object;
	unsigned int m_buffer;

	//store this mode matrix
	glm::mat4 ModelMatrix;

public:
	
	//constructor, with size of collider, and the offset the collider will have from the game object
	BoxCollider(glm::vec3 size_, glm::vec3 offsetOfColliderPosition_);

	//DEBUG FUNCTIONS START
	//this is going to do the setting up for the collider information
	void SetupDraw();
	//this is going to move the drawing of the collider in debug mode
	void updateModelMatrix(unsigned int modelMatLoc, float d);
	//this is going to draw the collider when in debug mode 
	void Draw();
	//DEBUG FUNCTIONS END
	
	//thios will check wich type of collider the other collider is and then it will call the correct check collision function
	CollisionInformation CollideCheck(Collider&);
	
	//this is going to overwrite Collider parent function with these function, it will simply return a radius so that we can now how big the
	//radius of these collider is, since we want to check if a collision occured
	glm::vec3 ReturnSize();

	//for the scene building its easier if i can edit the size directly
	void SetSize(glm::vec3 size_);
};

