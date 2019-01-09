#include "StdAfx.h"
#include "Matrix3.h"

Matrix3 Matrix3::Identity = Matrix3(
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f);

std::ostream& operator<< (std::ostream& out, const Matrix3& mat)
{
	out<< "|" << mat(0, 0) <<" " <<mat(0, 1) <<" " <<mat(0, 2) << "|" << std::endl;
	out<< "|" << mat(1, 0) <<" " <<mat(1, 1) <<" " <<mat(1, 2) << "|" << std::endl;
	out<< "|" << mat(2, 0) <<" " <<mat(2, 1) <<" " <<mat(2, 2) << "|" << std::endl;

	return out;
}

Matrix3::Matrix3(void)
{
	for (int i = 0; i < 9; i++)
	{
		m[i] = 0.0f;
	}
}

Matrix3::Matrix3(
	float m00, float m01, float m02,
	float m10, float m11, float m12,
	float m20, float m21, float m22)
{
	this->SetM(0, 0, m00); this->SetM(0, 1, m01); this->SetM(0, 2, m02); 
	this->SetM(1, 0, m10); this->SetM(1, 1, m11); this->SetM(1, 2, m12); 
	this->SetM(2, 0, m20); this->SetM(2, 1, m21); this->SetM(2, 2, m22); 
}

Matrix3::Matrix3(const Matrix3& m)
{
	Copy(m);
}

Matrix3::~Matrix3(void)
{
}

void Matrix3::SetM(int l, int c, float value)
{
	m[l * 3 + c] = value;
}

bool Matrix3::operator==(const Matrix3& that) const
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (that(i, j) != (*this)(i, j))
			{
				return false;
			}
		}
	}

	return true;
}

Matrix3 Matrix3::operator*= (const Matrix3& b)
{
	Matrix3(*this) = Matrix3(*this) * b;
	return Matrix3(*this);
}

const Matrix3 Matrix3::operator* (const Matrix3& rhs) const
{
	return Matrix3(
		m[0] * rhs(0, 0) + m[1] * rhs(1, 0) + m[2] * rhs(2, 0),
		m[0] * rhs(0, 1) + m[1] * rhs(1, 1) + m[2] * rhs(2, 1),
		m[0] * rhs(0, 2) + m[1] * rhs(1, 2) + m[2] * rhs(2, 2),

		m[3] * rhs(0, 0) + m[4] * rhs(1, 0) + m[5] * rhs(2, 0),
		m[3] * rhs(0, 1) + m[4] * rhs(1, 1) + m[5] * rhs(2, 1),
		m[3] * rhs(0, 2) + m[4] * rhs(1, 2) + m[5] * rhs(2, 2),

		m[6] * rhs(0, 0) + m[7] * rhs(1, 0) + m[8] * rhs(2, 0),
		m[6] * rhs(0, 1) + m[7] * rhs(1, 1) + m[8] * rhs(2, 1),
		m[6] * rhs(0, 2) + m[7] * rhs(1, 2) + m[8] * rhs(2, 2));
}
		

const Vector3 Matrix3::operator* (const Vector3& other) const
{
	return Vector3(
		m[0] * other.GetX() + m[1] * other.GetY() + m[2] * other.GetZ(),
		m[3] * other.GetX() + m[4] * other.GetY() + m[5] * other.GetZ(),
		m[6] * other.GetX() + m[7] * other.GetY() + m[8] * other.GetZ());
}

Matrix3& Matrix3::operator= (const Matrix3& rhs)
{
	if (this != &rhs)
	{
		Copy(rhs);
	}
	return *this;
}


float Matrix3::operator()(int line, int column) const
{
	return m[line * 3 + column];
}

void Matrix3::Copy(const Matrix3& mat)
{
	for (int i = 0; i < 9; i++)
	{
		m[i] = mat.m[i];
	}
}

		
Matrix3 Matrix3::Matrix3Scale(const Vector3& scale)
{
	return Matrix3(
		scale.GetX(), 0.0f, 0.0f,
		0.0f, scale.GetY(), 0.0f,
		0.0f, 0.0f, scale.GetZ());
}

Matrix3 Matrix3::Matrix3Scale(float scale)
{
	return Matrix3(
		scale, 0.0f, 0.0f,
		0.0f, scale, 0.0f,
		0.0f, 0.0f, scale);
}

Matrix3 Matrix3::Matrix3Inverse(const Matrix3& that)
{
	Matrix3* result = new Matrix3();

	float determinant = +that(0,0)*(that(1,1)*that(2,2)-that(2,1)*that(1,2))
                        -that(0,1)*(that(1,0)*that(2,2)-that(1,2)*that(2,0))
                        +that(0,2)*(that(1,0)*that(2,1)-that(1,1)*that(2,0));

	if (!determinant)
	{
		std::cout<<"Determinant 0"<<std::endl;
	}
	float invdet = 1.0f / determinant;

	result->SetM(0,0,  (that(1,1)*that(2,2)-that(2,1)*that(1,2))*invdet);
	result->SetM(1,0, -(that(0,1)*that(2,2)-that(0,2)*that(2,1))*invdet);
	result->SetM(2,0,  (that(0,1)*that(1,2)-that(0,2)*that(1,1))*invdet);
	result->SetM(0,1, -(that(1,0)*that(2,2)-that(1,2)*that(2,0))*invdet);
	result->SetM(1,1,  (that(0,0)*that(2,2)-that(0,2)*that(2,0))*invdet);
	result->SetM(2,1, -(that(0,0)*that(1,2)-that(1,0)*that(0,2))*invdet);
	result->SetM(0,2,  (that(1,0)*that(2,1)-that(2,0)*that(1,1))*invdet);
	result->SetM(1,2, -(that(0,0)*that(2,1)-that(2,0)*that(0,1))*invdet);
	result->SetM(2,2,  (that(0,0)*that(1,1)-that(1,0)*that(0,1))*invdet);

	return Matrix3::MatrixTranspose(*result);
}

Matrix3 Matrix3::Matrix3CreateRotationX(float angle)
{
	float c = cos(angle);
	float s = sin(angle);

    return Matrix3(
		1.0f, 0.0f, 0.0f,
		0.0f,	 c,   -s,
		0.0f,    s,    c);
}

Matrix3 Matrix3::Matrix3CreateRotationY(float angle)
{
	float c = cos(angle);
	float s = sin(angle);

    return Matrix3(
		   c, 0.0f,    s,
		0.0f, 1.0f, 0.0f,
		  -s, 0.0f,	   c);
}

Matrix3 Matrix3::Matrix3CreateRotationZ(float angle)
{
	float c = cos(angle);
	float s = sin(angle);

    return Matrix3(
		   c,   -s, 0.0f,
		   s,	 c, 0.0f,
		0.0f, 0.0f, 1.0f);
}

Matrix3 Matrix3::MatrixTranspose(const Matrix3& mat)
{
	Matrix3* transpose = new Matrix3;
	*transpose = mat;

	for (int i = 1; i < 3; i++)
	{
		for (int j = 0; j < i; j++)
		{			
			float temp = (*transpose)(i, j);
			transpose->SetM(i, j, (*transpose)(j, i));
			transpose->SetM(j, i, temp);
		}
	}

	return *transpose;
}