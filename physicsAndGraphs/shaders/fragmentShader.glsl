#version 430 core

#define FIELD 0
#define SKY 1
#define SPHERE 2
#define MYMODEL 3
#define TRACK 4

in vec2 texCoordsExport;
in vec3 normalExport;
in vec3 modelExport;
in vec3 eyeExport;

struct Light
{
   vec4 ambCols;
   vec4 difCols;
   vec4 specCols;
   vec4 coords;
};

struct Material
{
   vec4 ambRefl;
   vec4 difRefl;
   vec4 specRefl;
   vec4 emitCols;
   float shininess;
};

uniform Light light0;
uniform Light light1;
uniform vec4 globAmb;
uniform Material sphereFandB;

//texture uniforms
uniform sampler2D grassTex;
uniform sampler2D skyTex;
uniform sampler2D modelMaterial;

uniform uint object;

out vec4 colorsOut;

vec4 fieldTexColor, skyTexColor, modelTexColor;
//this will create the normal, light direction for the light 1 and 2
vec3 normal, lightDirection, lightDirection2;
//fAndBDif for both lights
vec4 fAndBDif, fAndBDif2;
vec3 eyeDirection;
//the halfway for both lights
vec3 halfway, halfway2;
//fandbspec for both lights
vec4 fAndBSpec,fAndBSpec2;


void main(void)
{  
   //add the texture calculation codes
   fieldTexColor = texture(grassTex, texCoordsExport);
   skyTexColor = texture(skyTex, texCoordsExport);
   modelTexColor = texture(modelMaterial, texCoordsExport);

   if (object == FIELD) colorsOut = fieldTexColor;
   if (object == SKY) colorsOut = skyTexColor;
   //if (object != FIELD && object!=SKY) {
    //DIFUSE
    //normal = normalize(normalExport);
	//lightDirection = normalize(vec3(light0.coords));
	//fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    
	//SPECULAR
	//eyeDirection = normalize(eyeExport - modelExport);
    //halfway = (length(lightDirection + eyeDirection) == 0.0f) ? vec3(0.0) : (lightDirection + eyeDirection) / length(lightDirection + eyeDirection);    
    //fAndBSpec = pow(max(dot(normal, halfway), 0.0), sphereFandB.shininess) * light0.specCols * sphereFandB.specRefl;

	//colorsOut =  vec4(vec3(min(fAndBDif+fAndBSpec, vec4(1.0))), 1.0);
   //}

   //for the rest of the objects do the lighting calculations
   if(object!=SKY && object != FIELD) {
	
	//DIFUSE LIGHT
	normal = normalize(normalExport);
	lightDirection = normalize(vec3(light0.coords));
	lightDirection2 = normalize(vec3(light1.coords));
	fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
	fAndBDif2 = max(dot(normal, lightDirection2), 0.0f) * (light1.difCols * sphereFandB.difRefl); 

	//SPECULAR
	eyeDirection = normalize(eyeExport - modelExport);
    halfway = (length(lightDirection + eyeDirection) == 0.0f) ? vec3(0.0) : (lightDirection + eyeDirection) / length(lightDirection + eyeDirection);    
	halfway2 = (length(lightDirection2 + eyeDirection) == 0.0f) ? vec3(0.0) : (lightDirection2 + eyeDirection) / length(lightDirection2 + eyeDirection);    
    fAndBSpec = pow(max(dot(normal, halfway), 0.0), sphereFandB.shininess) * light0.specCols * sphereFandB.specRefl;
	fAndBSpec2 = pow(max(dot(normal, halfway2), 0.0), sphereFandB.shininess) * light1.specCols * sphereFandB.specRefl;
	//add the texture width the specular light and diffuse light
	colorsOut = vec4(vec3(min(fAndBDif+fAndBDif2+fAndBSpec+fAndBSpec2, vec4(1.0))), 1.0) * modelTexColor;
   }
   
   //if(object==TRACK) {
    //DIFUSE LIGHT
	//normal = normalize(normalExport);
	//lightDirection = normalize(vec3(light0.coords));
//	fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 

	//SPECULAR
//	eyeDirection = normalize(eyeExport - modelExport);
    //halfway = (length(lightDirection + eyeDirection) == 0.0f) ? vec3(0.0) : (lightDirection + eyeDirection) / length(lightDirection + eyeDirection);    
  //  fAndBSpec = pow(max(dot(normal, halfway), 0.0), sphereFandB.shininess) * light0.specCols * sphereFandB.specRefl;

    //colorsOut =  vec4(vec3(min(fAndBDif + fAndBSpec, vec4(1.0))), 1.0);
   //}

}