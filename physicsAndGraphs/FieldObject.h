#pragma once
#include "GameObject.h"
#include "GraphicsEngine.h"
class FieldObject: GameObject
{
private:
	static unsigned int f_object;
	static unsigned int f_buffer;
	static unsigned int VAO;
	static unsigned int VBO;
	static unsigned int IBO;

	static void SetIDs(unsigned int vao, unsigned int vbo, unsigned int ibo);
public:
	
	static void Init(const char*);
	static void Draw();
	//this function will let me change texture
	static void ChangeTexture(unsigned int textureId_);

};

