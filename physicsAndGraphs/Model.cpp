#include "Model.h"
#include "OBJloader.h"
#include <fstream>
#include <GL/glew.h>
#include <GL/freeglut.h>

//initializes every variable and calls the Create object function. takes filename as an input parameter and passes it to CreatObject function, body type is from the enum of gameobject
Model::Model(const char* ObjFileName, const char* TextureLocationName_, glm::vec3 position_, glm::vec3 scale_, glm::vec3 rotation_, float mass_, bool movable_, int bodyType_, float coeficientOfRestitution_, float friction_)
{
	g_position = position_;
	g_scale = scale_;
	g_rotation=rotation_;
	TextureLocationName = TextureLocationName_;
	VerticesData = NULL; 
	NumVert = 0;
	VAO = VBO = 0;
	//call the function to create the model vertices, but not do the opengl stuff
	CreateObject(ObjFileName);
	

	movable = movable_;

	//send the information to calculate the inertia, the last value (scale.x) is the radius, and we ont use it if its not a sphere
	float inertia = GetInertiaFromBodyType(bodyType_, mass_, scale_.x, scale_.y, scale_.x);
	physicsBody = new RigidBody2D(mass_, position_,inertia, rotation_, coeficientOfRestitution_, friction_);
	
	//SetIDs(GraphicsEngine::vao[GraphicsEngine::MYMODEL], GraphicsEngine::buffer[GraphicsEngine::MYMODEL_VERTICES], 0);
}

Model::~Model()
{
	free(VerticesData);
}


void Model::CreateObject(const char* name)
{
	//this creates an vector(basically an array) of VertexWithAll, and fills it with the obj information by using the ObjLoader "api"
	std::vector<VertexWithAll> mesh = loadOBJ(name); //Import obj file data into a vector array
	
	NumVert = mesh.size();

	this->VerticesData = new VertexWithAll[NumVert];

	//size t creates an unsigned integer, whith the maximum bits available, in this case 64 bits
	for (size_t i = 0; i < NumVert; i++)
	{
		this->VerticesData[i] = mesh[i];
	}
}


void Model::SetPosition(glm::vec3 newPos)
{
	g_position = newPos;
}

glm::vec3 Model::GetPosition(void)
{
	return g_position;
}

void Model::SetScale (glm::vec3 scale_)
{
	g_scale = scale_;
}

glm::vec3 Model::GetScale(void)
{
	return g_scale;
}

void Model::SetRotation(glm::vec3 rotation_)
{
	g_rotation = rotation_;
}

glm::vec3 Model::GetRotation(void)
{
	return g_rotation;
}

//this will return the matrix for the sphere collider so that they both use the same model matrix
glm::mat4 Model::ReturnModelMatrix()
{
	return ModelMatrix;
}

//this function will let me change texture
void Model::ChangeTexture(unsigned int textureId_)
{
	textureId = textureId_;
}



//receive the vao, vbo and ibo
void Model::SetIDs(unsigned int vao, unsigned int vbo, unsigned int ibo)
{
	VAO = vao;
	VBO = vbo;
	IBO = ibo;
}

//here we are going to generate the buffers for the vbo, and send the data to the shader, we have the vbo vao and ibo from the setIds function
void Model::Setup()
{
	

	//this will add a texture to the texture list, and store its id
	textureId = GraphicsEngine::AddTexture(TextureLocationName);

	//get the object and the buffer (vaoId and vboId)
	GraphicsEngine::currentLimitOfVao = GraphicsEngine::currentLimitOfVao + 1;
	GraphicsEngine::currentLimitOfVbo = GraphicsEngine::currentLimitOfVbo + 1;
	m_object = GraphicsEngine::currentLimitOfVao;
	m_buffer= GraphicsEngine::currentLimitOfVbo;
	GraphicsEngine::vao.push_back(0);
	GraphicsEngine::buffer.push_back(0);

	//CREATE A MODEL, IN THIS CAS E A TABLE FROM A OBJ FILE
	glGenVertexArrays(1, &GraphicsEngine::vao[m_object]);
	glGenBuffers(1, &GraphicsEngine::buffer[m_buffer]);
	SetIDs(GraphicsEngine::vao[m_object], GraphicsEngine::buffer[m_buffer], 0);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//send the date to the buffer, and below we star sending it to the shader
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexWithAll) * NumVert, VerticesData, GL_STATIC_DRAW);

	//(location (in this case 4, the location will be received o the shader), number of floats, type, basically saying they are floats, the size of the data, and the offset to the data, in this case we are gonna send the position)
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(VertexWithAll), (GLvoid*)offsetof(VertexWithAll, position));
	glEnableVertexAttribArray(4); //send the information above to the shader, location 4

	//(location (in this case 5, the location will be received o the shader), number of floats, type, basically saying they are floats, the size of the data, and the offset to the data, in this case we are gonna send the normals)
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(VertexWithAll), (GLvoid*)offsetof(VertexWithAll, normal));
	glEnableVertexAttribArray(5); //send the information above to the shader, location 5

	//(location (in this case 6, the location will be received o the shader), number of floats, type, basically saying they are floats, the size of the data, and the offset to the data, in this case we are gonna send the texture coordinates)
	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, sizeof(VertexWithAll), (GLvoid*)offsetof(VertexWithAll, textcoord));
	glEnableVertexAttribArray(6); //send the information above to the shader, location 6



	/*int verCount = 121;
	int triCount = 660;
   glBindVertexArray(VAO);
   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(VertexWtihNormal) * verCount, sphereVerticesNor, GL_STATIC_DRAW);  ///please note the change
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * triCount, sphereIndices, GL_STATIC_DRAW); ///please note the change
   glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(sphereVerticesNor[0]), 0);  //layout(location=4) in vec4 fieldCoords;
   glEnableVertexAttribArray(2);
   glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(sphereVerticesNor[0]), (GLvoid*)sizeof(sphereVerticesNor[0].normals));
   glEnableVertexAttribArray(3);*/
}

//this function will scale and translate the model matrix, (id of model on the shader, d is an offset to move the camera, scale to change the scale of the model, and the offset position)
void Model::updateModelMatrix(unsigned int modelMatLoc, float d)
{
	ModelMatrix = glm::mat4(1.0);
						// eye				,	center				 ,	up
	//ModelMatrix = glm::lookAt(glm::vec3(0.0, 10.0, 15.0), glm::vec3(0.0 + d, 10.0, 0.0), glm::vec3(0.0, 1.0, 0.0)); //camera matrix, apply first

	ModelMatrix = glm::translate(ModelMatrix, GetPosition());

	ModelMatrix = glm::rotate(ModelMatrix, (g_rotation.x * glm::pi<float>()) / 180, glm::vec3(1, 0, 0)); //rotate model
	ModelMatrix = glm::rotate(ModelMatrix, (g_rotation.y * glm::pi<float>()) / 180, glm::vec3(0, 1, 0)); //rotate model
	ModelMatrix = glm::rotate(ModelMatrix, (g_rotation.z * glm::pi<float>()) / 180, glm::vec3(0, 0, 1)); //rotate model

	
	ModelMatrix = glm::scale(ModelMatrix, g_scale); //scale down the model


	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, value_ptr(ModelMatrix));//send modelview matrix to the shader

	
}

void Model::Draw()
{
	//this will set its own material to be active since we are going to draw the object below
	GraphicsEngine::SetActiveTexture(textureId);
	//Draw my Model
	//call the function that will scale and translate the model matrix, (id of model on the shader, d is an offset to move the camera, scale to change the scale of the model, and the offset position)
	updateModelMatrix(GraphicsEngine::modelMatLoc, 0);
	glUniform1ui(GraphicsEngine::objectLoc, m_object); //if(object == GraphicsEngine::MYMODEL

	//bind the vao of the objects and then draw the object, numvert is the total of the vertices
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, NumVert);

}

void Model::Update(float deltaTime)
{
	//change the position of the gameobject if the physics body has moved
	if (this->ReturnPhysicsBody() != nullptr)
	{
		g_position = physicsBody->ReturnPosition();
		g_rotation = physicsBody->ReturnOrientation();
	}
		
	//this will update the collider positions
	UpdateColliderPositions();

	//if this object is movable, call the function to check for input and then move
	if (movable)
	{
		CheckForInput();
	}

	//call the particle update method, wich will calculate the new aceleration, velocity and position
	physicsBody->Update(deltaTime);

	//reset the force of the particle (this cube) to 0, since we are going to add movement if we clicked an arrow key
	physicsBody->ResetTotalForces();
}

void Model::CheckForInput()
{
	//if the arrow up is clicked, move the particle up
	/*if (GameObject::specialKeys[GLUT_KEY_UP] == true)
		physicsBody->AddForce(glm::vec3(0, 0, -50), glm::vec3(0, 0, 0));
	//if the arrow down is clicked, move the particle bottom
	if (GameObject::specialKeys[GLUT_KEY_DOWN] == true)
		physicsBody->AddForce(glm::vec3(0, 0, 50), glm::vec3(0, 0, 0));
	//if the arrow left is clicked, move the particle left
	if (GameObject::specialKeys[GLUT_KEY_LEFT] == true)
		physicsBody->AddForce(glm::vec3(-50, 0, 0), glm::vec3(0, 0, 0));
	//if the arrow right is clicked, move the particle right
	if (GameObject::specialKeys[GLUT_KEY_RIGHT] == true)
		physicsBody->AddForce(glm::vec3(50, 0, 0), glm::vec3(0, 0, 0));
	//if the user clicked space go up
	if (GameObject::keys[32] == true)
		physicsBody->AddForce(glm::vec3(0, 50, 0), glm::vec3(0, 0, 0));
	//if the user clicked CTRL go down
	if (GameObject::specialKeys[GLUT_KEY_CTRL_L] == true)
		physicsBody->AddForce(glm::vec3(0, -50, 0), glm::vec3(0, 0, 0));

	//THIS WILL MAKE THE PLAYER ROTATE
	//if the q key is clicked, rotate the particle left (anti clockwise, on the z axis)  
	if (GameObject::keys['q'] || GameObject::keys['Q'] == true)
		physicsBody->AddRotationalMotionWithoutAddingForce(glm::vec3(50, 0, 0), glm::vec3(1, 1, 0));
	if (GameObject::keys['e'] || GameObject::keys['E'] == true)
		physicsBody->AddRotationalMotionWithoutAddingForce(glm::vec3(-50, 0, 0), glm::vec3(1, 1, 0));

	//if the q key is clicked, rotate the particle left (anti clockwise, on the y axis)  
	if (GameObject::keys['r'] || GameObject::keys['R'] == true)
		physicsBody->AddRotationalMotionWithoutAddingForce(glm::vec3(-50, 0, 0), glm::vec3(1, 0, 1));
	if (GameObject::keys['t'] || GameObject::keys['T'] == true)
		physicsBody->AddRotationalMotionWithoutAddingForce(glm::vec3(50, 0, 0), glm::vec3(1, 0, 1));
	
	//if the q key is clicked, rotate the particle left (anti clockwise  
	if (GameObject::keys['y'] || GameObject::keys['Y'] == true)
		physicsBody->AddRotationalMotionWithoutAddingForce(glm::vec3(-50, 0, 0), glm::vec3(0, 1, 1));
	if (GameObject::keys['u'] || GameObject::keys['U'] == true)
		physicsBody->AddRotationalMotionWithoutAddingForce(glm::vec3(50, 0, 0), glm::vec3(0, 1, 1));

	//if clicked on i and debug is on, show information about this object
	if (GameObject::keys['i'] == true || GameObject::keys['I'] == true && GameEngine::IsDebugModeOn())
	{
		system("cls");
		std::cout << "Model position: X: " << g_position.x << "Y: " << g_position.y << "Z: " << g_position.z << std::endl;
		std::cout << "Model Rotation: X: " << g_rotation.x << "Y: " << g_rotation.y << "Z: " << g_rotation.z << std::endl;
	}*/
}

