#include "GraphicsEngine.h"
unsigned int GraphicsEngine::programId;
unsigned int GraphicsEngine::vertexShaderId;
unsigned int GraphicsEngine::fragmentShaderId;
unsigned int GraphicsEngine::modelMatLoc;
unsigned int GraphicsEngine::viewMatLoc;
unsigned int GraphicsEngine::projMatLoc;
unsigned int GraphicsEngine::objectLoc;
unsigned int GraphicsEngine::grassTexLoc;
unsigned int GraphicsEngine::skyTexLoc;
unsigned int GraphicsEngine::modelMaterialUniform;
unsigned int GraphicsEngine::currentLimitOfVao;
unsigned int GraphicsEngine::currentLimitOfVbo;
std::vector<unsigned int>GraphicsEngine::buffer;
std::vector<unsigned int> GraphicsEngine::vao;
std::vector<GLuint> GraphicsEngine::textures;
glm::vec4 GraphicsEngine::globAmb;
glm::mat4 GraphicsEngine::modelMat;
glm::mat4 GraphicsEngine::viewMat;
glm::mat4 GraphicsEngine::projMat;
glm::mat3 GraphicsEngine::normalMat;
graphics::Material GraphicsEngine::sphereFandB;
graphics::Light GraphicsEngine::light0;
graphics::Light GraphicsEngine::light1;
std::vector<std::string> GraphicsEngine::TexNames;
// Camera
glm::vec3 GraphicsEngine::cameraPosition;
glm::vec3 GraphicsEngine::cameraForward;
//camera y rot
float GraphicsEngine::cameraYaw;
//camera x rot
float GraphicsEngine::cameraPitch;


void GraphicsEngine::init(int argc, char** argv, const char* windowTitle, int width, int height)
{
	//Initialize variables Begin
	modelMat = glm::mat4(1.0);
	viewMat = glm::mat4(1.0);
	projMat = glm::mat4(1.0);
	normalMat = glm::mat3(1.0);  ///create normal matrix

	globAmb = glm::vec4(0.2, 0.2, 0.2, 1.0);

	sphereFandB = {
		glm::vec4(1.0, 1.0, 1.0, 1.0), //ambient reflection
		glm::vec4(1.0, 1.0, 1.0, 1.0), //diffuse reflection
		glm::vec4(1.0, 1.0, 1.0, 1.0), //specular reflection
		glm::vec4(0.0, 0.0, 0.0, 1.0), //emit colors
		50.0f //shininess
	};

	//this will initialize the data fopr the light 0
	light0 = { glm::vec4(0.0, 0.0, 0.0, 1.0), //ambient 
		glm::vec4(1.0, 1.0, 1.0, 1.0),//difuse color
		glm::vec4(1.0, 1.0, 1.0, 1.0),//specular
		glm::vec4(1.0, 1.0, 0.0, 0.0)//light direction
	};

	//this will initialize the data fopr the light 1
	light1 = { glm::vec4(0.0, 0.0, 0.0, 1.0),//ambient
		glm::vec4(1.0, 1.0, 1.0, 1.0),//difuse color
		glm::vec4(1.0, 1.0, 1.0, 1.0),//specular
		glm::vec4(0.0, 1.0, 0.0, 0.0)//light direction
	};

	//this is going to store in which vao we are, because everyobject needs its vao and vbo,
	//it starts at -1 because every creation of an object does a +1, and if it started by 0, the first one would acceess the 1 value first instead of 0
	currentLimitOfVao = -1;
	currentLimitOfVbo = -1;

	cameraPosition = glm::vec3(0, 0, 0);
	cameraForward = glm::vec3(0.0, 0.0, 15.0);
	cameraYaw = 0;
	cameraPitch = 0;
	
	//Initialize variables End
	
	//INITIALIZE OPENGL GLUT ETC TO CREATE THE WINDOW
	glutInit(&argc, argv);

	glutInitContextVersion(2, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(windowTitle);


	glewExperimental = GL_TRUE;
	glewInit();
	
	glClearColor(0.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	
}

GraphicsEngine::~GraphicsEngine()
{
	
}

//this will initialize the shaders
void GraphicsEngine::SetupShaders()
{
	// Create shader program executable.
	GraphicsEngine::vertexShaderId = setShader("vertex", "shaders/vertexShader.glsl");
	GraphicsEngine::fragmentShaderId = setShader("fragment", "shaders/fragmentShader.glsl");
	GraphicsEngine::programId = glCreateProgram();
	glAttachShader(GraphicsEngine::programId, GraphicsEngine::vertexShaderId);
	glAttachShader(GraphicsEngine::programId, GraphicsEngine::fragmentShaderId);
	glLinkProgram(GraphicsEngine::programId);

	glUseProgram(GraphicsEngine::programId);

	//codes for OpenGL lighting
	glUniform4fv(glGetUniformLocation(GraphicsEngine::programId, "sphereFandB.ambRefl"), 1, &GraphicsEngine::sphereFandB.ambRefl[0]);
	glUniform4fv(glGetUniformLocation(GraphicsEngine::programId, "sphereFandB.difRefl"), 1, &GraphicsEngine::sphereFandB.difRefl[0]);
	glUniform4fv(glGetUniformLocation(GraphicsEngine::programId, "sphereFandB.specRefl"), 1, &GraphicsEngine::sphereFandB.specRefl[0]);
	glUniform4fv(glGetUniformLocation(GraphicsEngine::programId, "sphereFandB.emitCols"), 1, &GraphicsEngine::sphereFandB.emitCols[0]);
	glUniform1f(glGetUniformLocation(GraphicsEngine::programId, "sphereFandB.shininess"), GraphicsEngine::sphereFandB.shininess);

	glUniform4fv(glGetUniformLocation(GraphicsEngine::programId, "globAmb"), 1, &GraphicsEngine::globAmb[0]);

	//fill in the light0 struct on the fragment shader
	glUniform4fv(glGetUniformLocation(GraphicsEngine::programId, "light0.ambCols"), 1, &GraphicsEngine::light0.ambCols[0]);
	glUniform4fv(glGetUniformLocation(GraphicsEngine::programId, "light0.difCols"), 1, &GraphicsEngine::light0.difCols[0]);
	glUniform4fv(glGetUniformLocation(GraphicsEngine::programId, "light0.specCols"), 1, &GraphicsEngine::light0.specCols[0]);
	glUniform4fv(glGetUniformLocation(GraphicsEngine::programId, "light0.coords"), 1, &GraphicsEngine::light0.coords[0]);

	//fill in the light1 struct on the fragment shader
	glUniform4fv(glGetUniformLocation(GraphicsEngine::programId, "light1.ambCols"), 1, &GraphicsEngine::light1.ambCols[0]);
	glUniform4fv(glGetUniformLocation(GraphicsEngine::programId, "light1.difCols"), 1, &GraphicsEngine::light1.difCols[0]);
	glUniform4fv(glGetUniformLocation(GraphicsEngine::programId, "light1.specCols"), 1, &GraphicsEngine::light1.specCols[0]);
	glUniform4fv(glGetUniformLocation(GraphicsEngine::programId, "light1.coords"), 1, &GraphicsEngine::light1.coords[0]);
	

}

void GraphicsEngine::ObtainProjectionAndModelMatrix()
{
	// Obtain projection matrix uniform location and set value.
	GraphicsEngine::projMatLoc = glGetUniformLocation(GraphicsEngine::programId, "projMat");   //uniform glm::mat4 projMat;
	GraphicsEngine::projMat = glm::perspective(glm::radians(60.0), 1.0, 0.1, 1000.0);

	glUniformMatrix4fv(GraphicsEngine::projMatLoc, 1, GL_FALSE, value_ptr(GraphicsEngine::projMat));

	// Obtain modelview matrix uniform and object uniform locations.
	GraphicsEngine::modelMatLoc = glGetUniformLocation(GraphicsEngine::programId, "modelMat");   //uniform glm::mat4 modelViewMat;
	// Obtain modelview matrix uniform and object uniform locations.
	GraphicsEngine::viewMatLoc= glGetUniformLocation(GraphicsEngine::programId, "viewMat");   //uniform glm::mat4 modelViewMat;
	GraphicsEngine::objectLoc = glGetUniformLocation(GraphicsEngine::programId, "object");  //uniform uint object;
}

//this is going to add a texture to the the texture lists
unsigned int GraphicsEngine::AddTexture(const char* textureLocation, const char* uniformOfTextureNOTMANDATORY_)
{
	TexNames.push_back(textureLocation);
	textures.push_back(0);
	// Create GraphicsEngine::texture ids.
	glGenTextures(textures.size(), textures.data());
	int width, height;
	unsigned char* data;
	//WOOD TEXTURE SETUP (PROBABLY FOR THE TABLE) BEGIN
	glActiveTexture(GL_TEXTURE0 + textures.size() - 1);
	glBindTexture(GL_TEXTURE_2D, GraphicsEngine::textures[textures.size()-1]);

	//GET IMAGE DATA , AND ASSIGN VALUES TO WIDTH AND HEIGHT
	data = SOIL_load_image(TexNames[textures.size()-1].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	SOIL_free_image_data(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	//if the uniform field was filled, its because its not a normal model (SKYBOX, etc)
	if(uniformOfTextureNOTMANDATORY_!="")
		GraphicsEngine::modelMaterialUniform = glGetUniformLocation(GraphicsEngine::programId, uniformOfTextureNOTMANDATORY_);	//Get the model uniform from matrix shader and then
	else
		GraphicsEngine::modelMaterialUniform = glGetUniformLocation(GraphicsEngine::programId, "modelMaterial");	//Get the model uniform from matrix shader and then

	glUniform1i(GraphicsEngine::modelMaterialUniform, textures.size() - 1); //send GraphicsEngine::texture to shader


	return textures.size() - 1;
}

//this is going set the sended texture id to be active
void GraphicsEngine::SetActiveTexture(unsigned int textureId_)
{

	//Get the model uniform from matrix shader and then
	modelMaterialUniform = glGetUniformLocation(programId, "modelMaterial");
	glUniform1i(modelMaterialUniform, textureId_);
}

//this is called by the game engine draw game function, and it will move the camera 
void GraphicsEngine::MoveCamera()
{
	/*if (cameraPitch < -89)
	{
		cameraPitch = -89;
	}
	if (cameraPitch > 89)
	{
		cameraPitch = 89;
	}*/

	

	glm::vec3 eye = glm::vec3(0, 0, 0);
	eye.x = glm::cos(glm::radians(cameraPitch)) * -glm::cos(glm::radians(cameraYaw));
	eye.y = glm::sin(glm::radians(cameraPitch));
	eye.z = glm::cos(glm::radians(cameraPitch)) * glm::sin(glm::radians(cameraYaw));

	cameraForward = glm::normalize(eye);
}

//this will update the model matrix to move the camer
void GraphicsEngine::UpdateCamera()
{
	viewMat = glm::lookAt(cameraForward, glm::vec3(0), glm::vec3(0, 1, 0));
	viewMat = glm::translate(viewMat, cameraPosition);
	
	glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, value_ptr(viewMat));

	//Send Camera position to shader for Specular Lighting
	glUniform3fv(glGetUniformLocation(programId, "eyePos"), 1, &cameraForward[0]);
}