#include "stdafx.h"
#include "Camera.h"
#include "Input.h";

//translations
Vector3F Position;

//rotations
Vector3F Rotation;

Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::SetPosition(Vector3F position)
{
	Position = position;
}

void Camera::SetRotation(Vector3F rotation)
{
	Rotation = rotation;
}

//STUDY THESE FUNCTIONS!
void Camera::Apply()
{
	glLoadIdentity(); //reset GFX card default matrix.



	//only rotate by 2 axis at a time with this system due to gimble lock
	if(abs(Rotation.X > 0.001f)) glRotatef(-Rotation.X, 1, 0, 0); //apply these rotations 
	if(abs(Rotation.Y > 0.001f)) glRotatef(-Rotation.Y, 0, 1, 0);
	if(abs(Rotation.Z > 0.001f)) glRotatef(-Rotation.Z, 0, 0, 1);

	glTranslatef(-Position.X, -Position.Y, -Position.Z); //adjust (times) the default gfx matrix by these values.
}

