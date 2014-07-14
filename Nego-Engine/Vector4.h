#pragma once
template <class T>
class Vector4
{
public:

	T X;
	T Y;
	T Z;
	T W;

	//default CTOR
	Vector4()
	{
		X = NULL;
		Y = NULL;
		Z = NULL;
		W = NULL;
	}

	//const means arguments wont be modified (is promise to compiler for optimisation)
	Vector4(const T x, const T y, const T z, const T w)
	{
		X = x;
		Y = y;
		Z = z;
		W = w;
	}

	Vector4(const T xyzm)
	{
		X = xyzm;
		Y = xyzm;
		Z = xyzm;
		W = xyzm;
	}

	Vector4(const Vector4<T> &instanceToCopy)
	{
		X = instanceToCopy.X;
		Y = instanceToCopy.Y;
		Z = instanceToCopy.Z;
		W = instanceToCopy.W;
	}

	~Vector4()
	{

	}

	T Length()
	{
		return (T)sqrt((X*X) + (Y*Y) + (Z*Z) + (W*W));
	}

	T LengthSquared()
	{
		return (T)((X*X) + (Y*Y) + (Z*Z) + (W*W));
	}
};

