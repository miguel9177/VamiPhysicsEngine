#include "FieldObject.h"

unsigned int FieldObject::f_object;
unsigned int FieldObject::f_buffer;
unsigned int FieldObject::VAO;
unsigned int FieldObject::VBO;
unsigned int FieldObject::IBO;

//receive the vao, vbo and ibo
void FieldObject::SetIDs(unsigned int vao, unsigned int vbo, unsigned int ibo)
{
	VAO = vao;
	VBO = vbo;
	IBO = ibo;
}

void FieldObject::Init(const char* TextureLocationName_)
{
	static Vertex fieldVertices[] =
	{
		{glm::vec4(100.0, -10.0, 100.0, 1.0), glm::vec2(8.0, 0.0)},
		{glm::vec4(100.0, -10.0, -100.0, 1.0), glm::vec2(8.0, 8.0)},
		{glm::vec4(-100.0, -10.0, 100.0, 1.0), glm::vec2(0.0, 0.0)},
		{glm::vec4(-100.0, -10.0, -100.0, 1.0), glm::vec2(0.0, 8.0)}
	};

	//this will add the field texture, to the grassTex uniform
	GraphicsEngine::AddTexture(TextureLocationName_, "grassTex");

	///// Create a field  ///////////

   //Create VAO and VBO
	//get the object and the buffer (vaoId and vboId)
	GraphicsEngine::currentLimitOfVao = GraphicsEngine::currentLimitOfVao + 1;
	GraphicsEngine::currentLimitOfVbo = GraphicsEngine::currentLimitOfVbo + 1;
	f_object = GraphicsEngine::currentLimitOfVao;
	f_buffer = GraphicsEngine::currentLimitOfVbo;
	GraphicsEngine::vao.push_back(0);
	GraphicsEngine::buffer.push_back(0);

	glGenVertexArrays(1, &GraphicsEngine::vao[f_object]);
	glGenBuffers(1, &GraphicsEngine::buffer[f_buffer]);
	SetIDs(GraphicsEngine::vao[f_object], GraphicsEngine::buffer[f_buffer], 0);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fieldVertices), fieldVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(fieldVertices[0]), 0);  //layout(location=0) in glm::vec4 fieldCoords;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(fieldVertices[0]), (void*)(sizeof(fieldVertices[0].coords)));  //layout(location=1) in glm::vec2 fieldTexCoords;
	glEnableVertexAttribArray(1);
}

void FieldObject::Draw()
{
	   // Draw field.
   glUniform1ui(GraphicsEngine::objectLoc, f_object);  //if (object == FIELD)
   glBindVertexArray(VAO);
   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void FieldObject::ChangeTexture(unsigned int textureId_)
{
	std::cout << "CHANGE TEXTURE SHOULD NOT BE CALLED FROM FIELD OBJECT" << std::endl;
}
