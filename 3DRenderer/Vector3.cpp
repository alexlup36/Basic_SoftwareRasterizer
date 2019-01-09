#include "StdAfx.h"
#include "Vector3.h"

std::ostream& operator<<(std::ostream& out, const Vector3& v)
{
	out << "<" << v.GetX() << ", " << v.GetY() << ", " << v.GetZ() << ">" << std::endl;

	return out;
}

// Constructors
Vector3::Vector3(void)
	: _x(0.0f), _y(0.0f), _z(0.0f) { }

Vector3::Vector3(float x, float y, float z)
	: _x(x), _y(y), _z(z) {}

Vector3::~Vector3(void)
{
}


// Accessors and mutators
float Vector3::GetX(void) const
{
	return _x;
}
void Vector3::SetX(float x)
{
	_x = x;
}
float Vector3::GetY(void) const
{
	return _y;
}
void Vector3::SetY(float y)
{
	_y = y;
}
float Vector3::GetZ(void) const
{
	return _z;
}
void Vector3::SetZ(float z)
{
	_z = z;
}


// Operator overloads
Vector3 Vector3::operator= (const Vector3 &rhs)
{
	if (this != &rhs)
	{
		// Only copy if we are not assigning to ourselves. 
		Copy(rhs);
	}
	return Vector3(*this);
}

Vector3 Vector3::operator+(const Vector3 &other) const
{
	return Vector3(
		this->GetX() + other.GetX(),
		this->GetY() + other.GetY(),
		this->GetZ() + other.GetZ());
}

Vector3 Vector3::operator-(const Vector3 &other) const
{
	return Vector3(*this) -= other;
}

const Vector3 Vector3::operator*(float scale) const
{
	return Vector3(*this) *= scale;
}

const Vector3 Vector3::operator/(float scale) const
{
	return Vector3(*this) /= scale;
}

const Vector3 Vector3::operator* (const Vector3& other) const
{
	return Vector3(
		this->GetX() * other.GetX(),
		this->GetY() * other.GetY(),
		this->GetZ() * other.GetZ());
}

Vector3 Vector3::operator +=(const Vector3& other)
{
	this->_x += other.GetX();
	this->_y += other.GetY();
	this->_z += other.GetZ();

	return Vector3(*this);
}

Vector3 Vector3::operator -=(const Vector3& other)
{
	this->_x -= other.GetX();
	this->_y -= other.GetY();
	this->_z -= other.GetZ();

	return Vector3(*this);
}

Vector3 Vector3::operator *=(const Vector3& other)
{
	this->_x *= other.GetX();
	this->_y *= other.GetY();
	this->_z *= other.GetZ();

	return Vector3(*this);
}

Vector3 Vector3::operator /=(const Vector3& other)
{
	this->_x /= other.GetX();
	this->_y /= other.GetY();
	this->_z /= other.GetZ();

	return Vector3(*this);
}

Vector3 Vector3::operator *=(const float& other)
{
	this->_x *= other;
	this->_y *= other;
	this->_z *= other;

	return Vector3(*this);
}

Vector3 Vector3::operator /=(const float& other)
{
	this->_x /= other;
	this->_y /= other;
	this->_z /= other;

	return Vector3(*this);
}

bool Vector3::operator==(const Vector3& that) const
{
	return (_x == that._x) && (_y == that._y) && (_z == that._z);
}
		
bool Vector3::operator!=(const Vector3& that) const
{
	return !(*this == that);
}

Vector3 Vector3::Transform(const Matrix4& mat)
{
	Vector4 temp = mat * Vector4(this->GetX(), this->GetY(), this->GetZ(), 1.0f);
	return temp.ToVector3();
}

Vector4 Vector3::ToVector4()
{
	return Vector4(this->GetX(), this->GetY(), this->GetZ(), 1.0f);
}

// Private methods
void Vector3::Init(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}

void Vector3::Copy(const Vector3& v)
{
	_x = v._x;
	_y = v._y;
	_z = v._z;
}

Vector3 Vector3::Zero()
{
	return Vector3(0.0f, 0.0f, 0.0f);
}

float Vector3::Length(const Vector3& v)
{
	return sqrt((float)(v.GetX() * v.GetX() + v.GetY() * v.GetY() + v.GetZ() * v.GetZ()));
}

Vector3 Vector3::Normalize(const Vector3& input)
{
	float length = Length(input);

	float x = input.GetX() / length;
	float y = input.GetY() / length;
	float z = input.GetZ() / length;

	return Vector3(x, y, z);
}

float Vector3::Vec3Dot(const Vector3& v1, const Vector3& v2)
{
	return v1.GetX() * v2.GetX() + v1.GetY() * v2.GetY() + v1.GetZ() * v2.GetZ();
}

Vector3 Vector3::Vec3Cross(const Vector3& v1, const Vector3& v2)
{
	return Vector3(
		v1.GetY() * v2.GetZ() - v2.GetY() * v1.GetZ(),
		v2.GetX() * v1.GetZ() - v1.GetX() * v2.GetZ(),
		v1.GetX() * v2.GetY() - v1.GetY() * v2.GetX());
}