#include "Sphere.h"

//Graphics constructor
Sphere::Sphere(const char* TextureLocationName_, glm::vec3 position_, float radius_, glm::vec3 rotation_, float mass_, bool movable_, float coeficientOfRestitution_, float friction_)
{
	stacks = 10; //number of stacks
	slices = 10; //number of slices
	radius = radius_; //get the radius that is gonna ddefine how big a bnall is
	g_position = position_; //initialize the 3D position to 
	g_rotation = rotation_;
	g_scale = glm::vec3(1);
	TextureLocationName = TextureLocationName_;// store the location of the texture
	VAO = VBO = 0;
	sphereVerticesNor = (VertexWtihNormal*)malloc(sizeof(VertexWtihNormal) * 121); //total number of vertices = (stacks+1)*(slices +1)
	sphereIndices = (unsigned int*)malloc(sizeof(unsigned int) * 660);
	//this will create the vertices data normals, etc for the sphere
	CreateSpherewithNormal();
	//this will be true if the sphere moves
	movable = movable_;
	

	//color = color_;
	//firstColor = color;


	//send the physics body and collider to the game object
	physicsBody = new Particle(mass_, position_, coeficientOfRestitution_, friction_);
	
}

//cube destructor
Sphere::~Sphere()
{
}

//this will return the matrix for the sphere collider so that they both use the same model matrix
glm::mat4 Sphere::ReturnModelMatrix()
{
	return ModelMatrix;
}

//this will create the data for the sphere
void Sphere::CreateSpherewithNormal(void)
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

			sphereVerticesNor[count].coords = glm::vec4(x * radius, y * radius, z * radius, 1.0); //6.0 is just small tweak, you can remove it 
			sphereVerticesNor[count].normals = glm::vec3(x, y, z); ///Sphere normals

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
void Sphere::SetIDs(unsigned int vao, unsigned int vbo, unsigned int ibo)
{
	VAO = vao;
	VBO = vbo;
	IBO = ibo;
}

//here we are going to generate the buffers for the vbo, and send the data to the shader, we have the vbo vao and ibo from the setIds function
void Sphere::Setup()
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexWtihNormal) * verCount, sphereVerticesNor, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * triCount, sphereIndices, GL_STATIC_DRAW); 

	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(sphereVerticesNor[0]), 0);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(sphereVerticesNor[0]), (GLvoid*)sizeof(sphereVerticesNor[0].coords));
	glEnableVertexAttribArray(5);
}

//this function will scale and translate the model matrix, (id of model on the shader, d is an offset to move the camera, scale to change the scale of the model, and the offset position)
void Sphere::updateModelMatrix(unsigned int modelMatLoc, float d)
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
void Sphere::Draw()
{
	/*
		glPushMatrix();

		//this is the code to draw a cube
		//move by using the particle position
		glTranslatef(physicsBody->ReturnPosition().x, physicsBody->ReturnPosition().y, physicsBody->ReturnPosition().z);
	
		//if the sphere has a collider move the collider to the physics body position
		if (colliderOfGameObject != nullptr)
		{	//change the collider position
			colliderOfGameObject->colliderPosition = physicsBody->ReturnPosition();
		}

		glColor3f(color.r, color.g,color.b);
	
		//this will draw a sphere with the raius and 20 slices and stacks
		glutSolidSphere(radius, 20, 20);
	
		glEnd();

		//THIS IS THE CODE TO WRITE DEBUG INFORMATION IF DEBUG MODE IS ON
		if (GameEngine::IsDebugModeOn())
		{
		
			//this will draw a line with the object velocity
			glColor3f(1.f, 1.f, 1.f);
			glm::vec3 vel = physicsBody->ReturnVelocity();
			glBegin(GL_LINES);
			glVertex3f(0, 0, 0); //0, 0, 0 is used here as I assume you have a glTranslatef line above, so 0, 0, 0 puts us at the center of the object now
			glVertex3f(vel.x, vel.y, vel.z);
			glEnd();

			glPointSize(5.0f); // so we can see the point better

			//this is going to draw a point on the midle of the object
			glColor3f(0.f, 0.f, 0.f);
			glBegin(GL_POINTS);
			//at the middle of object
			glVertex3f(0, 0, 0);
			glEnd();

			glColor3f(1.f, 1.f, 1.f);
			std::string informationText = "Pos: X-> " + std::to_string(physicsBody->ReturnPosition().x).erase(5, 9) + " Y-> " + std::to_string(physicsBody->ReturnPosition().y).erase(5, 9) + " Z-> " + std::to_string(physicsBody->ReturnPosition().z).erase(5, 9);
			glRasterPos2f(informationText.length() * -0.045, 0.6f + 0.35f);
			for (int i = 0; i < informationText.length(); i++) {
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, informationText[i]);
			}

			//informationText = "Rot: X-> " + std::to_string(physicsBody->ReturnOrientation().x).erase(5, 9) + " Y-> " + std::to_string(physicsBody->ReturnOrientation().y).erase(5, 9) + " Z-> " + std::to_string(physicsBody->ReturnOrientation().z).erase(5, 9);
			//glRasterPos2f(informationText.length() * -0.045, 0.6f + 0.35f);
			//for (int i = 0; i < informationText.length(); i++) {
				//glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, informationText[i]);
			//}

			informationText = "Vel: X-> " + std::to_string(physicsBody->ReturnVelocity().x).erase(5, 9) + " Y-> " + std::to_string(physicsBody->ReturnVelocity().y).erase(5, 9) + " Z-> " + std::to_string(physicsBody->ReturnVelocity().z).erase(5, 9);
			glRasterPos2f(informationText.length() * -0.045, 0.6f + 0.1f);
			for (int i = 0; i < informationText.length(); i++) {
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, informationText[i]);
			}
		}

		glPopMatrix();
	*/

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
void Sphere::Update(float deltaTime)
{
	//change the position of the gameobject if the physics body has moved
	if (this->ReturnPhysicsBody() != nullptr)
	{
		g_position = physicsBody->ReturnPosition();
		//IF WE ARE USING A RIGIDBODY ACTIVATE THIS
		//g_rotation = physicsBody->ReturnOrientation();
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
void Sphere::CheckForInput()
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
		std::cout << "Sphere position: X: " << g_position.x << "Y: " << g_position.y << "Z: " << g_position.z << std::endl;
		std::cout << "Sphere Rotation: X: " << g_rotation.x << "Y: " << g_rotation.y << "Z: " << g_rotation.z << std::endl;
	}
	*/
}

//this function will let me change texture
void Sphere::ChangeTexture(unsigned int textureId_)
{
	textureId = textureId_;
}



