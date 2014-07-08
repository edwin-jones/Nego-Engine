#pragma once
class Camera
{
public:
	Camera();
	~Camera();
	void SetPosition(Vector3F position);
	void SetRotation(Vector3F rotation);
	void Apply();

private:
	const int MovementSpeed = 5;
};

