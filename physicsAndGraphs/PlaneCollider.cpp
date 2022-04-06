#include "PlaneCollider.h"

PlaneCollider::PlaneCollider(glm::vec2 size_, glm::vec3 offsetOfColliderPosition_)
{
	//this will store the size of the plane, we put the z to 0 since its suposed to not have depth, since its a plane
	size = glm::vec3(size_.x, 0, size_.y);
	//we dont need the position since it will be changed on the game object, in this case probably at cube
	positionOfCollider = glm::vec3(0, 0, 0);
	//this will store how much the collider will diverse from the game objecy
	offsetOfColliderPosition = offsetOfColliderPosition_;
	//tell the collider parent class wich collider it has
	colliderType = PLANECOLLIDER;
}

void PlaneCollider::SetupDraw()
{
	//radius = radius * gameObjectOfCollider->g_scale.x;
	//if (GameEngine::IsDebugModeOn())
	//{
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
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * triCount, sphereIndices, GL_STATIC_DRAW); 

		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(cubeVertices[0]), 0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(cubeVertices[0]), (void*)sizeof(cubeVertices[0].coords));
		glEnableVertexAttribArray(5);
	//}
}

void PlaneCollider::updateModelMatrix(unsigned int modelMatLoc, float d)
{
	if (GameEngine::IsDebugModeOn())
	{
		ModelMatrix = glm::mat4(1.0);
		//ModelMatrix = glm::lookAt(glm::vec3(0.0, 10.0, 15.0), glm::vec3(0.0 + d, 10.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

		ModelMatrix = glm::translate(ModelMatrix, positionOfCollider); //apply Sphere Position
		ModelMatrix = glm::scale(ModelMatrix, size); //scale down the model

		glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, value_ptr(ModelMatrix));  //send modelview matrix to the shader
	}
}

void PlaneCollider::Draw()
{
	if (GameEngine::IsDebugModeOn())
	{
		//this will set its own material to be active since we are going to draw the object below
		GraphicsEngine::SetActiveTexture(currentTextureId);
		// Draw sphere
		updateModelMatrix(GraphicsEngine::modelMatLoc, 0);
		glUniform1ui(GraphicsEngine::objectLoc, m_object);  //if (object == GraphicsEngine::SPHERE)

		glBindVertexArray(VAO);
		//36 is the size of items on the cube
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

CollisionInformation PlaneCollider::CollideCheck(Collider& collidedObject)
{
	//do a switch case to check wich collider its checking 
	switch (collidedObject.colliderType)
	{
		//this will call the correct function from the ColliderFunctions header and cpp
	case SPHERECOLLIDER:
		return CheckPlaneWithSphere(*this, collidedObject);
		break;
	case BOXCOLLIDER:
		return CheckPlaneWithBox(*this, collidedObject);
		break;
	case OOBBCOLLIDER:
		return CheckPlaneWithOobb(*this, collidedObject);
		break;
	case PLANECOLLIDER:
		return CheckPlaneWithPlane(*this, collidedObject);
		break;
	}
	//this will create a struct of the collision information
	CollisionInformation tempFalseCollisionInfo;
	tempFalseCollisionInfo.collided = false;
	return tempFalseCollisionInfo;
}

glm::vec3 PlaneCollider::ReturnSize()
{
	return size;
}

void PlaneCollider::SetSize(glm::vec3 size_)
{
	size = size_;
}
