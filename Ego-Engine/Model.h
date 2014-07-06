#pragma once
class Model
{
	private:
		GLfloat *mVertexList;
		GLushort *mIndices;
		GLfloat *mColours;
		GLfloat *mTpList;

		short mVerts;
		Vector3F mPosition;

	public:
		Model(Vector3F position);
		~Model();

		void PopulateGraphicsArray(GLfloat* vertArray, int* arrayPosition, GLushort* indcArray, int* indcArrayPosition, 
			GLfloat* colArray, int* colPosition, GLfloat* tpArray, int* tpPosition);
};



