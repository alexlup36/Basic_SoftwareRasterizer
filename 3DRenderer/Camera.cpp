#include "StdAfx.h"
#include "Camera.h"


Camera::Camera(void)
{
}


Camera::~Camera(void)
{
}

Matrix4 Camera::CreateViewMatrix(const Vector3& position, const Vector3& at, const Vector3& upVec)
{
	Vector3 view = Vector3::Normalize(at - position);
	Vector3 right = Vector3::Normalize(Vector3::Vec3Cross(view, upVec));
	Vector3 up = Vector3::Vec3Cross(right, view);

	return Matrix4(
		right.GetX(), up.GetX(), view.GetX(), 0.0f,
		right.GetY(), up.GetY(), view.GetY(), 0.0f,
		right.GetZ(), up.GetZ(), view.GetZ(), 0.0f,
		-Vector3::Vec3Dot(position, right), -Vector3::Vec3Dot(position, up), -Vector3::Vec3Dot(position, view), 1.0f);
}

Matrix4 Camera::CreateProjectionMatrix(const float width, const float height, const float dn, const float df)
{
	return Matrix4(
		2/width, 0.0f, 0.0f, 0.0f,
		0.0f, 2/height, 0.0f, 0.0f,
		0.0f, 0.0f, -2/(df - dn), (df + dn) / (dn - df),
		0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 Camera::CreatePerspectiveFieldOfView(float fov, float aspect, float dn, float df)
{
	float m11 = 1.0f / ((float)tan((double)(fov * 0.5f)));
    float m00 = m11 / aspect;
	float m22 = df / (dn - df);
	float m32 = (dn * df) / (dn - df);

    return Matrix4(
		m00, 0, 0, 0,
		0, m11, 0, 0,
		0, 0, m22, -1.0f,
		0, 0, m32, 0);
}
