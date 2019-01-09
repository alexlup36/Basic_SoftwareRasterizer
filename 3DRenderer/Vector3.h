#pragma once
#include <string>
#include "Vector4.h"

class Matrix3;
class Matrix4;
class Vector4;

class Vector3
{
	friend std::ostream& operator<< (std::ostream &out, const Vector3& v);
	
	public:
		// Constructors and destructor
		Vector3(void);
		Vector3(float x, float y, float z);
		~Vector3(void);

		// Accessors and mutators
		inline float GetX(void) const;
		inline void SetX(float x);
		inline float GetY(void) const;
		inline void SetY(float y);
		inline float GetZ(void) const;
		inline void SetZ(float z);

		// Operations
		Vector3 operator= (const Vector3 &rhs);
		virtual Vector3 operator+(const Vector3 &other) const;
		Vector3 operator-(const Vector3 &other) const;
		const Vector3 operator*(float) const;
		const Vector3 operator/(float) const;
		virtual const Vector3 operator* (const Vector3& other) const;

		Vector3 operator +=(const Vector3& b);
		Vector3 operator -=(const Vector3& b);
		Vector3 operator *=(const Vector3& b);
		Vector3 operator /=(const Vector3& b);
		Vector3 operator *=(const float& b);
		Vector3 operator /=(const float& b);

		bool operator==(const Vector3& that) const;
		bool operator!=(const Vector3& that) const;

		Vector3 Transform(const Matrix4& mat);
		Vector4 ToVector4();

	protected:
		float _x;
		float _y;
		float _z;

		void Init(float x, float y, float z);
		void Copy(const Vector3& v);	

	public:
		static Vector3 Zero();

		static inline float Length(const Vector3& v);
		static float Vec3Dot(const Vector3& v1, const Vector3& v2);
		static Vector3 Vec3Cross(const Vector3& v1, const Vector3& v2);
		static Vector3 Normalize(const Vector3& input);
};

typedef Vector3 Point2;