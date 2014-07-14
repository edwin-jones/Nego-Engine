#pragma once

typedef WPARAM Key;

static class Input
{
	
public:
	Input();
	~Input();

	//This method MUST be called before all others and initialises/zeros memory of all internal variables.
	static void Init();

	//This method sets a key state
	static void SetKeyState(Key key, BOOLEAN state);

	//This method checks to see if a key is down.
	static BOOLEAN IsKeyDown(Key key);

private:
	//this array stores the state of all keys on the keyboard as 1/0s.
	static BOOLEAN KeyBoardState[256];
};

