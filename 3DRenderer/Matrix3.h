#pragma once
#include "Vector3.h"
#include <iostream>

class Vector3;

class Matrix3
{
	friend std::ostream& operator<< (std::ostream& out, const Matrix3& mat);

	public:
		Matrix3(void);
		Matrix3(
			float m00, float m01, float m02,
			float m10, float m11, float m12,
			float m20, float m21, float m22);
		Matrix3(const Matrix3&);
		~Matrix3();

		void SetM(int, int, float);

		bool operator==(const Matrix3& that) const;
		Matrix3& operator= (const Matrix3& rhs);
		Matrix3 operator*= (const Matrix3& b);
		const Matrix3 operator* (const Matrix3& other) const;
		const Vector3 operator* (const Vector3& other) const;

		float operator()(int line, int column) const;

		static Matrix3 Identity;

	private:
		float m[9];

		void Copy(const Matrix3& m);

	public:
		static Matrix3 Matrix3CreateRotationX(float angle);
		static Matrix3 Matrix3CreateRotationY(float angle);
		static Matrix3 Matrix3CreateRotationZ(float angle);

		static Matrix3 MatrixTranspose(const Matrix3& mat);
		static Matrix3 Matrix3Scale(const Vector3& scale);
		static Matrix3 Matrix3Scale(float scale);
		static Matrix3 Matrix3Inverse(const Matrix3& that);
};