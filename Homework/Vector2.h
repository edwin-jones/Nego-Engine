#pragma once
template <class T>
class Vector2
{
public:

	T X;
	T Y;


	//default CTOR
	Vector2()
	{
		X = NULL;
		Y = NULL;
	}

	//const means arguments wont be modified (is promise to compiler for optimisation)
	Vector2(const T x, const T y)
	{
		X = x;
		Y = y;
	}

	Vector2(const T xy)
	{
		X = xy;
		Y = xy;
	}

	Vector2(const Vector2<T> &instanceToCopy)
	{
		X = instanceToCopy.X;
		Y = instanceToCopy.Y;
	}

	~Vector2()
	{

	}

	T Length()
	{
		return (T)sqrt((X*X) + (Y*Y));
	}

	T LengthSquared()
	{
		return (T)((X*X) + (Y*Y));
	}
};

