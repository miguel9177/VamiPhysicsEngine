#include "cameraController.h"

//this will be true if the mouse is being dragged
bool cameraController::isDragging;
//this will store the pos of when we started dragging
glm::vec2 cameraController::initialMousePos;
float cameraController::initialCameraPitch;
float cameraController::initialCameraYaw;
bool cameraController::firstTimeOnLoop;
glm::vec3 cameraController::initialWhiteBallCameraPos;
glm::vec3 cameraController::currentWhiteBallCameraPos;
unsigned int cameraController::currerntCameraPos;

//this will store the white ball, its assigned on the game scene constructor
GameObject* cameraController::whiteBall;

void cameraController::Start()
{
	
	//GraphicsEngine::cameraPitch = 90;
	

	//tell the code that this is the first loop
	firstTimeOnLoop = true;

	//rotatte the yaw of the camera to the correct rotation for it to be looking at the table
	GraphicsEngine::cameraYaw = -90;
	//GraphicsEngine::cameraPitch = 90;
	GraphicsEngine::MoveCamera();

	initialMousePos = glm::vec2(0.5,0.5);
	initialCameraPitch = GraphicsEngine::cameraPitch;
	initialCameraYaw = GraphicsEngine::cameraYaw;
	
	
}

void cameraController::Update()
{
	//OLD CAMERA KEY CONTROLS

	//if j is clicked move forward
	if (ButtonsPressed::keys['j'] || ButtonsPressed::keys['J'] == true)
	{
		GraphicsEngine::cameraPosition += GraphicsEngine::cameraForward * 0.2f;
		
	}
	//if n is clicked move backwards
	if (ButtonsPressed::keys['n'] || ButtonsPressed::keys['N'] == true)
	{
		GraphicsEngine::cameraPosition += -GraphicsEngine::cameraForward * 0.2f;
		
	}
	//if b is clicked move left
	if (ButtonsPressed::keys['b'] || ButtonsPressed::keys['B'] == true)
	{
		GraphicsEngine::cameraPosition += -glm::normalize(glm::cross(GraphicsEngine::cameraForward, glm::vec3(0, 0.1, 0))) * 0.2f;
		
	}
	//if m is clicked move right
	if (ButtonsPressed::keys['m'] || ButtonsPressed::keys['M'] == true)
	{
		GraphicsEngine::cameraPosition += glm::normalize(glm::cross(GraphicsEngine::cameraForward, glm::vec3(0, 0.1, 0))) * 0.2f;
		
	}
	//if h is clicked move bottom
	if (ButtonsPressed::keys['h'] || ButtonsPressed::keys['H'] == true)
	{
		GraphicsEngine::cameraPosition += glm::vec3(0, 0.1, 0) * 0.2f;
		
	}
	//if k is clicked move up
	if (ButtonsPressed::keys['k'] || ButtonsPressed::keys['K'] == true)
	{
		GraphicsEngine::cameraPosition += -glm::vec3(0, 0.1, 0) * 0.2f;
		
	}
	//if i is pressed, show the camera position
	if (ButtonsPressed::keys['i'] || ButtonsPressed::keys['I'] == true)
	{
		system("cls");
		std::cout << "Camera pos: X: " << GraphicsEngine::cameraPosition.x << " Y: " << GraphicsEngine::cameraPosition.y << " Z: " << GraphicsEngine::cameraPosition.z << std::endl;
	}
	
	//GraphicsEngine::cameraForward = GraphicsEngine::cameraPosition;
	//GraphicsEngine::cameraForward.z += 15;
	InputManager();

	RotateCamera();

	GraphicsEngine::MoveCamera();
}

void cameraController::OnMouseClick()
{
	//if right mouse button is pressed that means we are dragging the mouse, else it means we stopped dragging
	if(ButtonsPressed::IsRightMouseButtonClicking())
	{
		isDragging = true;
		initialMousePos = ButtonsPressed::ReturnMousePos();
		initialCameraPitch = GraphicsEngine::cameraPitch;
		initialCameraYaw = GraphicsEngine::cameraYaw;
		
	}
	else { isDragging = false; initialMousePos = glm::vec2(0.5, 0.5);}
}

//this will manage the key inputs for the camera
void cameraController::InputManager()
{
	
	//if its the first time on the loop move the camera to the ball pos, and then save that pos
	if (firstTimeOnLoop == true)
	{
		//move the camera to the white ball pos and have add a clamping value depending on the axis
		GraphicsEngine::cameraPosition = whiteBall->g_position;
		GraphicsEngine::cameraPosition.x -= 18;
		GraphicsEngine::cameraPosition.y -= -8;
		GraphicsEngine::cameraPosition.z -= 19;
		
		//store the current camera pos on the initial and current white ball camera pos variables
		initialWhiteBallCameraPos = GraphicsEngine::cameraPosition;
		currentWhiteBallCameraPos = initialWhiteBallCameraPos;
		
	}


	if (ButtonsPressed::keys['1'] == true)
		MoveCameraToWhiteBallPos();
	else if (ButtonsPressed::keys['2'] == true)
		MoveCameraToWhiteBallRightPos();
	else if (ButtonsPressed::keys['3'] == true)
		MoveCameraToWhiteBallLeftPos();
	else if (ButtonsPressed::keys['4'] == true)
		MoveCameraToWhiteBallBackPos();
	else if (ButtonsPressed::keys['5'] == true)
		MoveCameraToWhiteBallDiagonalBackLeftPos();
	else if (ButtonsPressed::keys['6'] == true)
		MoveCameraToWhiteBallDiagonalFrontLeftPos();
	else if (ButtonsPressed::keys['7'] == true)
		MoveCameraToWhiteBallDiagonalBackRightPos();
	else if (ButtonsPressed::keys['8'] == true)
		MoveCameraToWhiteBallDiagonalFrontRightPos();
	else if (ButtonsPressed::keys['9'] == true)
		MoveCameraToTopView();
	
	if (ButtonsPressed::keys[','])
		GraphicsEngine::cameraYaw += 1;
	
	if (ButtonsPressed::keys['.'])
		GraphicsEngine::cameraYaw -= 1;
	
	
	
	//tell the code that this isnt the first frame
	firstTimeOnLoop = false;
}

//when this function is called it will move the camera to the white ball pos
void cameraController::MoveCameraToWhiteBallPos()
{
	//tell thbe copde to be on the front pos
	currerntCameraPos = FRONTPOS;

	GraphicsEngine::cameraPitch = 0;
	GraphicsEngine::cameraYaw = -90;
	//if the ball has moved since the last time (i use the clamping values from above) store the white ball pos
	//if (currentWhiteBallCameraPos.x != (initialWhiteBallCameraPos.x - (whiteBall->g_position.x - 18)))
		currentWhiteBallCameraPos.x = -(initialWhiteBallCameraPos.x - (whiteBall->g_position.x - 18.2));
	//currentWhiteBallCameraPos.y -= initialWhiteBallCameraPos.y - whiteBall->g_position.y;
	//if (currentWhiteBallCameraPos.z != (initialWhiteBallCameraPos.z - (whiteBall->g_position.z - 19)))
		currentWhiteBallCameraPos.z = -(initialWhiteBallCameraPos.z - (whiteBall->g_position.z - 19));

	//get the difference of the intial camera pos and the current to move the camera to the ball pos
	float diffX = initialWhiteBallCameraPos.x - currentWhiteBallCameraPos.x;
	//float diffY = initialWhiteBallCameraPos.y - currentWhiteBallCameraPos.y;
	float diffZ = initialWhiteBallCameraPos.z - currentWhiteBallCameraPos.z;
	GraphicsEngine::cameraPosition.x = diffX;
	GraphicsEngine::cameraPosition.y = 7.f;
	GraphicsEngine::cameraPosition.z = diffZ;

}

//when this function is called it will move the camera to the right of the white ball pos
void cameraController::MoveCameraToWhiteBallRightPos()
{
	//tell thbe copde to be on the front pos
	currerntCameraPos = RIGHTPOS;
	GraphicsEngine::cameraPitch = 0;
	GraphicsEngine::cameraYaw = 0;
	//if the ball has moved since the last time (i use the clamping values from above) store the white ball pos
	//if (currentWhiteBallCameraPos.x != (initialWhiteBallCameraPos.x - ((whiteBall->g_position.x - 18))))
		currentWhiteBallCameraPos.x = -(initialWhiteBallCameraPos.x - (whiteBall->g_position.x - 20.226f));
	//currentWhiteBallCameraPos.y -= initialWhiteBallCameraPos.y - whiteBall->g_position.y;
	//if (currentWhiteBallCameraPos.z != (initialWhiteBallCameraPos.z - (whiteBall->g_position.z - 19)))
		currentWhiteBallCameraPos.z = -(initialWhiteBallCameraPos.z - (whiteBall->g_position.z - 17.3));

	//get the difference of the intial camera pos and the current to move the camera to the ball pos
	float diffX = initialWhiteBallCameraPos.x - currentWhiteBallCameraPos.x;
	//float diffY = initialWhiteBallCameraPos.y - currentWhiteBallCameraPos.y;
	float diffZ = initialWhiteBallCameraPos.z - currentWhiteBallCameraPos.z;
	GraphicsEngine::cameraPosition.x = diffX;
	GraphicsEngine::cameraPosition.y = 7.f;
	GraphicsEngine::cameraPosition.z = diffZ;
}

//when this function is called it will move the camera to the left of the white ball pos
void cameraController::MoveCameraToWhiteBallLeftPos()
{
	currerntCameraPos = LEFTPOS;
	GraphicsEngine::cameraPitch = 0;
	GraphicsEngine::cameraYaw = 180;
	//if the ball has moved since the last time (i use the clamping values from above) store the white ball pos
	//if (currentWhiteBallCameraPos.x != (initialWhiteBallCameraPos.x - ((whiteBall->g_position.x - 18))))
	currentWhiteBallCameraPos.x = -(initialWhiteBallCameraPos.x - (whiteBall->g_position.x - 16.226f));
	//currentWhiteBallCameraPos.y -= initialWhiteBallCameraPos.y - whiteBall->g_position.y;
	//if (currentWhiteBallCameraPos.z != (initialWhiteBallCameraPos.z - (whiteBall->g_position.z - 19)))
	currentWhiteBallCameraPos.z = -(initialWhiteBallCameraPos.z - (whiteBall->g_position.z - 17.3));

	//get the difference of the intial camera pos and the current to move the camera to the ball pos
	float diffX = initialWhiteBallCameraPos.x - currentWhiteBallCameraPos.x;
	//float diffY = initialWhiteBallCameraPos.y - currentWhiteBallCameraPos.y;
	float diffZ = initialWhiteBallCameraPos.z - currentWhiteBallCameraPos.z;
	GraphicsEngine::cameraPosition.x = diffX;
	GraphicsEngine::cameraPosition.y = 7.f;
	GraphicsEngine::cameraPosition.z = diffZ;
}

//when this function is called it will move the camera to the back of the white ball pos
void cameraController::MoveCameraToWhiteBallBackPos()
{
	//tell thbe copde to be on the front pos
	currerntCameraPos = BACKPOS;
	GraphicsEngine::cameraPitch = 0;
	GraphicsEngine::cameraYaw = 90;
	//if the ball has moved since the last time (i use the clamping values from above) store the white ball pos
	//if (currentWhiteBallCameraPos.x != (initialWhiteBallCameraPos.x - (whiteBall->g_position.x - 18)))
		currentWhiteBallCameraPos.x = -(initialWhiteBallCameraPos.x - (whiteBall->g_position.x - 18.2));
	//currentWhiteBallCameraPos.y -= initialWhiteBallCameraPos.y - whiteBall->g_position.y;
	//if (currentWhiteBallCameraPos.z != (initialWhiteBallCameraPos.z - (whiteBall->g_position.z - 19)))
		currentWhiteBallCameraPos.z = -(initialWhiteBallCameraPos.z - (whiteBall->g_position.z - 15));

	//get the difference of the intial camera pos and the current to move the camera to the ball pos
	float diffX = initialWhiteBallCameraPos.x - currentWhiteBallCameraPos.x;
	//float diffY = initialWhiteBallCameraPos.y - currentWhiteBallCameraPos.y;
	float diffZ = initialWhiteBallCameraPos.z - currentWhiteBallCameraPos.z;
	GraphicsEngine::cameraPosition.x = diffX;
	GraphicsEngine::cameraPosition.y = 7.f;
	GraphicsEngine::cameraPosition.z = diffZ;
}

//this will move the camera to the diagonal
void cameraController::MoveCameraToWhiteBallDiagonalBackLeftPos()
{
	//tell thbe copde to be on the front pos
	currerntCameraPos = DIAGONALBACKLEFT;
	GraphicsEngine::cameraPitch = 0;
	GraphicsEngine::cameraYaw = -135;
	//if the ball has moved since the last time (i use the clamping values from above) store the white ball pos
	//if (currentWhiteBallCameraPos.x != (initialWhiteBallCameraPos.x - (whiteBall->g_position.x - 18)))
	currentWhiteBallCameraPos.x = -(initialWhiteBallCameraPos.x - (whiteBall->g_position.x) + 16.83);
	//currentWhiteBallCameraPos.y -= initialWhiteBallCameraPos.y - whiteBall->g_position.y;
	//if (currentWhiteBallCameraPos.z != (initialWhiteBallCameraPos.z - (whiteBall->g_position.z - 19)))
	currentWhiteBallCameraPos.z = -(initialWhiteBallCameraPos.z - (whiteBall->g_position.z) + 18.52f);

	//get the difference of the intial camera pos and the current to move the camera to the ball pos
	float diffX = initialWhiteBallCameraPos.x - currentWhiteBallCameraPos.x;
	//float diffY = initialWhiteBallCameraPos.y - currentWhiteBallCameraPos.y;
	float diffZ = initialWhiteBallCameraPos.z - currentWhiteBallCameraPos.z;
	GraphicsEngine::cameraPosition.x = diffX;
	GraphicsEngine::cameraPosition.y = 7.f;
	GraphicsEngine::cameraPosition.z = diffZ;
}

//this will move the camera to the diagonal
void cameraController::MoveCameraToWhiteBallDiagonalFrontLeftPos()
{
	//tell thbe copde to be on the front pos
	currerntCameraPos = DIAGONALFRONTLEFT;
	GraphicsEngine::cameraPitch = 0;
	GraphicsEngine::cameraYaw = -225;
	//if the ball has moved since the last time (i use the clamping values from above) store the white ball pos
	//if (currentWhiteBallCameraPos.x != (initialWhiteBallCameraPos.x - (whiteBall->g_position.x - 18)))
	currentWhiteBallCameraPos.x = -(initialWhiteBallCameraPos.x - (whiteBall->g_position.x) + 16.83);
	//currentWhiteBallCameraPos.y -= initialWhiteBallCameraPos.y - whiteBall->g_position.y;
	//if (currentWhiteBallCameraPos.z != (initialWhiteBallCameraPos.z - (whiteBall->g_position.z - 19)))
	currentWhiteBallCameraPos.z = -(initialWhiteBallCameraPos.z - (whiteBall->g_position.z) + 15.69f);

	//get the difference of the intial camera pos and the current to move the camera to the ball pos
	float diffX = initialWhiteBallCameraPos.x - currentWhiteBallCameraPos.x;
	//float diffY = initialWhiteBallCameraPos.y - currentWhiteBallCameraPos.y;
	float diffZ = initialWhiteBallCameraPos.z - currentWhiteBallCameraPos.z;
	GraphicsEngine::cameraPosition.x = diffX;
	GraphicsEngine::cameraPosition.y = 7.f;
	GraphicsEngine::cameraPosition.z = diffZ;
}

//this will move the camera to the diagonal
void cameraController::MoveCameraToWhiteBallDiagonalBackRightPos()
{
	//tell thbe copde to be on the front pos
	currerntCameraPos = DIAGONALBACKRIGHT;
	GraphicsEngine::cameraPitch = 0;
	GraphicsEngine::cameraYaw = -45;
	//if the ball has moved since the last time (i use the clamping values from above) store the white ball pos
	//if (currentWhiteBallCameraPos.x != (initialWhiteBallCameraPos.x - (whiteBall->g_position.x - 18)))
	currentWhiteBallCameraPos.x = -(initialWhiteBallCameraPos.x - (whiteBall->g_position.x - 19.8));
	//currentWhiteBallCameraPos.y -= initialWhiteBallCameraPos.y - whiteBall->g_position.y;
	//if (currentWhiteBallCameraPos.z != (initialWhiteBallCameraPos.z - (whiteBall->g_position.z - 19)))
	currentWhiteBallCameraPos.z = -(initialWhiteBallCameraPos.z - (whiteBall->g_position.z - 18.96));

	//get the difference of the intial camera pos and the current to move the camera to the ball pos
	float diffX = initialWhiteBallCameraPos.x - currentWhiteBallCameraPos.x;
	//float diffY = initialWhiteBallCameraPos.y - currentWhiteBallCameraPos.y;
	float diffZ = initialWhiteBallCameraPos.z - currentWhiteBallCameraPos.z;
	GraphicsEngine::cameraPosition.x = diffX;
	GraphicsEngine::cameraPosition.y = 7.f;
	GraphicsEngine::cameraPosition.z = diffZ;
}

//this will move the camera to the diagonal
void cameraController::MoveCameraToWhiteBallDiagonalFrontRightPos()
{
	//tell thbe copde to be on the front pos
	currerntCameraPos = DIAGONALFRONTRIGHT;
	GraphicsEngine::cameraPitch = 0;
	GraphicsEngine::cameraYaw = 45;
	//if the ball has moved since the last time (i use the clamping values from above) store the white ball pos
	//if (currentWhiteBallCameraPos.x != (initialWhiteBallCameraPos.x - (whiteBall->g_position.x - 18)))
	currentWhiteBallCameraPos.x = -(initialWhiteBallCameraPos.x - (whiteBall->g_position.x - 19.615));
	//currentWhiteBallCameraPos.y -= initialWhiteBallCameraPos.y - whiteBall->g_position.y;
	//if (currentWhiteBallCameraPos.z != (initialWhiteBallCameraPos.z - (whiteBall->g_position.z - 19)))
	currentWhiteBallCameraPos.z = -(initialWhiteBallCameraPos.z - (whiteBall->g_position.z - 15.84));

	//get the difference of the intial camera pos and the current to move the camera to the ball pos
	float diffX = initialWhiteBallCameraPos.x - currentWhiteBallCameraPos.x;
	//float diffY = initialWhiteBallCameraPos.y - currentWhiteBallCameraPos.y;
	float diffZ = initialWhiteBallCameraPos.z - currentWhiteBallCameraPos.z;
	GraphicsEngine::cameraPosition.x = diffX;
	GraphicsEngine::cameraPosition.y = 7.f;
	GraphicsEngine::cameraPosition.z = diffZ;
}


//this will move the camera to the top view
void cameraController::MoveCameraToTopView()
{
	//tell thbe copde to be on the front pos
	currerntCameraPos = TOPPOS;
	GraphicsEngine::cameraPosition=glm::vec3(-9, -15.6, -15);
	GraphicsEngine::cameraPitch = 90;
	GraphicsEngine::cameraYaw = 90;
}

//this is going to rotate the camera when clicking right mouse
void cameraController::RotateCamera()
{
	//if we are dragging the camera
	/*if (isDragging)
	{
		//get the differencial pitch and yaw from the beggining of the drag
		float differensePitch = (initialMousePos.y - ButtonsPressed::ReturnMousePos().y) ;
		float differenseYaw = (initialMousePos.x - ButtonsPressed::ReturnMousePos().x);
		
		
		if (differensePitch<0.05 && differensePitch>-0.05 && differenseYaw<0.5 && differenseYaw>-0.5)
		{
				
		}
		//if i moved atleast 0.5 in any axis do the rotation calculation
		else {
			
			//the times 20 is just for it to move faster
			differensePitch = (differensePitch * 20) - initialCameraPitch;

			differenseYaw = (differenseYaw * 20) - initialCameraYaw;

			GraphicsEngine::cameraPitch = differensePitch;
			GraphicsEngine::cameraYaw = -differenseYaw;

			
		}
	
	}*/
		
}