#include "stdafx.h"
#include "Bitmap.h"




Bitmap::Bitmap(string filename)
{
	//open file
	FILE * file;

	fopen_s(&file,filename.c_str(), "r");

	//read file data into header array.
	fread(Header, 1, 54, file);

	//the point at which the bitmap pixel data starts
	Blobstart = *(int*)&(Header[0x0A]);
	//sanity check, if blobstart is undefined, assume its 54 bytes in

	if (Blobstart == 0)Blobstart = 54;

	Width = *(int*)&(Header[0x12]);
	Height = *(int*)&(Header[0x16]);

	unsigned int totalBytes = Width*Height * 3;

	Data = new byte[totalBytes];

	fread(Data, 1, totalBytes, file);

	//close the file//release the handle.
	fclose(file);
}


Bitmap::~Bitmap()
{
}

int Bitmap::GetWidth()
{
	return Width;
}
int Bitmap::GetHeight()
{
	return Height;
}

Vector2I Bitmap::GetSize()
{
	return Vector2I(Width, Height);
}

byte * Bitmap::GetData()
{
	return Data;
}
