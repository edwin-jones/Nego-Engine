#pragma once
class Level
{
public:
	Level();
	Level(string fileLocation);

	~Level();
	int GetHeight();
	int GetWidth();
	int GetBlock(int x, int y);
	void SetBlock(int x, int y, int type);


private:
	int * MapData;
	int Width;
    int Height;
};

