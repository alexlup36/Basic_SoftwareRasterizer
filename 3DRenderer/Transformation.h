#pragma once
#include "3DRenderer.h"
#include "Triangle.h"

class Triangle;

class Transformation
{
public:
	Transformation(void);
	virtual ~Transformation(void);

	static const Transformation IDENTITY;

private:
	Matrix3 _rotation;
	Vector3 _translation;
	Vector3 _scale;

	bool _isIdentity, isUniformScale;

	Matrix3 _transformation;
public:
	Matrix3& Rotation();
	Vector3& Translation();
	Vector3& Scale();

	Matrix3 GetTransformation();

	void SetRotation(const Matrix3& rot);
	const Matrix3& GetRotation() const;

	void SetTranslation(const Vector3& trans);
	const Vector3& GetTranslation() const;

	void SetUniformScale(float s);
	void SetScale(const Vector3& s);
	const Vector3& GetScale() const;

	void MakeIdentity();
	void MakeUnitScale();
	bool IsIdentity() const;
	bool IsUniformScale() const;

	Triangle ApplyForward(Triangle& input);
	Vector3 ApplyForward(const Vector3& input) const;
	void ApplyForward(int quantity, const Vector3* input, Vector3* output) const;

	void SetProduct(Transformation& t1, Transformation& t2);
	void SetInverse(Transformation& inverse);
};

