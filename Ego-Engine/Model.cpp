#include "stdafx.h"
#include "Model.h"
#include "Bitmap.h";


//CTOR
Model::Model(Vector3F position)
{
	mTexture = new Bitmap("Temp.bmp");

	currentTextureIdentifier = 0;

	mPosition = position;

	mVerts = 24;

	const float diameter = 30.0f;

	//Setup vertices (some will be reused)
	mVertexList = new GLfloat[72]
	{
		0.0f, 0.0f, 0.0f, //front? //0
			diameter, 0.0f, 0.0f, //1
			0.0f, diameter, 0.0f,
			diameter, diameter, 0.0f, //3

			0.0f, 0.0f, -diameter, //left? //4
			0.0f, 0.0f, 0.0f,
			0.0f, diameter, -diameter,
			0.0f, diameter, 0.0f, //7

			0, 0.0f, -diameter, //back? //8
			0, diameter, -diameter, //9
			diameter, 0, -diameter, //10
			diameter, diameter, -diameter, //11

			diameter, 0.0f, -diameter, //right  //12   
			diameter, diameter, -diameter, //14
			diameter, 0.0f, 0.0f, //13
			diameter, diameter, 0.0f, //15      

			0.0f, diameter, -diameter, //top //16
			0.0f, diameter, 0.0f, //17
			diameter, diameter, -diameter, //19
			diameter, diameter, 0, //18

			diameter, 0, -diameter, //23
			diameter, 0, 0, //22
			0.0f, 0.0f, -diameter, //bottom //20
			0.0f, 0.0f, 0.0f, //21
	};

	mTpList = new GLfloat[48]
	{
			0, 0, //face 1
			1, 0,
			0, 1,
			1, 1,

			0, 0, //face 2
			1, 0,
			0, 1,
			1, 1,

			0, 0, //face 3
			1, 0,
			0, 1,
			1, 1,

			0, 0, //face 4
			1, 0,
			0, 1,
			1, 1,

			0, 0, //face 5
			1, 0,
			0, 1,
			1, 1,

			0, 0, //face 6
			1, 0,
			0, 1,
			1, 1,
	};

	//set up indices, this way we can reuse vertices. //each 3 verts is a triangle, and each side of a cube is made of two triangles/6 verts total.
	//A triangle is drawn counter clockwise, and whichever order the verts are drawn in will affect which way/side the triangle faces.
	//A good trick to flip a triangle of verts (1 2 3) is to swap the last two verts so it becomes (1 3 2).
	mIndices = new GLushort[36]
	{
		0, 1, 2, //front
			3, 2, 1,

			4, 5, 6, //left
			7, 6, 5,

			8, 9, 10, //back
			11, 10, 9,

			12, 13, 14, //left
			15, 14, 13,

			16, 17, 18, //top
			19, 18, 17,

			20, 21, 22, //bottom
			23, 22, 21,
	};

	//map a color to each vertex. We can't recolor if we use a vertex twice so it must be part of the same face of the cube.
	mColours = new GLfloat[72]
	{
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,

			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,

			1.0f, 0.5f, 0.0f,
			1.0f, 0.5f, 0.0f,
			1.0f, 0.5f, 0.0f,
			1.0f, 0.5f, 0.0f,

			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,

			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,

			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,

	};
}

//destructor. Release all memory here.
Model::~Model()
{
	delete[] mVertexList;
	delete[] mIndices;
	delete[] mColours;

	delete mTexture;
}

void Model::PopulateGraphicsArray(GLfloat* vertArray, int* arrayPosition, 
	GLushort* indcArray, int* indcArrayPosition, GLfloat* colArray,
	int* colPosition, GLfloat* tpArray, int* tpPosition)
{

	int initialArrayPosition = *arrayPosition;
	//colors and texture(s)
	for (int i = 0; i < (mVerts * 3); i++)
	{
		vertArray[(*arrayPosition)++] = mVertexList[i] + +(i % 3 == 0 ? mPosition.X : 0) + (i % 3 == 1 ? mPosition.Y : 0) + (i % 3 == 2 ? mPosition.Z : 0);
		colArray[(*colPosition)++] = mColours[i];
	}

	for (int i = 0; i < (mVerts * 2); i++)
	{
		tpArray[(*tpPosition)++] = mTpList[i];
	}
	//verts
	for (int i = 0; i < ((mVerts / 4) * 6); i++)
	{
		indcArray[(*indcArrayPosition)++] = (initialArrayPosition / 3) + mIndices[i];
	}
}

Bitmap * Model::GetTexture()
{
	return mTexture;
}