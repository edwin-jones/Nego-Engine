#include "stdafx.h"
#include "level.h"
#include <fstream>
#include <sstream>


//CTOR
Level::Level()
{
}

//SECONDARY CTOR
Level::Level(string fileLocation)
{
	//open file
	string line;
	vector<vector<string>> Lines;

	//open the txt file and read until the end of it
	ifstream myfile(fileLocation);
	if (myfile.is_open() && !myfile.eof())
	{
		int height = 0; //calulcate how many rows
		while (getline(myfile, line)) //get the current line in the txt file.
		{
			++height;
			std::stringstream ss(line);
			vector<string> lineParts;

			int width = 0; //calculate how many columns, assume non jagged map.

			while (!ss.eof()) //read until end of string
			{
				++width; //incremement width for each column

				string partOfLine;              
				getline(ss, partOfLine, ',');//read until comma, not '\0'  
				
				lineParts.push_back(partOfLine);  //push line segement into line vector.
			}

			Lines.push_back(lineParts); //push vector of segements into vector<string> vector.

			Width = width;		
		}

		//close the file!
		myfile.close();

		Height = height;

		MapData = new int[Width * Height];

		for (int i = 0; i < Height; i++)
		{
			vector<string> currentLineParts = Lines[i];

			for (int j = 0; j < Width; j++)
			{
				MapData[(Height * i) + j] = atoi(currentLineParts[j].c_str());
			}
		}
	}
}

//DTOR
Level::~Level()
{
}

int Level::GetHeight()
{
	return Height;
}

int Level::GetWidth()
{
	return Width;
}

int Level::GetBlock(int x, int y)
{
	return MapData[(Height * y) + x];
}

void Level::SetBlock(int x, int y, int type)
{
	MapData[(Height * y) + x] = type;
}
