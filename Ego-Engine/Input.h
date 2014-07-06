#pragma once

typedef WPARAM Key;

static class Input
{
	
public:
	Input();
	~Input();

	static void Init();

	static void RegisterKeyDown(Key key);
	static void RegisterKeyUp(Key key);

private:
	//this array stores the state of all keys on the keyboard as 1/0s.
	static BOOLEAN KeyBoardState[256];
};

