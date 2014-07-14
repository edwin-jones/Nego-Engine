// Homework.cpp : Defines the entry point for the console application.temp.bmp
#include "stdafx.h"
#include "Model.h"
#include "Level.h"
#include "Input.h"
#include "Block.h"
#include <math.h>


Vector3F rotation = Vector3F(0);
Vector3F position = Vector3F(0);

const float Speed = 1.5f;

const int targetFPS = 60;
const int targetUPS = 120;
double coreFrequency = 0.0f;

//global functions declarations (we will implement them later.
void UpdateTimerClockFreq();
INT64 GetTimerCurrentTime();
void Update();

Renderer * MainRenderer;

//entry point for the window
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int iCmdShow)
{

	//Bitmap * bmp = new Bitmap("C:\\Users\\Edwin\\Documents\\Visual Studio 2013\\Projects\\Homework\\Debug\\Temp.bmp");

	Level * levelOne = new Level("level1.csv");
	Level * floor = new Level("floor.csv");

	MainRenderer = new Renderer();

	MainRenderer->Init(hInstance, 512, 512);

	//load floor blocks.
	for (int y = 0; y < floor->GetHeight(); y++)
	{
		for (int x = 0; x < floor->GetWidth(); x++)
		{
			if (floor->GetBlock(x, y) == 0)
			{
				MainRenderer->AddToScene(new Block(Vector3F(x * 30, y * 30, 30), Block::BlockType::Floor));
			}
		}
	}

	//load floor wall blocks for level 1.
	for (int y = 0; y < levelOne->GetHeight(); y++)
	{
		for (int x = 0; x < levelOne->GetWidth(); x++)
		{
			if (levelOne->GetBlock(x, y) == 0)
			{
				MainRenderer->AddToScene(new Block(Vector3F(x * 30, y * 30, 0), Block::BlockType::Wall));
			}
		}
	}

	
	
	


	MainRenderer->SetBackBufferColor(Vector4F(0.0f, 0.5f, 1.0f, 1.0f));

	//MainRenderer->GetCamera()->SetPosition(Vector3F(-20.0f, -20.0f, -1000.0f));
	position = Vector3F(0, 0, 0.0f);
	MainRenderer->GetCamera()->SetPosition(position);
	rotation.X = 280.0f;

	//HACK this will make player view look a little higher thant it is.
	position.Z -= 10;

	//HACK place player origin far back enough they can see the level
	position.Y -= 200;

	rotation.Z += 160;

	//get clockspeed
	LARGE_INTEGER li;
	UpdateTimerClockFreq();

	INT64 lastDraw = GetTimerCurrentTime();
	INT64 lastUpdate = GetTimerCurrentTime();



	//while checking for window messages, such as quit/exit
	while (MainRenderer->Update())
	{
		//check if we should update
		if (((GetTimerCurrentTime() - lastUpdate) / coreFrequency) > (1000 / targetUPS))
		{
			Update();
			lastUpdate = GetTimerCurrentTime();
			UpdateTimerClockFreq();
		}

		//check if we should draw, lock at 59fps. this will reduce stutter to a degree but 60 fps would be best.
		if (((GetTimerCurrentTime() - lastDraw) / coreFrequency) > (900 / targetFPS))
		{
			MainRenderer->Draw();
			lastDraw = GetTimerCurrentTime();
			UpdateTimerClockFreq();
		}
	}

	//dispose of memory we no longer need.
	delete MainRenderer;

	return 0;
}

void UpdateTimerClockFreq()
{
	LARGE_INTEGER li;
	QueryPerformanceFrequency(&li);
	coreFrequency = double(li.QuadPart) / 1000.0;
}

INT64 GetTimerCurrentTime()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);

	return li.QuadPart;
}



void Update()
{
	//when the cubes rotate a full circle, reverse their direction of rotation.
	/*if (rotation >= 360.0f)
	{
		rotationUpdate = -1.0f;
	}
	else if (rotation < 0)
	{
		rotationUpdate = 1;
	}*/

	//calculate input
	if (Input::IsKeyDown(VK_UP))
	{
		position.X += sin(rotation.Z) * Speed;
		position.Y += cos(rotation.Z) * Speed;
		//position.X += Speed;
	}
	else if (Input::IsKeyDown(VK_DOWN))
	{
		position.X -= sin(rotation.Z) * Speed;
		position.Y -= cos(rotation.Z) * Speed;
	}
	else if (Input::IsKeyDown(VK_LEFT))
	{
		rotation.Z += Speed;
	}
	else if (Input::IsKeyDown(VK_RIGHT))
	{
		rotation.Z -= Speed;
	}


	MainRenderer->GetCamera()->SetRotation(rotation);
	MainRenderer->GetCamera()->SetPosition(position);
}