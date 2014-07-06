#include "stdafx.h"
#include "Input.h"



Input::Input()
{
}


Input::~Input()
{
	
}

void Input::Init()
{
	//Clean our the keyboard stat array and fill it with zeros.
	ZeroMemory(&Input::KeyBoardState, sizeof(Input::KeyBoardState));
}

void Input::RegisterKeyDown(Key key)
{
	Input::KeyBoardState[key] = 1;
}

void Input::RegisterKeyUp(Key key)
{
	Input::KeyBoardState[key] = 0;
}
