#include "StdAfx.h"
#include "Matrix4.h"

std::ostream& operator<< (std::ostream& out, const Matrix4& mat)
{
	out<< "|" << mat(0, 0) <<" " <<mat(0, 1) <<" " <<mat(0, 2) << " " <<mat(0, 3) << "|" << std::endl;
	out<< "|" << mat(1, 0) <<" " <<mat(1, 1) <<" " <<mat(1, 2) << " " <<mat(1, 3) << "|" << std::endl;
	out<< "|" << mat(2, 0) <<" " <<mat(2, 1) <<" " <<mat(2, 2) << " " <<mat(2, 3) << "|" << std::endl;
	out<< "|" << mat(3, 0) <<" " <<mat(3, 1) <<" " <<mat(3, 2) << " " <<mat(3, 3) << "|" << std::endl;

	return out;
}

Matrix4 Matrix4::Identity = Matrix4(
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f);

Matrix4::Matrix4(void)
{
	for (int i = 0; i < 16; i++)
	{
		m[i] = 0.0f;
	}
}

Matrix4::Matrix4(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33)
{
	Matrix4* temp = this;
	temp->m[0] = m00; temp->m[1] = m01; temp->m[2] = m02; temp->m[3] = m03;
	temp->m[4] = m10; temp->m[5] = m11; temp->m[6] = m12; temp->m[7] = m13;
	temp->m[8] = m20; temp->m[9] = m21; temp->m[10] = m22; temp->m[11] = m23;
	temp->m[12] = m30; temp->m[13] = m31; temp->m[14] = m32; temp->m[15] = m33;
}

Matrix4::~Matrix4(void)
{
}

void Matrix4::SetM(int l, int c, float value)
{
	m[l * 4 + c] = value;
}

Matrix4 Matrix4::operator*= (const Matrix4& b)
{
	Matrix4(*this) = Matrix4(*this) * b;
	return Matrix4(*this);
}

const Matrix4 Matrix4::operator* (const Matrix4& rhs) const
{
	return Matrix4(
		m[0] * rhs(0, 0) + m[1] * rhs(1, 0) + m[2] * rhs(2, 0) + m[3] * rhs(3, 0),
		m[0] * rhs(0, 1) + m[1] * rhs(1, 1) + m[2] * rhs(2, 1) + m[3] * rhs(3, 1),
		m[0] * rhs(0, 2) + m[1] * rhs(1, 2) + m[2] * rhs(2, 2) + m[3] * rhs(3, 2),
		m[0] * rhs(0, 3) + m[1] * rhs(1, 3) + m[2] * rhs(2, 3) + m[3] * rhs(3, 3),

		m[4] * rhs(0, 0) + m[5] * rhs(1, 0) + m[6] * rhs(2, 0) + m[7] * rhs(3, 0),
		m[4] * rhs(0, 1) + m[5] * rhs(1, 1) + m[6] * rhs(2, 1) + m[7] * rhs(3, 1),
		m[4] * rhs(0, 2) + m[5] * rhs(1, 2) + m[6] * rhs(2, 2) + m[7] * rhs(3, 2),
		m[4] * rhs(0, 3) + m[5] * rhs(1, 3) + m[6] * rhs(2, 3) + m[7] * rhs(3, 3),

		m[8] * rhs(0, 0) + m[9] * rhs(1, 0) + m[10] * rhs(2, 0) + m[11] * rhs(3, 0),
		m[8] * rhs(0, 1) + m[9] * rhs(1, 1) + m[10] * rhs(2, 1) + m[11] * rhs(3, 1),
		m[8] * rhs(0, 2) + m[9] * rhs(1, 2) + m[10] * rhs(2, 2) + m[11] * rhs(3, 2),
		m[8] * rhs(0, 3) + m[9] * rhs(1, 3) + m[10] * rhs(2, 3) + m[11] * rhs(3, 3),

		m[12] * rhs(0, 0) + m[13] * rhs(1, 0) + m[14] * rhs(2, 0) + m[15] * rhs(3, 0),
		m[12] * rhs(0, 1) + m[13] * rhs(1, 1) + m[14] * rhs(2, 1) + m[15] * rhs(3, 1),
		m[12] * rhs(0, 2) + m[13] * rhs(1, 2) + m[14] * rhs(2, 2) + m[15] * rhs(3, 2),
		m[12] * rhs(0, 3) + m[13] * rhs(1, 3) + m[14] * rhs(2, 3) + m[15] * rhs(3, 3));
}
		

const Vector4 Matrix4::operator* (const Vector4& other) const
{
	return Vector4(
		m[0] * other.GetX() + m[1] * other.GetY() + m[2] * other.GetZ() + m[3],
		m[4] * other.GetX() + m[5] * other.GetY() + m[6] * other.GetZ() + m[7],
		m[8] * other.GetX() + m[9] * other.GetY() + m[10] * other.GetZ() + m[11],
		m[12] * other.GetX() + m[13] * other.GetY() + m[14] * other.GetZ() + m[15]);
}

Matrix4& Matrix4::operator= (const Matrix4& rhs)
{
	if (this != &rhs)
	{
		Copy(rhs);
	}
	return *this;
}


float Matrix4::operator()(int line, int column) const
{
	return m[line * 4 + column];
}

void Matrix4::Copy(const Matrix4& mat)
{
	for (int i = 0; i < 16; i++)
	{
		m[i] = mat.m[i];
	}
}

Matrix4 Matrix4::Matrix4CreateRotationX(float angle)
{
	float degree = angle*Util::PI/180;

	float c = cosf(degree);
	float s = sinf(degree);

    return Matrix4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f,	 c,   -s, 0.0f,
		0.0f,	 s,	   c, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 Matrix4::Matrix4CreateRotationY(float angle)
{
	float degree = angle*Util::PI/180;

	float c = cosf(degree);
	float s = sinf(degree);

    return Matrix4(
		   c, 0.0f,    s, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		  -s, 0.0f,	   c, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 Matrix4::Matrix4CreateRotationZ(float angle)
{
	float degree = angle*Util::PI/180;

	float c = cosf(degree);
	float s = sinf(degree);

    return Matrix4(
		   c,   -s, 0.0f, 0.0f,
		   s,	 c, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 Matrix4::Matrix4Translation(const Vector4& v)
{
	return Matrix4Translation(v.GetX(), v.GetY(), v.GetZ());
}

Matrix4 Matrix4::Matrix4Translation(float x, float y, float z)
{
	return Matrix4(
		1.0f, 0.0f, 0.0f, x,
		0.0f, 1.0f, 0.0f, y, 
		0.0f, 0.0f, 1.0f, z,
		0.0f, 0.0f, 0.0f, 1.0f);
}
		
Matrix4 Matrix4::Matrix4Scale(const Vector4& scale)
{
	return Matrix4(
		scale.GetX(),		  0.0f,         0.0f, 0.0f,
				0.0f, scale.GetY(),         0.0f, 0.0f,
				0.0f,         0.0f, scale.GetZ(), 0.0f,
				0.0f,         0.0f,		    0.0f, 1.0f);
}

Matrix4 Matrix4::Matrix4Scale(float scale)
{
	return Matrix4(
		scale,  0.0f,  0.0f, 0.0f,
		 0.0f, scale,  0.0f, 0.0f,
		 0.0f,  0.0f, scale, 0.0f,
		 0.0f,  0.0f,  0.0f, 1.0f);
}

Matrix4 Matrix4::MatrixTranspose(const Matrix4& mat)
{
	Matrix4* transpose = new Matrix4;
	*transpose = mat;

	for (int i = 1; i < 4; i++)
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

Vector4 Matrix4::MATRIX_COL4(const Matrix4& other, int c)
{
	return Vector4(
		other(0, c), other(1, c), other(2, c), other(3, c));
}

Vector4 Matrix4::MATRIX_ROW4(const Matrix4& other, int r)
{
	return Vector4(
		other(r, 0), other(r, 1), other(r, 2), other(r, 3));
}

Matrix4 Matrix4::MatrixInverse(const Matrix4& mat)
{
	Vector4 aux = MATRIX_COL4(mat, 3);

	return Matrix4(
		mat(0, 0), mat(1, 0), mat(2, 0), -Vector4::Dot(MATRIX_COL4(mat, 0), aux),
		mat(0, 1), mat(1, 1), mat(2, 1), -Vector4::Dot(MATRIX_COL4(mat, 1), aux),
		mat(0, 2), mat(1, 2), mat(2, 2), -Vector4::Dot(MATRIX_COL4(mat, 2), aux),
		0.0f, 0.0f, 0.0f, 1.0);
}