#pragma once
class Bitmap
{

public:
	Bitmap(string filename);
	~Bitmap();
	int GetWidth();
	int GetHeight();
	Vector2I GetSize();
	byte* GetData();

private:
	byte Header[54];
	unsigned int Blobstart;
	unsigned int Height;
	unsigned int Width;
	byte * Data;
};

