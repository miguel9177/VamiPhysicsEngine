#include "Player.h"


//constructor that takes a mass, position, speed, etc, then passes to the rigidbody constructor the mass the position, inertia and orientation
//PS: THE BODY TYPE NEEDS TO BE ONE OF THE VALUES FROM THE ENUM WHICH 
Player::Player(float mass_, glm::vec3 position_, glm::vec3 color_,float speed_, float rotationalSpeed_, int bodyType, float width_, float height_, glm::vec3 orientation_, float coeficientOfRestitution_, float radius)
{

	//save the speed, width and height to the variable speed
	speed = speed_;
	rotationalSpeed =rotationalSpeed_;
	height = height_;
	width = width_;
	//color = color_;


	float inertia = GetInertiaFromBodyType(bodyType, mass_, width, height, radius);
	//this willl create the physics body, and it will use the get inertia from the function
	//physicsBody = new RigidBody2D(1.0f, position_, inertia,orientation_, coeficientOfRestitution_);
}



Player::~Player()
{
}

//this is going to check for input (if the player clicks the arrow keys or not), this is called on the update function
void Player::CheckForInput()
{
	//THIS WILL MAKE THE PLAYER MOVE
	//if the arrow up is clicked, move the particle up
	/*if (GameObject::specialKeys[GLUT_KEY_UP] == true)
		physicsBody->AddForce(glm::rotateZ(glm::vec3(0, speed, 0), physicsBody->ReturnOrientation().z), glm::vec3 (0,0, 0));
	//if the arrow down is clicked, move the particle bottom
	if (GameObject::specialKeys[GLUT_KEY_DOWN] == true)
		physicsBody->AddForce(glm::rotateZ(glm::vec3(0, -speed, 0), physicsBody->ReturnOrientation().z), glm::vec3(0, 0, 0));
	//if the arrow left is clicked, move the particle left
	if (GameObject::specialKeys[GLUT_KEY_LEFT] == true)
		physicsBody->AddForce(glm::rotateZ(glm::vec3(-speed, 0, 0), physicsBody->ReturnOrientation().z), glm::vec3(0, 0, 0));
	//if the arrow right is clicked, move the particle right
	if (GameObject::specialKeys[GLUT_KEY_RIGHT] == true)
		physicsBody->AddForce(glm::rotateZ(glm::vec3(speed, 0, 0), physicsBody->ReturnOrientation().z), glm::vec3(0, 0, 0));

	//THIS WILL MAKE THE PLAYER ROTATE
	//if the q key is clicked, rotate the particle left (anti clockwise  
	if (GameObject::keys['q'] || GameObject::keys['Q'] == true)
		physicsBody->AddRotationalMotionWithoutAddingForce(glm::vec3(rotationalSpeed, 0, 0), glm::vec3(1, 1, 0));
	if (GameObject::keys['e'] || GameObject::keys['E'] == true)
		physicsBody->AddRotationalMotionWithoutAddingForce(glm::vec3(-rotationalSpeed, 0, 0), glm::vec3(1, 1, 0));
	*/
	

}


void Player::Update(float deltaTime)
{
	
	
	//Create gravity force by moving the particle (this player) down times the mass, since the heavier the object the harder it falls
	//particle->AddForce(glm::vec3(0.0f, -100.0f, 0.0f));

	//call the function to check for input and then move
	CheckForInput();
	
	//call the particle update method, wich will calculate the new aceleration, velocity and position
	physicsBody->Update(deltaTime);

	//reset the force of the particle (this player) to 0, since we are going to add movement if we clicked an arrow key
	physicsBody->ResetTotalForces();
}

//draw function that draws the object, using the current particle position
void Player::Draw()
{
	//dont affect other objects, only this one so take a copy of the matrix and put it on the stack
	glPushMatrix();

	//move the player by changing the position to the physicsbody(rigidbody in this case) position, the physicsbody position has been affected by acceleration etc
	glTranslatef(physicsBody->ReturnPosition().x, physicsBody->ReturnPosition().y, physicsBody->ReturnPosition().z);
	
	
	float degrees = physicsBody->ReturnOrientation().z * (180.0 / 3.141592653589793238463);//convert radians to degrees
	glRotatef(degrees, 0, 0, 1);

	//std::cout << " X: " << physicsBody->ReturnOrientation().x << " Y: " << physicsBody->ReturnOrientation().y << " Z: " << physicsBody->ReturnOrientation().z << std::endl;
	//std::cout << " Angle (z) : " << degrees << std::endl;

	//glColor3f(color.x,color.y,color.z);

	//draw the object
	glBegin(GL_QUADS);
		glVertex3f(-height, width, 0); //top left
		glVertex3f(height, width, 0); //top right
		glVertex3f(height, -width, 0); //bottom right
		glVertex3f(-height, -width, 0); //bottom left
	glEnd();
	
	
	//THIS IS THE CODE TO WRITE DEBUG INFORMATION IF DEBUG MODE IS ON
	if (GameEngine::IsDebugModeOn)
	{
		glPointSize(5.0f); // so we can see the point better

		//this is going to draw a point on the midle of the object
		glColor3f(0.f, 0.f, 0.f);
		glBegin(GL_POINTS);
		//at the middle of object
		glVertex3f(0, 0, 0);
		glEnd();

		
		//this will draw a line with the object velocity
		glColor3f(1.f, 1.f, 1.f);
		glm::vec3 vel = physicsBody->ReturnVelocity();
		glBegin(GL_LINES);
		glVertex3f(0, 0, 0); //0, 0, 0 is used here as I assume you have a glTranslatef line above, so 0, 0, 0 puts us at the center of the object now
		glVertex3f(vel.x, vel.y, vel.z);
		glEnd();
		
		std::string informationText = "Pos: X-> " + std::to_string(physicsBody->ReturnPosition().x).erase(5, 9) + " Y-> " + std::to_string(physicsBody->ReturnPosition().y).erase(5, 9) + " Z-> " + std::to_string(physicsBody->ReturnPosition().z).erase(5, 9);
		glRasterPos2f(informationText.length() * -0.06, height + 0.6f);
		for (int i = 0; i < informationText.length(); i++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, informationText[i]);
		}

		informationText = "Rot: X-> " + std::to_string(physicsBody->ReturnOrientation().x).erase(5, 9) + " Y-> " + std::to_string(physicsBody->ReturnOrientation().y).erase(5, 9) + " Z-> " + std::to_string(physicsBody->ReturnOrientation().z).erase(5, 9);
		glRasterPos2f(informationText.length() * -0.06, height + 0.35f);
		for (int i = 0; i < informationText.length(); i++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, informationText[i]);
		}

		informationText = "Vel: X-> " + std::to_string(physicsBody->ReturnVelocity().x).erase(5, 9) + " Y-> " + std::to_string(physicsBody->ReturnVelocity().y).erase(5, 9) + " Z-> " + std::to_string(physicsBody->ReturnVelocity().z).erase(5, 9);
		glRasterPos2f(informationText.length() * -0.06, height + 0.1f);
		for (int i = 0; i < informationText.length(); i++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, informationText[i]);
		}
	}


	glPopMatrix();
	
}

//this function will let me change texture
void Player::ChangeTexture(unsigned int textureId_)
{
	std::cout << "CHANGE TEXTURE OF PLAYER IS NOT FILLED SINCE I DONT EVEN HAVE TEXTURES ON THE PLAYER" << std::endl;
}




