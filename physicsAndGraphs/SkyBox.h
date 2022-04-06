#pragma once
#include "GameObject.h"
#include "GraphicsEngine.h"
class SkyBox : GameObject
{
private:
	static unsigned int s_object;
	static unsigned int s_buffer;
	static unsigned int s_objectBottom;
	static unsigned int s_bufferBottom;
	
	//static unsigned int VAO;
	//static unsigned int VBO;
	static unsigned int IBO;
	static unsigned int textureId;

	static void InitBottomSkyBox(const char* TextureLocationName_);
	
public:
	
	static void Init(const char*, const char* textureBottom);
	static void Draw();
	static void SetIDs(unsigned int, unsigned int, unsigned int);
	static void ChangeTexture(unsigned int textureId_);

};

