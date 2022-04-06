#include "SphereRigidBody.h"

//initializes every variable and calls the Create object function. takes filename as an input parameter and passes it to CreatObject function, body type is from the enum of gameobject
SphereRigidBody::SphereRigidBody(const char* TextureLocationName_, glm::vec3 position_, float radius_, glm::vec3 rotation_, float mass_, bool movable_, float coeficientOfRestitution_, float friction_)
{
	stacks = 10; //number of stacks
	slices = 10; //number of slices
	radius = radius_; //get the radius that is gonna ddefine how big a bnall is
	g_position = position_; //initialize the 3D position to 
	g_rotation = rotation_;
	g_scale = glm::vec3(1);
	TextureLocationName = TextureLocationName_;// store the location of the texture
	VAO = VBO = 0;
	sphereVerticesNor = (VertexWithAll*)malloc(sizeof(VertexWithAll) * 121); //total number of vertices = (stacks+1)*(slices +1)
	sphereIndices = (unsigned int*)malloc(sizeof(unsigned int) * 660);
	//this will create the vertices data normals, etc for the sphere
	CreateSpherewithNormal();
	//this will be true if the sphere moves
	movable = movable_;


	//color = color_;
	//firstColor = color;

	//send the information to calculate the inertia, the last value (scale.x) is the radius, and we ont use it if its not a sphere
	float inertia = GetInertiaFromBodyType(BodyTypeOfGameObject::circle, mass_, radius, radius, radius);
	//send the physics body and collider to the game object
	physicsBody = new RigidBody2D(mass_, position_, inertia, rotation_, coeficientOfRestitution_, friction_);

}

//cube destructor
SphereRigidBody::~SphereRigidBody()
{
}

//this will return the matrix for the sphere collider so that they both use the same model matrix
glm::mat4 SphereRigidBody::ReturnModelMatrix()
{
	return ModelMatrix;
}

//this will create the data for the sphere
void SphereRigidBody::CreateSpherewithNormal(void)
{
	int count;
	count = 0;
	for (int i = 0; i <= stacks; ++i) {

		GLfloat V = i / (float)stacks;
		GLfloat phi = V * glm::pi <float>();

		// Loop Through Slices
		for (int j = 0; j <= slices; ++j) {

			GLfloat U = j / (float)slices;  //The parameter along all stacks, it range from 0 to 1
			GLfloat theta = U * (glm::pi <float>() * 2);  // The phi angle, it was converted to radian 

			// Calc The Vertex Positions
			GLfloat x = cosf(theta) * sinf(phi);
			GLfloat y = cosf(phi);
			GLfloat z = sinf(theta) * sinf(phi);

			sphereVerticesNor[count].position = glm::vec3(x * radius, y * radius, z * radius); 
			sphereVerticesNor[count].color = glm::vec3(1,1,1);//currently not being used, since we dot need to edit the color
			sphereVerticesNor[count].textcoord = glm::vec2(x * radius, y * radius);
			sphereVerticesNor[count].normal = glm::vec3(x, y, z); ///Sphere normals

			count++;
		}
	}

	count = 0;
	// Calc The Index Positions
	for (int i = 0; i < slices * stacks + slices; ++i) {

		//The triangle index is explained in the lecture slides
		sphereIndices[count] = i;
		count++;
		sphereIndices[count] = i + slices + 1;
		count++;
		sphereIndices[count] = i + slices;
		count++;

		sphereIndices[count] = i + slices + 1;
		count++;
		sphereIndices[count] = i;
		count++;
		sphereIndices[count] = i + 1;
		count++;
	}

	count = 0;
}

//this will store the ids of vao, vbo and ibo
void SphereRigidBody::SetIDs(unsigned int vao, unsigned int vbo, unsigned int ibo)
{
	VAO = vao;
	VBO = vbo;
	IBO = ibo;
}

//here we are going to generate the buffers for the vbo, and send the data to the shader, we have the vbo vao and ibo from the setIds function
void SphereRigidBody::Setup()
{
	int verCount = 121;
	int triCount = 660;

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexWithAll) * verCount, sphereVerticesNor, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * triCount, sphereIndices, GL_STATIC_DRAW); 
	
	//(location (in this case 4, the location will be received o the shader), number of floats, type, basically saying they are floats, the size of the data, and the offset to the data, in this case we are gonna send the position)
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(VertexWithAll), (GLvoid*)offsetof(VertexWithAll, position));
	glEnableVertexAttribArray(4); //send the information above to the shader, location 4

	//(location (in this case 5, the location will be received o the shader), number of floats, type, basically saying they are floats, the size of the data, and the offset to the data, in this case we are gonna send the normals)
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(VertexWithAll), (GLvoid*)offsetof(VertexWithAll, normal));
	glEnableVertexAttribArray(5); //send the information above to the shader, location 5

	//(location (in this case 6, the location will be received o the shader), number of floats, type, basically saying they are floats, the size of the data, and the offset to the data, in this case we are gonna send the texture coordinates)
	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, sizeof(VertexWithAll), (GLvoid*)offsetof(VertexWithAll, textcoord));
	glEnableVertexAttribArray(6); //send the information above to the shader, location 6
}

//this function will scale and translate the model matrix, (id of model on the shader, d is an offset to move the camera, scale to change the scale of the model, and the offset position)
void SphereRigidBody::updateModelMatrix(unsigned int modelMatLoc, float d)
{

	ModelMatrix = glm::mat4(1.0);

	//ModelMatrix = glm::lookAt(glm::vec3(0.0, 10.0, 15.0), glm::vec3(0.0 + d, 10.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

	ModelMatrix = glm::translate(ModelMatrix, g_position); //apply Sphere Position

	ModelMatrix = glm::rotate(ModelMatrix, (g_rotation.x * glm::pi<float>()) / 180, glm::vec3(1, 0, 0)); //rotate model
	ModelMatrix = glm::rotate(ModelMatrix, (g_rotation.y * glm::pi<float>()) / 180, glm::vec3(0, 1, 0)); //rotate model
	ModelMatrix = glm::rotate(ModelMatrix, (g_rotation.z * glm::pi<float>()) / 180, glm::vec3(0, 0, 1)); //rotate model

	ModelMatrix = glm::scale(ModelMatrix, g_scale); //scale down the model

	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, value_ptr(ModelMatrix));  //send modelview matrix to the shader

}

//function to draw
void SphereRigidBody::Draw()
{
	int triCount = 660;
	//this will set its own material to be active since we are going to draw the object below
	GraphicsEngine::SetActiveTexture(textureId);
	// Draw sphere
	updateModelMatrix(GraphicsEngine::modelMatLoc, 0);
	glUniform1ui(GraphicsEngine::objectLoc, m_object);  //if (object == GraphicsEngine::SPHERE)

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLE_STRIP, triCount, GL_UNSIGNED_INT, sphereIndices);


}

//this will update the popsition of the collider and gameobject by whatever the physics body position is, and then it will check for input
void SphereRigidBody::Update(float deltaTime)
{
	//change the position of the gameobject if the physics body has moved
	if (this->ReturnPhysicsBody() != nullptr)
	{
		g_position = physicsBody->ReturnPosition();
		g_rotation = physicsBody->ReturnOrientation();
	}

	//this will update the colliders positons
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
void SphereRigidBody::CheckForInput()
{
}

//this will let chyange teh texture
void SphereRigidBody::ChangeTexture(unsigned int textureId_)
{
	textureId = textureId_;
}
