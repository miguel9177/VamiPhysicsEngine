#include "Cube.h"


//this is the constructer to use if we want mass, takes a particle mass, a particle position and a bool to check if the cube is movable, and pass this to the gameobject that is going to create the particle
Cube::Cube(const char* TextureLocationName_, glm::vec3 position_, glm::vec3 size_, glm::vec3 rotation_, float mass_, bool movable_, float coeficientOfRestitution_, float friction_, bool isGridCube_)
{
	movable = movable_;
	g_position = position_;
	g_rotation = rotation_;
	g_scale= size_;
	TextureLocationName = TextureLocationName_;
	VAO = VBO = 0;
	movable = movable_;
	
	//this willl be false everytime, unless this is a grid cube, we need to know this so that we can hide it if we are jnot in debug mode
	isGridCube = isGridCube_;

	//send the physics body and collide to the game object 
	//coefficient of restitution is value from 0 to 1, 0 means no bounce, 1 means bounce with the same speed it collided
	physicsBody = new Particle(mass_, position_, coeficientOfRestitution_,friction_);	
}

//cube destructor
Cube::~Cube()
{
}

//this will return the matrix for the sphere collider so that they both use the same model matrix
glm::mat4 Cube::ReturnModelMatrix()
{
	return ModelMatrix;
}

//this will store the ids of vao, vbo and ibo
void Cube::SetIDs(unsigned int vao, unsigned int vbo, unsigned int ibo)
{
	VAO = vao;
	VBO = vbo;
	IBO = ibo;
}

//here we are going to generate the buffers for the vbo, and send the data to the shader, we have the vbo vao and ibo from the setIds function
void Cube::Setup()
{
	//THIS VERTICES DATA WAS TAKEN FROM https://gist.github.com/kitebizelt/b3b582759c9f7b526953cfbcdcf376ea
	static Vertex cubeVertices[36] =
	{
		{glm::vec4(-1.0f,-1.0f,-1.0f, 1.0), glm::vec2(0.0f, 0.0f)},
		{glm::vec4(-1.0f,-1.0f, 1.0f,1.0), glm::vec2(1.0f, 0.0f)},
		{glm::vec4(-1.0f, 1.0f, 1.0f, 1.0),glm::vec2(1.0f, 1.0f)},// triangle 1 : end

		{glm::vec4(1.0f, 1.0f,-1.0f, 1.0),glm::vec2(0.0f, 1.0f)},// triangle 2 : begin
		{glm::vec4(-1.0f,-1.0f,-1.0f,1.0),glm::vec2(1.0f, 0.0f)},
		{glm::vec4(-1.0f, 1.0f,-1.0f, 1.0),glm::vec2(1.0f, 1.0f)},// triangle 2 : end

		{glm::vec4(1.0f,-1.0f, 1.0f,1.0),glm::vec2(0.0f, 0.0f)},
		{glm::vec4(-1.0f,-1.0f,-1.0f,1.0),glm::vec2(1.0f, 1.0f)},
		{glm::vec4(1.0f,-1.0f,-1.0f,1.0),glm::vec2(0.0f, 1.0f)},

		{glm::vec4(1.0f, 1.0f,-1.0f,1.0),glm::vec2(0.0f, 1.0f)},
		{glm::vec4(1.0f,-1.0f,-1.0f,1.0),glm::vec2(0.0f, 0.0f)},
		{glm::vec4(-1.0f,-1.0f,-1.0f,1.0),glm::vec2(1.0f, 0.0f)},

		{glm::vec4(-1.0f,-1.0f,-1.0f,1.0),glm::vec2(0.0f, 0.0f)},
		{glm::vec4(-1.0f, 1.0f, 1.0f,1.0),glm::vec2(1.0f, 1.0f)},
		{glm::vec4(-1.0f, 1.0f,-1.0f,1.0),glm::vec2(0.0f, 1.0f)},

		{glm::vec4(1.0f,-1.0f, 1.0f,1.0),glm::vec2(0.0f, 0.0f)},
		{glm::vec4(-1.0f,-1.0f, 1.0f,1.0),glm::vec2(1.0f, 0.0f)},
		{glm::vec4(-1.0f,-1.0f,-1.0f,1.0),glm::vec2(1.0f, 1.0f)},

		{glm::vec4(-1.0f, 1.0f, 1.0f,1.0),glm::vec2(0.0f, 1.0f)},
		{glm::vec4(-1.0f,-1.0f, 1.0f,1.0),glm::vec2(0.0f, 0.0f)},
		{glm::vec4(1.0f,-1.0f, 1.0f,1.0),glm::vec2(1.0f, 0.0f)},

		{glm::vec4(1.0f, 1.0f, 1.0f,1.0),glm::vec2(0.0f, 1.0f)},
		{glm::vec4(1.0f,-1.0f,-1.0f,1.0),glm::vec2(1.0f, 0.0f)},
		{glm::vec4(1.0f, 1.0f,-1.0f,1.0),glm::vec2(1.0f, 1.0f)},

		{glm::vec4(1.0f,-1.0f,-1.0f,1.0),glm::vec2(1.0f, 0.0f)},
		{glm::vec4(1.0f, 1.0f, 1.0f,1.0),glm::vec2(0.0f, 1.0f)},
		{glm::vec4(1.0f,-1.0f, 1.0f,1.0),glm::vec2(0.0f, 0.0f)},

		{glm::vec4(1.0f, 1.0f, 1.0f,1.0),glm::vec2(1.0f, 0.0f)},
		{glm::vec4(1.0f, 1.0f,-1.0f,1.0),glm::vec2(1.0f, 1.0f)},
		{glm::vec4(-1.0f, 1.0f,-1.0f,1.0),glm::vec2(0.0f, 1.0f)},

		{glm::vec4(1.0f, 1.0f, 1.0f,1.0),glm::vec2(1.0f, 0.0f)},
		{glm::vec4(-1.0f, 1.0f,-1.0f,1.0),glm::vec2(0.0f, 1.0f)},
		{glm::vec4(-1.0f, 1.0f, 1.0f,1.0),glm::vec2(0.0f, 0.0f)},

		{glm::vec4(1.0f, 1.0f, 1.0f,1.0),glm::vec2(1.0f, 1.0f)},
		{glm::vec4(-1.0f, 1.0f, 1.0f,1.0),glm::vec2(0.0f, 1.0f)},
		{glm::vec4(1.0f,-1.0f, 1.0f,1.0),glm::vec2(1.0f, 0.0f)},

	};

	//this will add a texture to the texture list, and store its id
	textureId = GraphicsEngine::AddTexture(TextureLocationName);

	//get the object and the buffer (vaoId and vboId)
	GraphicsEngine::currentLimitOfVao = GraphicsEngine::currentLimitOfVao + 1;
	GraphicsEngine::currentLimitOfVbo = GraphicsEngine::currentLimitOfVbo + 1;
	m_object = GraphicsEngine::currentLimitOfVao;
	m_buffer = GraphicsEngine::currentLimitOfVbo;
	GraphicsEngine::vao.push_back(0);
	GraphicsEngine::buffer.push_back(0);

	//Create VAO and VBO
	glGenVertexArrays(1, &GraphicsEngine::vao[m_object]);
	glGenBuffers(1, &GraphicsEngine::buffer[m_buffer]);
	//Binding VAO and VBO
	SetIDs(GraphicsEngine::vao[m_object], GraphicsEngine::buffer[m_buffer], 0);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * triCount, sphereIndices, GL_STATIC_DRAW); 

	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(cubeVertices[0]), 0);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(cubeVertices[0]), (void*)sizeof(cubeVertices[0].coords));
	glEnableVertexAttribArray(5);
}



//this function will scale and translate the model matrix, (id of model on the shader, d is an offset to move the camera, scale to change the scale of the model, and the offset position)
void Cube::updateModelMatrix(unsigned int modelMatLoc, float d)
{
	
	ModelMatrix = glm::mat4(1.0);
	//ModelMatrix = glm::lookAt(glm::vec3(0.0, 10.0, 15.0), glm::vec3(0.0 + d, 10.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

	ModelMatrix = glm::translate(ModelMatrix, g_position); //apply Sphere Position
	ModelMatrix = glm::scale(ModelMatrix, g_scale); //scale down the model

	ModelMatrix = glm::rotate(ModelMatrix, (g_rotation.x * glm::pi<float>()) / 180, glm::vec3(1, 0, 0)); //rotate model
	ModelMatrix = glm::rotate(ModelMatrix, (g_rotation.y * glm::pi<float>()) / 180, glm::vec3(0, 1, 0)); //rotate model
	ModelMatrix = glm::rotate(ModelMatrix, (g_rotation.z * glm::pi<float>()) / 180, glm::vec3(0, 0, 1)); //rotate model

	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, value_ptr(ModelMatrix));  //send modelview matrix to the shader
}

//function to draw
void Cube::Draw()
{
	//if its not a grid cube, always draw this object
	if (isGridCube==false)
	{
		//this will set its own material to be active since we are going to draw the object below
		GraphicsEngine::SetActiveTexture(textureId);
		// Draw sphere
		updateModelMatrix(GraphicsEngine::modelMatLoc, 0);
		glUniform1ui(GraphicsEngine::objectLoc, m_object);  //if (object == GraphicsEngine::SPHERE)

		glBindVertexArray(VAO);
		//36 is the size of items on the cube
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	//if its a grid cube and debug mode is one, draw the cube of the grid
	else if(GameEngine::IsDebugModeOn())
	{
		//this will set its own material to be active since we are going to draw the object below
		GraphicsEngine::SetActiveTexture(textureId);
		// Draw sphere
		updateModelMatrix(GraphicsEngine::modelMatLoc, 0);
		glUniform1ui(GraphicsEngine::objectLoc, m_object);  //if (object == GraphicsEngine::SPHERE)

		glBindVertexArray(VAO);
		//36 is the size of items on the cube
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

//this will update the popsition of the collider and gameobject by whatever the physics body position is, and then it will check for input
void Cube::Update(float deltaTime)
{
	//change the position of the gameobject if the physics body has moved
	if (this->ReturnPhysicsBody() != nullptr)
	{
		g_position = physicsBody->ReturnPosition();
		//IF WE ARE USING A RIGIDBODY ACTIVATE THIS
		//g_rotation = physicsBody->ReturnOrientation();
	}

	//this will update the collider position
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

//this is going to check for input (if the player clicks the arrow keys or not), this is called on the update function
void Cube::CheckForInput()
{
	//if the arrow up is clicked, move the particle up
	/*if (GameObject::specialKeys[GLUT_KEY_UP] == true)
		physicsBody->AddForce(glm::vec3(0, 0, -500), glm::vec3(0, 0, 0));
	//if the arrow down is clicked, move the particle bottom
	if (GameObject::specialKeys[GLUT_KEY_DOWN] == true)
		physicsBody->AddForce(glm::vec3(0, 0, 500), glm::vec3(0, 0, 0));
	//if the arrow left is clicked, move the particle left
	if (GameObject::specialKeys[GLUT_KEY_LEFT] == true)
		physicsBody->AddForce(glm::vec3(-500, 0, 0), glm::vec3(0, 0, 0));
	//if the arrow right is clicked, move the particle right
	if (GameObject::specialKeys[GLUT_KEY_RIGHT] == true)
		physicsBody->AddForce(glm::vec3(500, 0, 0), glm::vec3(0, 0, 0));
	//if the user clicked space go up
	if (GameObject::keys[32] == true)
		physicsBody->AddForce(glm::vec3(0, 500, 0), glm::vec3(0, 0, 0));
	//if the user clicked CTRL go down
	if (GameObject::specialKeys[GLUT_KEY_CTRL_L] == true)
		physicsBody->AddForce(glm::vec3(0, -500, 0), glm::vec3(0, 0, 0));

	//if clicked on i and debug is on, show information about this object
	if (GameObject::keys['i'] == true || GameObject::keys['I'] == true && GameEngine::IsDebugModeOn())
	{
		system("cls");
		std::cout << "Cube position: X: " << g_position.x << "Y: " << g_position.y << "Z: " << g_position.z << std::endl;
		std::cout << "Cube Rotation: X: " << g_rotation.x << "Y: " << g_rotation.y << "Z: " << g_rotation.z << std::endl;
	}*/
}

//this function will let me change texture
void Cube::ChangeTexture(unsigned int textureId_)
{
	textureId = textureId_;
}

