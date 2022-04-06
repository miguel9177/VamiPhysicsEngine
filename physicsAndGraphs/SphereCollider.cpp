#include "SphereCollider.h"


SphereCollider::SphereCollider(float radius_, glm::vec3 offsetOfColliderPosition_)
{
	radius = radius_;
	//we dont need the position since it will be changed on the game object, in this case probably at sphere
	positionOfCollider = glm::vec3(0,0,0);
	//this will store how much the collider will diverse from the game objecy
	offsetOfColliderPosition = offsetOfColliderPosition_;
	//tell the collider parent class wich collider it has
	colliderType = SPHERECOLLIDER;	
}



//this will do the setup opengl for the sphere collider, this will only be called if debug mode is on
void SphereCollider::SetupDraw()
{
	//radius = radius * gameObjectOfCollider->g_scale.x;
	//if (GameEngine::IsDebugModeOn())
	//{
		int count;
		int stacks = 10;
		int slices = 10;

		//GRAPHICS STUFF
		//total number of vertices = (stacks+1)*(slices +1)
		VertexWtihNormal* sphereVerticesNor = (VertexWtihNormal*)malloc(sizeof(VertexWtihNormal) * 121);
		//the indices is for the ibo current only being used for the drawing part, since it knows how many triangles it has
		sphereIndices = (unsigned int*)malloc(sizeof(unsigned int) * 660);
		count = 0;

		//THIS WILL CREATE THE SPHERE VERTICES
		{
			
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

					sphereVerticesNor[count].coords = glm::vec4(x * radius, y * radius, z * radius, 1.0); 
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

		int verCount = 121;
		int triCount = 660;

		//this will add a texture to the texture list, and store its id
		currentTextureId = GraphicsEngine::AddTexture("Textures/transparentPink.png");
		initialTextureId = currentTextureId;

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
		VAO = GraphicsEngine::vao[m_object];
		VBO = GraphicsEngine::buffer[m_buffer];

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexWtihNormal) * verCount, sphereVerticesNor, GL_STATIC_DRAW);

		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(sphereVerticesNor[0]), 0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(sphereVerticesNor[0]), (GLvoid*)sizeof(sphereVerticesNor[0].coords));
		glEnableVertexAttribArray(5);
	//}
}

//this is going to draw the collider when in debug mode 
void SphereCollider::Draw()
{
	
	if (GameEngine::IsDebugModeOn())
	{
		int triCount = 660;
		
		//this will set its own material to be active since we are going to draw the object below
		GraphicsEngine::SetActiveTexture(currentTextureId);

		// Draw sphere
		updateModelMatrix(GraphicsEngine::modelMatLoc, 0);
		glUniform1ui(GraphicsEngine::objectLoc, m_object);  //if (object == GraphicsEngine::SPHERE)

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLE_STRIP, triCount, GL_UNSIGNED_INT, sphereIndices);

	}
}

//this function will scale and translate the model matrix, (id of model on the shader, d is an offset to move the camera, scale to change the scale of the model, and the offset position)
void SphereCollider::updateModelMatrix(unsigned int modelMatLoc, float d)
{
	if (GameEngine::IsDebugModeOn())
	{
		ModelMatrix = glm::mat4(1.0);
		//ModelMatrix = glm::lookAt(glm::vec3(0.0, 10.0, 15.0), glm::vec3(0.0 + d, 10.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

		ModelMatrix = glm::translate(ModelMatrix, positionOfCollider); //apply Sphere Position

		ModelMatrix = glm::rotate(ModelMatrix, (gameObjectOfCollider->g_rotation.x * glm::pi<float>()) / 180, glm::vec3(1, 0, 0)); //rotate model
		ModelMatrix = glm::rotate(ModelMatrix, (gameObjectOfCollider->g_rotation.y * glm::pi<float>()) / 180, glm::vec3(0, 1, 0)); //rotate model
		ModelMatrix = glm::rotate(ModelMatrix, (gameObjectOfCollider->g_rotation.z * glm::pi<float>()) / 180, glm::vec3(0, 0, 1)); //rotate model
		
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1)); //scale down the model
		
		glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, value_ptr(ModelMatrix));  //send modelview matrix to the shader
	}
	
}

//thios will check wich type of collider the other collider is and then it will call the correct check collision function
CollisionInformation SphereCollider::CollideCheck(Collider& collidedObject)
{
	//do a switch case to check wich collider its checking 
	switch (collidedObject.colliderType)
	{
		//this will call the correct function from the ColliderFunctions header and cpp
		case SPHERECOLLIDER:
			return CheckSphereWithSphere(*this, collidedObject);
			break;
		case BOXCOLLIDER:
			return CheckBoxWithSphere(collidedObject, *this);
			break;
		case OOBBCOLLIDER:
			return CheckSphereWithOobb(*this, collidedObject);
			break;
		case PLANECOLLIDER:
			return CheckPlaneWithSphere(collidedObject, *this);
			break;
	}
	//this will create a struct of the collision information
	CollisionInformation tempFalseCollisionInfo;
	tempFalseCollisionInfo.collided = false;
	return tempFalseCollisionInfo;
}


//this will return the radius of the sphere
float SphereCollider::ReturnRadius()
{
	return radius;
}






