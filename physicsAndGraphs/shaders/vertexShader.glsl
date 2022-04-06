#version 430 core

#define FIELD 0
#define SKY 1
#define SPHERE 2
#define MYMODEL 3
#define TRACK 4

layout(location=0) in vec4 Coords;
layout(location=1) in vec2 TexCoords;
layout(location=2) in vec4 sphereCoords;
layout(location=3) in vec3 sphereNormals;

//object (mymodel) information
layout(location = 4) in vec3 objCoords;
layout(location = 5) in vec3 objNormals;
layout(location=6) in vec2 objTextCoords;

//this is set by the modelMatLoc graphics engine variable
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;
uniform uint object;
uniform vec3 eyePos;

out vec2 texCoordsExport;
out vec3 normalExport;
out vec3 eyeExport;
out vec3 modelExport;



vec4 coords;



void main(void)
{   
   if (object == FIELD)
   {
      coords = Coords;
      texCoordsExport = TexCoords;
   }
   if (object == SKY)
   {
     coords = Coords;
     texCoordsExport = TexCoords;
   }

   //if the current objec is a model
   if(object!=SKY && object != FIELD)
   {
        //i convert the objCoords to vec4 since coords are vec4
        coords = vec4(objCoords, 1.0f);
        
        normalExport = objNormals;
        texCoordsExport = objTextCoords;
        //i multiply the projection by view matrix and model matrix since i want to move the model, and i need to multiply by the "camera matrix"
        //it needs to be in this order so that it works
        gl_Position = projMat * viewMat * modelMat * coords;
        eyeExport = eyePos;
        modelExport = vec3(modelMat * coords);
   }
   else{
        //this is for the camera, it will use the view matrix multiplied by the projection matrix and coordinates, i dont 
        //use the model matrix since i dont want to move any object
       gl_Position = projMat * viewMat * coords;
       eyeExport = eyePos;
       modelExport = vec3(viewMat * coords);
   }
}
