#pragma once
template <class T>
class Vector3
{
public:

	T X;
	T Y;
	T Z;

	//default CTOR
	Vector3()
	{
		X = NULL;
		Y = NULL;
		Z = NULL;
	}

	//const means arguments wont be modified (is promise to compiler for optimisation)
	Vector3(const T x, const T y, const T z)
	{
		X = x;
		Y = y;
		Z = z;
	}

	Vector3(const T xyz)
	{
		X = xyz;
		Y = xyz;
		Z = xyz;
	}

	Vector3(const Vector3<T> &instanceToCopy)
	{
		X = instanceToCopy.X;
		Y = instanceToCopy.Y;
		Z = instanceToCopy.Z;
	}

	~Vector3()
	{

	}

	T Length()
	{
		return (T)sqrt((X*X) + (Y*Y) + (Z*Z));
	}

	T LengthSquared()
	{
		return (T)((X*X) + (Y*Y) + (Z*Z));
	}
};

