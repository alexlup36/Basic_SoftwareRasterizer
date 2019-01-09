#pragma once
#include "Vector4.h"
#include <iostream>
#include <cmath>
#include "Util.h"

class Vector4;

class Matrix4
{
	friend std::ostream& operator<< (std::ostream& out, const Matrix4& mat);

	public:
		Matrix4(void);
		Matrix4(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33);
		~Matrix4();

		void SetM(int, int, float);

		Matrix4& operator= (const Matrix4& rhs);
		Matrix4 operator*= (const Matrix4& b);
		const Matrix4 operator* (const Matrix4& other) const;
		const Vector4 operator* (const Vector4& other) const;

		float operator()(int line, int column) const;

		static Matrix4 Identity;

	private:
		float m[16];

		void Copy(const Matrix4& m);

	public:
		static Matrix4 Matrix4CreateRotationX(float angle);
		static Matrix4 Matrix4CreateRotationY(float angle);
		static Matrix4 Matrix4CreateRotationZ(float angle);

		static Matrix4 Matrix4Translation(const Vector4& v);
		static Matrix4 Matrix4Translation(float x, float y, float z);

		static Matrix4 Matrix4Scale(const Vector4& scale);
		static Matrix4 Matrix4Scale(float scale);

		static Matrix4 MatrixTranspose(const Matrix4& mat);
		static Matrix4 MatrixInverse(const Matrix4& mat);

		static Vector4 MATRIX_COL4(const Matrix4& other, int c);
		static Vector4 MATRIX_ROW4(const Matrix4& other, int c);
};