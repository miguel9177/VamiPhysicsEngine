#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "soil/SOIL.h"
#include <string>

#include<vector>
#include "shader.h"
#include "vertex.h"

#include <GL/glew.h>
#include <GL/freeglut.h>




namespace graphics {
	struct Material
	{
		glm::vec4 ambRefl;
		glm::vec4 difRefl;
		glm::vec4 specRefl;
		glm::vec4 emitCols;
		float shininess;
	};

	struct Light
	{
		glm::vec4 ambCols;
		glm::vec4 difCols;
		glm::vec4 specCols;
		glm::vec4 coords;
	};
}
class GraphicsEngine
{
private:

	// list of textures
	static std::vector<unsigned int> textures;
	// Load the images.
	static std::vector<std::string> TexNames;
public:
	static enum object { FIELD, SKY, SPHERE, MYMODEL, TRACK }; // VAO ids.
	static enum buffer_ { FIELD_VERTICES, SKY_VERTICES, SPHERE_VERTICES, SPHERE_INDICES, MYMODEL_VERTICES, TRACK_VERTICES }; // VBO ids.
	static unsigned int currentLimitOfVao;
	static unsigned int currentLimitOfVbo;
	static glm::vec4 globAmb; //CONST
	// Front and back material properties.
	static graphics::Material sphereFandB; //const


	static graphics::Light light0; //this will do the first light
	static graphics::Light light1; //this will do the second light



	//this is going to represent the object transformations
	static glm::mat4 modelMat; //= glm::mat4(1.0);
	//this is going to represent the camera transformations
	static glm::mat4 viewMat; //= glm::mat4(1.0);
	static glm::mat4 projMat; //= glm::mat4(1.0);
	static glm::mat3 normalMat; //= mat3(1.0);  ///create normal matrix

	static unsigned int
		programId,
		vertexShaderId,
		fragmentShaderId,
		//this is going to represent the object transformations
		modelMatLoc,
		//this is going to represent the camera transformations
		viewMatLoc,
		projMatLoc,
		objectLoc,
		grassTexLoc,  //for grass texture 
		skyTexLoc,
		modelMaterialUniform;

	static std::vector<unsigned int> vao;
	static std::vector<unsigned int> buffer;

	// Camera
	static glm::vec3 cameraPosition;
	static glm::vec3 cameraForward;
	//camera y rot
	static float cameraYaw;
	//camera x rot
	static float cameraPitch;

	//static Sphere testSphere;


	static void init(int argc, char** argv, const char* windowTitle, int width, int height);
	~GraphicsEngine();


	static void SetupShaders();
	static void ObtainProjectionAndModelMatrix();
	static unsigned int AddTexture(const char*, const char* = "");//this is going to add a texture to the texture list, and it will return an unsigned int
	static void SetActiveTexture(unsigned int);//this is going activate the textureid passed
	static void MoveCamera();
	static void UpdateCamera();
};

