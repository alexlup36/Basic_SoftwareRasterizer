#pragma once
#include <string>
#include "Matrix4.h"
#include "Vector3.h"
#include "Util.h"

class Vector3;

class Vector4
{
	friend std::ostream& operator<< (std::ostream &out, const Vector4& v);

	public:
		// Constructors and destructor
		Vector4(void);
		Vector4(float x, float y, float z);
		Vector4(float x, float y, float z, float w);
		Vector4(const Vector4& v);
		~Vector4(void);

		// Accessors and mutators
		float GetX(void) const;
		void SetX(float x);
		float GetY(void) const;
		void SetY(float y);
		float GetZ(void) const;
		void SetZ(float z);
		float GetW(void) const;
		void SetW(float w);

		// Operations
		Vector4 operator= (const Vector4 &rhs);
		const Vector4 operator+(const Vector4 &other) const;
		const Vector4 operator-(const Vector4 &other) const;
		const Vector4 operator*(float) const;
		const Vector4 operator/(float) const;

		Vector4 operator +=(const Vector4& b);
		Vector4 operator -=(const Vector4& b);
		Vector4 operator *=(const Vector4& b);
		Vector4 operator /=(const Vector4& b);
		Vector4 operator *=(const float& b);
		Vector4 operator /=(const float& b);

		bool operator==(const Vector4& that) const;
		bool operator!=(const Vector4& that) const;

		Vector3 ToVector3();

	private:
		float _x;
		float _y;
		float _z;
		float _w;

		void Init(float x, float y, float z);
		void Copy(const Vector4& v);	

	public:
		static Vector4 VectorUp;
		static Vector4 VectorDown;
		static Vector4 VectorRight;
		static Vector4 VectorLeft;
		static Vector4 VectorForward;
		static Vector4 VectorBackward;

		static float Length(const Vector4& v);
		static float Dot(const Vector4& v1, const Vector4& v2);
		static const Vector4 Cross(const Vector4& v1, const Vector4& v2);
		static const Vector4 Normalize(const Vector4& input);
};


