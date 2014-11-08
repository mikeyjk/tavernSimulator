#include "InputEngine.h"
#include <iostream>

using namespace std;

InputEngine* InputEngine::Instance()
{
	static InputEngine Instance;
	return &Instance;
}

InputEngine::InputEngine()
{
	resetAllKeys();
}



void InputEngine::initInputControl(std::string type)
{
	InputEngine* input;
	input = InputEngine::Instance();
	
	if(type == "OpenGL")
	{
		glutKeyboardFunc(keyPressed);
		glutKeyboardUpFunc(keyUp);
		glutSpecialFunc(SpecialFunc);
		glutSpecialUpFunc(SpecialUpFunc);
		glutPassiveMotionFunc(MouseMotion);
		glutMouseFunc(MouseFunction);
		mousePoint.x = 0;
		mousePoint.y = 0;
		alphaMousePoint.x = 0;
		alphaMousePoint.y = 0;
		
	}
	else if(type == "DirectX")
	{

	}


	
}

//this is used to cast all the shifted keys to no shifted keys, also casts all lower case to upper case
unsigned char ShiftCheck(unsigned char key)
{
	switch (key)
	{
	case '~':
		key = '`';
		break;
	case '!':
		key = '1';
		break;
	case '@':
		key = '2';
		break;
	case '#':
		key = '3';
		break;
	case '$':
		key = '4';
		break;
	case '%':
		key = '5';
		break;
	case '^':
		key = '6';
		break;
	case '&':
		key = '7';
		break;
	case '*':
		key = '8';
		break;
	case '(':
		key = '9';
		break;
	case ')':
		key = '0';
		break;
	case '_':
		key = '-';
		break;
	case '+':
		key = '=';
		break;
	case '{':
		key = '[';
		break;
	case '}':
		key = ']';
		break;
	case ':':
		key = ';';
		break;
	case '"':
		key = 96;//ascii for "
		break;
	case '<':
		key = ',';
		break;
	case '>':
		key = '.';
		break;
	case '?':
		key = '/';
		break;
	case '|':
		key = 92; // ascii for
			break;
	}

	if(key > 96 && key < 123)
	{
		key -= 32;// cast any chars to upper case
	}

	return key;
}

void InputEngine::keyPressed(unsigned char key, int x, int y)
{
	InputEngine* input;
	input = InputEngine::Instance();

	key = ShiftCheck(key);

	if(input->keyStates[key] == false)
	{
		input->keyStatesDown[key] = true;
		input->keyStates[key] = true;
	}
	else
	{
		input->keyStatesDown[key] = false;
		input->keyStates[key] = true;
	}
}

void InputEngine::keyUp(unsigned char key, int x, int y)
{
	InputEngine* input;
	input = InputEngine::Instance();

	key = ShiftCheck(key);

	input->keyStates[key] = false;
	input->keyStatesUp[key] = true;
}

void InputEngine::SpecialFunc(int key, int x, int y)
{

	InputEngine* input;
	input = InputEngine::Instance();

	if(input->specialKeys[key] == false)
	{
		input->specialKeysDown[key] = true;
		input->specialKeys[key] = true;
	}
	else
	{
		input->specialKeysDown[key] = false;
		input->specialKeys[key] = true;
	}

}

void InputEngine::SpecialUpFunc(int key, int x, int y)
{
	InputEngine* input;
	input = InputEngine::Instance();


	input->specialKeys[key] = false;
	input->specialKeysUp[key] = true;

}




void InputEngine::MouseMotion(int x ,int y)
{
	InputEngine* input;
	input = InputEngine::Instance();


	input->mousePoint.x = (float)x;
	input->mousePoint.y = (float)y;

	 input->alphaMousePoint.x = glutGet(GLUT_WINDOW_WIDTH)/2 - (float)x;
	 input->alphaMousePoint.y = (float)y - glutGet(GLUT_WINDOW_HEIGHT)/2;
}

void InputEngine::MouseFunction(int button, int state, int x, int y) 
{
	InputEngine* input;
	input = InputEngine::Instance();

	input->mousePoint.x = (float)x;
	input->mousePoint.y = (float)y;

	

	 input->alphaMousePoint.x = glutGet(GLUT_WINDOW_WIDTH)/2 - (float)x;
	 input->alphaMousePoint.y = (float)y - glutGet(GLUT_WINDOW_HEIGHT)/2;

	 if (button == 35)
		 button = 3;
	 if (button == 36)
		 button = 4;

	input->mouseButtonsDown[button] = true;

	if(input->mouseButtons[button] == false && state == GLUT_DOWN)
	{
		input->mouseButtonsDown[button] = true;
		input->mouseButtons[button] = true;
	}
	else if(state == GLUT_UP)
	{
		input->mouseButtonsUp[button] = true;

		if(button != 3 && button != 4)//added because the mouse scroll doesnt work the same as the others
		{
			input->mouseButtons[button] = false;
			input->mouseButtonsDown[button] = false;
		}
	}
	else
	{
		input->mouseButtonsDown[button] = false;
		input->mouseButtons[button] = true;
		
	}

	//need to add function for mouseDown, and mouseButtons
}

void InputEngine::setMouseFixed(bool fix)
{
	fixedMouse = fix;
	if(fix)
	{
		glutSetCursor(GLUT_CURSOR_NONE);
	}
	else
	{
		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	}
}

bool InputEngine::getMouseFixed()
{
	return fixedMouse;
}

bool switchCase(KeyCode key, bool keyState[256], bool specialKeys[120])
{
	bool keyDown = false;

	switch(key)
	{
	case KeyCode::A:
		
		keyDown = keyState['A'];
		break;
	case KeyCode::B:
		keyDown = keyState['B'];
		break;
	case KeyCode::C:
		keyDown = keyState['C'];
		break;
	case KeyCode::D:
		keyDown = keyState['D'];
		break;
	case KeyCode::E:
		keyDown = keyState['E'];
		break;
	case KeyCode::F:
		keyDown = keyState['F'];
		break;
	case KeyCode::G:
		keyDown = keyState['G'];
		break;
	case KeyCode::H:
		keyDown = keyState['H'];
		break;
	case KeyCode::I:
		keyDown = keyState['I'];
		break;
	case KeyCode::J:
		keyDown = keyState['J'];
		break;
	case KeyCode::K:
		keyDown = keyState['K'];
		break;
	case KeyCode::L:
		keyDown = keyState['L'];
		break;
	case KeyCode::M:
		keyDown = keyState['M'];
		break;
	case KeyCode::N:
		keyDown = keyState['N'];
		break;
	case KeyCode::O:
		keyDown = keyState['O'];
		break;
	case KeyCode::P:
		keyDown = keyState['P'];
		break;
	case KeyCode::Q:
		keyDown = keyState['Q'];
		break;
	case KeyCode::R:
		keyDown = keyState['R'];
		break;
	case KeyCode::S:
		keyDown = keyState['S'];
		break;
	case KeyCode::T:
		keyDown = keyState['T'];
		break;
	case KeyCode::U:
		keyDown = keyState['U'];
		break;
	case KeyCode::V:
		keyDown = keyState['V'];
		break;
	case KeyCode::W:
		keyDown = keyState['W'];
		break;
	case KeyCode::X:
		keyDown = keyState['X'];
		break;
	case KeyCode::Y:
		keyDown = keyState['Y'];
		break;
	case KeyCode::Z:
		keyDown = keyState['Z'];
		break;
	case KeyCode::Alpha1:
		keyDown = keyState['1'];
		break;
	case KeyCode::Alpha2:
		keyDown = keyState['2'];
		break;
	case KeyCode::Alpha3:
		keyDown = keyState['3'];
		break;
	case KeyCode::Alpha4:
		keyDown = keyState['4'];
		break;
	case KeyCode::Alpha5:
		keyDown = keyState['5'];
		break;
	case KeyCode::Alpha6:
		keyDown = keyState['6'];
		break;
	case KeyCode::Alpha7:
		keyDown = keyState['7'];
		break;
	case KeyCode::Alpha8:
		keyDown = keyState['8'];
		break;
	case KeyCode::Alpha9:
		keyDown = keyState['9'];
		break;
	case KeyCode::Alpha0:
		keyDown = keyState['0'];
		break;
	case KeyCode::Space:
		keyDown = keyState[32];//ascii value for space
		break;
	case KeyCode::Tilde:
		keyDown = keyState['`'];
		break;
	case KeyCode::Dash:
		keyDown = keyState['-'];
		break;
	case KeyCode::Equals:
		keyDown = keyState['='];
		break;
	case KeyCode::Backspace:
		keyDown = keyState[8];//ascii value for backspace
		break;
	case KeyCode::Tab:
		keyDown = keyState[9];//ascii value for Tab
		break;
	case KeyCode::CapsLock:
		keyDown = keyState[20];//acsii value for Caps
		break;
	case KeyCode::BackSlash:
		keyDown = keyState[92];//ascii value for backslash
		break;
	case KeyCode::Enter:
		keyDown = keyState[13];//ascii value for enter
		break;
	case KeyCode::OpenBracket:
		keyDown = keyState['['];
		break;
	case KeyCode::ClosedBracket:
		keyDown = keyState[']'];
		break;
	case KeyCode::Colon:
		keyDown = keyState[';'];
		break;
	case KeyCode::Apostrophe:
		keyDown = keyState[39];//ascii value for apostrophe
		break;
	case KeyCode::Comma:
		keyDown = keyState[','];
		break;
	case KeyCode::Period:
		keyDown = keyState['.'];
		break;
	case KeyCode::ForwardSlash:
		keyDown = keyState['/'];
		break;
	case KeyCode::Delete:
		keyDown = keyState[127];
		break;
	case KeyCode::Esc:
		keyDown = keyState[27];
		break;
		//begin the cases for all the SpecialKeys
	case KeyCode::Ins:
		keyDown = specialKeys[108];
		break;
	case KeyCode::Home:
		keyDown = specialKeys[106];
		break;
	case KeyCode::End:
		keyDown = specialKeys[107];
		break;
	case KeyCode::PageUp:
		keyDown = specialKeys[104];
		break;
	case KeyCode::PageDown:
		keyDown = specialKeys[105];
		break;
	case KeyCode::F1:
		keyDown = specialKeys[1];
		break;
	case KeyCode::F2:
		keyDown = specialKeys[2];
		break;
	case KeyCode::F3:
		keyDown = specialKeys[3];
		break;
	case KeyCode::F4:
		keyDown = specialKeys[4];
		break;
	case KeyCode::F5:
		keyDown = specialKeys[5];
		break;
	case KeyCode::F6:
		keyDown = specialKeys[6];
		break;
	case KeyCode::F7:
		keyDown = specialKeys[7];
		break;
	case KeyCode::F8:
		keyDown = specialKeys[8];
		break;
	case KeyCode::F9:
		keyDown = specialKeys[9];
		break;
	case KeyCode::F10:
		keyDown = specialKeys[10];
		break;
	case KeyCode::F11:
		keyDown = specialKeys[11];
		break;
	case KeyCode::F12:
		keyDown = specialKeys[12];
		break;
	case KeyCode::LeftKey:
		keyDown = specialKeys[100];
		break;
	case KeyCode::UpKey:
		keyDown = specialKeys[101];
		break;
	case KeyCode::RightKey:
		keyDown = specialKeys[102];
		break;
	case KeyCode::DownKey:
		keyDown = specialKeys[103];
		break;
	case KeyCode::LeftShift:
		keyDown = specialKeys[112];
		break;
	case KeyCode::LeftCtrl:
		keyDown = specialKeys[114];
		break;
	case KeyCode::LeftAlt:
		keyDown = specialKeys[106];
		break;
	case KeyCode::RightShift:
		keyDown = specialKeys[113];
		break;
	case KeyCode::RightCtrl:
		keyDown = specialKeys[115];
		break;
	case KeyCode::RightAlt:
		keyDown = specialKeys[117];
		break;

		}
	


	return keyDown;
}

bool mouseSwitchCase(MouseCode key, bool mouse[5])
{
	bool keyDown = false;

	switch(key)
	{
	case MouseCode::LeftClick:
		keyDown = mouse[0];
		break;
	case MouseCode::RightClick:
		keyDown = mouse[2];
		break;
	case MouseCode::MiddleClick:
		keyDown = mouse[1];
		break;
	case MouseCode::ScrollUp:
		keyDown = mouse[3];
		break;
	case MouseCode::ScrollDown:
		keyDown = mouse[4];
		break;
	}
	return keyDown;
}

bool InputEngine::getKeyDown(KeyCode key)
{
	return switchCase(key, keyStatesDown, specialKeysDown);
}

bool InputEngine::getKey(KeyCode key)
{
	return switchCase(key, keyStates, specialKeys);
}

bool InputEngine::getKeyUp(KeyCode key)
{
	return switchCase(key, keyStatesUp, specialKeysUp);
}

bool InputEngine::getMouseDown(MouseCode key)
{
	return mouseSwitchCase(key, mouseButtonsDown);
}

bool InputEngine::getMouse(MouseCode key)
{
	return mouseSwitchCase(key, mouseButtons);
}

bool InputEngine::getMouseUp(MouseCode key)
{
	return mouseSwitchCase(key, mouseButtonsUp);
}

void InputEngine::resetAllKeys()
{
	for(int i=0;i<256;i++)
	{
		keyStatesDown[i] = false;
		keyStatesUp[i] = false;

		if(i<120)
		{
			specialKeysDown[i] = false;
			specialKeysUp[i] = false;
		}

		if(i < 5)
		{
			mouseButtonsDown[i] = false;
			mouseButtonsUp[i] = false;
		}
	}

	if(fixedMouse)
	{
		setCursorMid();
	}
}

Vec2 InputEngine::getMousePoint()
{
	return mousePoint;
}

Vec2 InputEngine::getAlphaMousePoint()
{
	return alphaMousePoint;
}

void InputEngine::setCursorMid()
{
	SetCursorPos(glutGet(GLUT_WINDOW_X) + glutGet(GLUT_WINDOW_WIDTH)/2, glutGet(GLUT_WINDOW_Y) +  glutGet(GLUT_WINDOW_HEIGHT)/2);
	//glutSetCursor(GLUT_CURSOR_NONE);
}

void InputEngine::switchFixedMouse()
{
	fixedMouse = !fixedMouse;
	if(fixedMouse)
	{
		glutSetCursor(GLUT_CURSOR_NONE);
	}
	else
	{
		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	}
}