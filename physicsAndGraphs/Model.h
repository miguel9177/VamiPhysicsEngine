#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include "vertex.h"
#include "GameObject.h"
#include "GraphicsEngine.h"
#include "GameEngine.h"

class Model : public GameObject
{
private:
	
	
	//GRAPHICS STUFF START
	VertexWithAll* VerticesData;  //Data with vertices, normal, texCoords
	unsigned int m_object;
	unsigned int m_buffer;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int IBO; //for triangle indices buffer
	unsigned int textureId; //this is going to store the id of this model
	const char* TextureLocationName; //this is going to store the name of the texture
	
	glm::mat4 ModelMatrix;
	//this is going to store the number of vertices that this model will have
	int NumVert;
	//GRAPHICS STUFF END
	
	//takes filename as an input parameter
	void CreateObject(const char *);
public:
	//initializes every variable and calls the Create object function. takes filename as an input parameter and passes it to CreatObject function
	Model(const char* ObjFileName, const char* TextureLocationName_, glm::vec3 position_, glm::vec3 scale_, glm::vec3 rotation_, float mass_, bool movable_, int bodyType_, float coeficientOfRestitution_, float friction_);
	~Model();

	//ALL this voids lets you edit or see the position, rotation and scale
	void SetPosition(glm::vec3 newPos);
	glm::vec3 GetPosition(void);
	void SetScale(glm::vec3 scale_);
	glm::vec3 GetScale(void);
	void SetRotation(glm::vec3 orientation_);
	glm::vec3 GetRotation(void);

	//this will set the ids for the VAO VBO AND IBO
	void SetIDs(unsigned int, unsigned int, unsigned int);

	//this will update the model matrix (move,scale, rotate the matrix)
	void updateModelMatrix(unsigned int modelMatLoc, float d);

	//this will do the setup for the visuals of the object
	void Setup();
	//this will draw the model graphics
	void Draw();
	//this will update the popsition of the collider and gameobject by whatever the physics body position is, and then it will check for input
	void Update(float);
	//this will check fgor input and add force if we move
	void CheckForInput();
	//this will return the model matrix for use in the collider
	glm::mat4 ReturnModelMatrix();

	//this function will let me change texture
	void ChangeTexture(unsigned int textureId_);
};

