#include "StdAfx.h"
#include "Transformation.h"


Transformation::Transformation(void)
{
	_rotation = Matrix3::Identity;
	_scale = Vector3(1.0f, 1.0f, 1.0f);
	_translation = Vector3::Zero();
}


Transformation::~Transformation(void)
{
}


Matrix3& Transformation::Rotation()
{
	return _rotation;
}

Vector3& Transformation::Translation()
{
	return _translation;
}

Vector3& Transformation::Scale()
{
	return _scale;
}

void Transformation::SetRotation(const Matrix3& rot)
{
	_rotation = rot;
}

const Matrix3& Transformation::GetRotation() const
{
	return _rotation;
}

void Transformation::SetTranslation(const Vector3& trans)
{
	_translation = trans;
}

const Vector3& Transformation::GetTranslation() const
{
	return _translation;
}

void Transformation::SetUniformScale(float s)
{
	_scale = Vector3(s, s, s);
}

void Transformation::SetScale(const Vector3& s)
{
	_scale = s;
}

const Vector3& Transformation::GetScale() const
{
	return _scale;
}

Matrix3 Transformation::GetTransformation()
{
	_transformation =  _rotation * Matrix3::Matrix3Scale(_scale);
	
	return _transformation;
}

void Transformation::MakeIdentity()
{
	_transformation = Matrix3::Identity;
}

void Transformation::MakeUnitScale()
{
	_scale = Vector3(1.0f, 1.0f, 1.0f);
}

bool Transformation::IsIdentity() const
{
	return (Matrix3::Identity == _transformation) && (_translation == Vector3::Zero());
}
	
bool Transformation::IsUniformScale() const
{
	return (_scale.GetX() == _scale.GetY()) && (_scale.GetY() == _scale.GetZ());
}

Vector3 Transformation::ApplyForward(const Vector3& input) const
{
	return _transformation * input + _translation;
}
	
void Transformation::ApplyForward(int quantity, const Vector3* input, Vector3* output) const
{
	int i = 0;

	while (i < quantity)
	{
		output[i] = _transformation * input[i] + _translation;
		i++;
	}
}

Triangle Transformation::ApplyForward(Triangle& input)
{
	Matrix3 scale = Matrix3::Matrix3Scale(_scale);
	
	Vector3 pos = input.vertices[0].Position();
	input.vertices[0].SetPosition(_rotation * scale * pos + _translation);

	pos = input.vertices[1].Position();
	input.vertices[1].SetPosition(_rotation * scale * pos + _translation);

	pos = input.vertices[2].Position();
	input.vertices[2].SetPosition(_rotation * scale * pos + _translation);
	
	return input;
}

void Transformation::SetProduct(Transformation& t1, Transformation& t2)
{
	_transformation = t1.GetTransformation() * t2.GetTransformation();
}
	
void Transformation::SetInverse(Transformation& inverse)
{
	_transformation = Matrix3::Matrix3Inverse(inverse.GetTransformation());
}