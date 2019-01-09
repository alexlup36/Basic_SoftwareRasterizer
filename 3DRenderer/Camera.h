#pragma once
#include "Matrix4.h"

class Matrix4;
class Vector3;

class Camera
{
public:
	Camera(void);
	~Camera(void);

	static Matrix4 CreateViewMatrix(const Vector3& position, const Vector3& at, const Vector3& up);
	static Matrix4 CreateProjectionMatrix(const float width, const float height, const float dn, const float df);
	static Matrix4 CreatePerspectiveFieldOfView(float fov, float aspect, float dn, float df);
};

