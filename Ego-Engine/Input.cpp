#include "stdafx.h"
#include "Input.h"

//define KeyboardState array.
BOOLEAN Input::KeyBoardState[256] = { 0 };

Input::Input()
{
}


Input::~Input()
{
	
}

void Input::Init()
{
}

void Input::SetKeyState(Key key, BOOLEAN keyPressed)
{
	Input::KeyBoardState[key] = keyPressed;
}

BOOLEAN Input::IsKeyDown(Key key)
{
	return Input::KeyBoardState[key];
}