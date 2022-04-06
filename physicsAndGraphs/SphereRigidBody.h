#pragma once
#include<GL/glew.h>
#include<GL/freeglut.h>
#include<glm/glm.hpp>
#include "GameObject.h"
#include "GameEngine.h"

class SphereRigidBody : public GameObject
{
private:

	//radius of circle
	float radius;
	

	//GRAPHICS STUFF
	VertexWithAll* sphereVerticesNor;  //Sphere vertices data with normals
	unsigned int* sphereIndices;          //Sphere triangle indices    

	int stacks; // nunber of stacks
	int slices; // number of slices

	unsigned int VAO;//this is the vaoid stored for the opengl
	unsigned int VBO;//this is the vboid stored for the opengl
	unsigned int IBO; //for triangle indices buffer
	unsigned int textureId; //this is going to store the id of this model
	const char* TextureLocationName; //this is going to store the name of the texture

	//this is going to store wich vao and vbo we are on the graphics engine, so we then can access our object with ease
	unsigned int m_object;
	unsigned int m_buffer;



	void CreateSpherewithNormal(); //The function creates vertex data and normals 
	//store this mode matrix
	glm::mat4 ModelMatrix;
public:

	//graphics constructor
	SphereRigidBody(const char* TextureLocationName_, glm::vec3 position_, float radius_, glm::vec3 rotation_, float mass_, bool movable_, float coeficientOfRestitution_, float friction_);

	//destructor
	~SphereRigidBody();
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
	//this function will let me change texture
	void ChangeTexture(unsigned int textureId_);


};

