#pragma once
//this will let me create a map, wich is basically an 2 size array, but the first element is a key and the second is a element
#include <map>
#include <glm/glm.hpp>
//this script will return if a button is pressed, mouse position etc
class ButtonsPressed
{
private:
	//these 3 bools will be true if the currousponding mouse button is being pressed
	static bool leftMouseButton;
	static bool rightMouseButton;
	static bool middleMouseButton;
	//this will store the mouse position
	static glm::vec2 mousePos;
public:
	/*this will create 2 maps for the keys, one for normal keys and another for the special keys(arrow keys etc),
	it will hold a char or an int (keycode), and a boolean (if its being pressed or not) they are static because we
	only need one copy of them in the entire game*/
	static std::map<char, bool> keys;
	static std::map<int, bool> specialKeys;//we use int here, because the special keys uses an int as the keycode, not a char

	//this is gonna return true if the currosponding mouse button is clicking
	static bool IsLeftMouseButtonClicking();
	static bool IsRightMouseButtonClicking();
	static bool IsMiddleMouseButtonClicking();
	static glm::vec2 ReturnMousePos();
	//this is gonna set if they are being clicked or not, this is suposed to only be accessed by the game engine
	static void SetLeftMouseButtonClicking(bool);
	static void SetRightMouseButtonClicking(bool);
	static void SetMiddleMouseButtonClicking(bool);
	static void SetMousePos(glm::vec2);
};

