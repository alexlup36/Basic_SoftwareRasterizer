#include "StdAfx.h"
#include "Light.h"
	

Light::Light(void)
{
	position = Vector3::Zero();
	direction = Vector3::Zero();

	spec = 0;
}

Light::Light(Vector3& pos, Vector3& dir, material& mat, float specularity)
{
	position = pos;
	direction = Vector3::Normalize(dir);
	m.ka = mat.ka;
	m.kd = mat.kd;
	m.ks = mat.ks;

	spec = specularity;
}


Light::~Light(void)
{
}
