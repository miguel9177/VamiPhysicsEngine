#include "SkyBox.h"
unsigned int SkyBox::s_object;
unsigned int SkyBox::s_buffer;
unsigned int SkyBox::s_objectBottom;
unsigned int SkyBox::s_bufferBottom;

//unsigned int SkyBox::VAO;
//unsigned int SkyBox::VBO;
unsigned int SkyBox::IBO;
unsigned int SkyBox::textureId;

void SkyBox::SetIDs(unsigned int vao, unsigned int vbo, unsigned int ibo)
{
	//VAO = vao;
	//VBO = vbo;
	//IBO = ibo;
}

void SkyBox::ChangeTexture(unsigned int textureId_)
{
	std::cout << "CHANGE TEXTURE SHOULD NOT BE CALLED FROM SkyBox OBJECT" << std::endl;
}

void SkyBox::InitBottomSkyBox(const char* TextureLocationName_)
{
	static Vertex skyVertices[4] =
	{
		{glm::vec4(100.0, -14.8, 100.0, 1.0), glm::vec2(8.0, 0.0)},
		{glm::vec4(100.0, -14.8, -100.0, 1.0), glm::vec2(8.0, 8.0)},
		{glm::vec4(-100.0, -14.8, 100.0, 1.0), glm::vec2(0.0, 0.0)},
		{glm::vec4(-100.0, -14.8, -100.0, 1.0), glm::vec2(0.0, 8.0)}
	};

	///// Create a Sky /////////////
	//this will add the field texture, to the grassTex uniform
	textureId = GraphicsEngine::AddTexture(TextureLocationName_, "skyTex");
	//Create VAO and VBO
	 //get the object and the buffer (vaoId and vboId)
	GraphicsEngine::currentLimitOfVao = GraphicsEngine::currentLimitOfVao + 1;
	GraphicsEngine::currentLimitOfVbo = GraphicsEngine::currentLimitOfVbo + 1;
	s_objectBottom = GraphicsEngine::currentLimitOfVao;
	s_bufferBottom = GraphicsEngine::currentLimitOfVbo;
	GraphicsEngine::vao.push_back(0);
	GraphicsEngine::buffer.push_back(0);

	//CREATE A MODEL, IN THIS CAS E A TABLE FROM A OBJ FILE
	glGenVertexArrays(1, &GraphicsEngine::vao[s_objectBottom]);
	glGenBuffers(1, &GraphicsEngine::buffer[s_bufferBottom]);
	//SetIDs(GraphicsEngine::vao[s_object2], GraphicsEngine::buffer[s_buffer2], 0);

	glBindVertexArray(GraphicsEngine::vao[s_objectBottom]);
	glBindBuffer(GL_ARRAY_BUFFER, GraphicsEngine::vao[s_objectBottom]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(skyVertices), skyVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(skyVertices[0]), 0);  //layout(location=2) in glm::vec4 skyCoords;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(skyVertices[0]), (void*)(sizeof(skyVertices[0].coords))); //layout(location=3) in glm::vec2 skyTexCoords;
	glEnableVertexAttribArray(1);
}


void SkyBox::Init(const char* TextureLocationName_, const char* textureBottom)
{
	static Vertex skyVertices[30] =
	{
		//BACK
		{glm::vec4(100.0, -20.0, -20.0, 1.0), glm::vec2(1.0, 0.0)},
		{glm::vec4(100.0, 90.0, -20.0, 1.0), glm::vec2(1.0, 1.0)},
		{glm::vec4(-100.0, -20.0, -20.0, 1.0), glm::vec2(0.0, 0.0)},

	    {glm::vec4(100.0, 90.0, -20.0, 1.0), glm::vec2(1.0, 1.0)},
		{glm::vec4(-100.0, -20.0, -20.0, 1.0), glm::vec2(0.0, 0.0)},
		{glm::vec4(-100.0, 90.0, -20.0, 1.0), glm::vec2(0.0, 1.0)},

		//FRONT
		{glm::vec4(100.0, -20.0, 60.0, 1.0), glm::vec2(1.0, 0.0)},
		{glm::vec4(100.0, 90.0, 60.0, 1.0), glm::vec2(1.0, 1.0)},
		{glm::vec4(-100.0, -20.0, 60.0, 1.0), glm::vec2(0.0, 0.0)},

		{glm::vec4(100.0, 90.0, 60.0, 1.0), glm::vec2(1.0, 1.0)},
		{glm::vec4(-100.0, -20.0, 60.0, 1.0), glm::vec2(0.0, 0.0)},
		{glm::vec4(-100.0, 90.0, 60.0, 1.0), glm::vec2(0.0, 1.0)},

		//TOP
		{glm::vec4(100.0, 25.0, 100.0, 1.0), glm::vec2(8.0, 0.0)},
		{glm::vec4(100.0, 25.0, -100.0, 1.0), glm::vec2(8.0, 8.0)},
		{glm::vec4(-100.0, 25.0, 100.0, 1.0), glm::vec2(0.0, 0.0)},

		{glm::vec4(100.0, 25.0, -100.0, 1.0), glm::vec2(8.0, 8.0)},
		{glm::vec4(-100.0, 25.0, 100.0, 1.0), glm::vec2(0.0, 0.0)},
		{glm::vec4(-100.0, 25.0, -100.0, 1.0), glm::vec2(0.0, 8.0)},

		//LEFT
		{glm::vec4(30.0, 30.0, 100.0, 1.0), glm::vec2(0.0, 1.0)},
		{glm::vec4(30.0, -30.0, -100.0, 1.0), glm::vec2(1.0, 1.0)},
		{glm::vec4(30.0, -30.0, 100.0, 1.0), glm::vec2(0.0, 0.0)},

		{glm::vec4(30.0, -30.0, -100.0, 1.0), glm::vec2(0.0, 1.0)},
		{glm::vec4(30.0, 30.0, 100.0, 1.0), glm::vec2(1.0, 1.0)},
		{glm::vec4(30.0, 30.0, -100.0, 1.0), glm::vec2(0.0, 0.0)},

		//Right
		{glm::vec4(-20.0, 30.0, 100.0, 1.0), glm::vec2(0.0, 1.0)},
		{glm::vec4(-20.0, -30.0, -100.0, 1.0), glm::vec2(1.0, 1.0)},
		{glm::vec4(-20.0, -30.0, 100.0, 1.0), glm::vec2(0.0, 0.0)},

		{glm::vec4(-20.0, -30.0, -100.0, 1.0), glm::vec2(0.0, 1.0)},
		{glm::vec4(-20.0, 30.0, 100.0, 1.0), glm::vec2(1.0, 1.0)},
		{glm::vec4(-20.0, 30.0, -100.0, 1.0), glm::vec2(0.0, 0.0)}
	};

	///// Create a Sky /////////////
	//this will add the field texture, to the grassTex uniform
	textureId = GraphicsEngine::AddTexture(TextureLocationName_, "skyTex");
   //Create VAO and VBO
	//get the object and the buffer (vaoId and vboId)
	GraphicsEngine::currentLimitOfVao = GraphicsEngine::currentLimitOfVao + 1;
	GraphicsEngine::currentLimitOfVbo = GraphicsEngine::currentLimitOfVbo + 1;
	s_object = GraphicsEngine::currentLimitOfVao;
	s_buffer = GraphicsEngine::currentLimitOfVbo;
	GraphicsEngine::vao.push_back(0);
	GraphicsEngine::buffer.push_back(0);

	//CREATE A MODEL, IN THIS CAS E A TABLE FROM A OBJ FILE
	glGenVertexArrays(1, &GraphicsEngine::vao[s_object]);
	glGenBuffers(1, &GraphicsEngine::buffer[s_buffer]);
	//SetIDs(GraphicsEngine::vao[s_object], GraphicsEngine::buffer[s_buffer], 0);

	glBindVertexArray(GraphicsEngine::vao[s_object]);
	glBindBuffer(GL_ARRAY_BUFFER, GraphicsEngine::buffer[s_buffer]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(skyVertices), skyVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(skyVertices[0]), 0);  //layout(location=2) in glm::vec4 skyCoords;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(skyVertices[0]), (void*)(sizeof(skyVertices[0].coords))); //layout(location=3) in glm::vec2 skyTexCoords;
	glEnableVertexAttribArray(1);
	InitBottomSkyBox(textureBottom);
	
}

void SkyBox::Draw()
{
	

	//this will set its own material to be active since we are going to draw the object below
	GraphicsEngine::SetActiveTexture(textureId);
	// Draw sky.
	glUniform1ui(GraphicsEngine::objectLoc, s_object);  //if (object == SKY)
	glBindVertexArray(GraphicsEngine::vao[s_object]);
	glDrawArrays(GL_TRIANGLES, 0, 30);

	//this will set its own material to be active since we are going to draw the object below
	GraphicsEngine::SetActiveTexture(textureId);
	// Draw sky.
	glUniform1ui(GraphicsEngine::objectLoc, s_objectBottom);  //if (object == SKY)
	glBindVertexArray(GraphicsEngine::vao[s_objectBottom]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);




}
