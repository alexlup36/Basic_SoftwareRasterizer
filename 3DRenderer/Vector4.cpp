#include "StdAfx.h"
#include "Vector4.h"

std::ostream& operator<<(std::ostream& out, const Vector4& v)
{
	out << "<" << v.GetX() << ", " << v.GetY() << ", " << v.GetZ() << ", " << v.GetW() << ">" << std::endl;

	return out;
}

// Constructors
Vector4::Vector4(void)
{
	Init(0.0f , 0.0f, 0.0f);
}

Vector4::Vector4(float x, float y, float z)
{
	Init(x, y, z);
	_w = 1.0f;
}

Vector4::Vector4(float x, float y, float z, float w)
{
	Init(x, y, z);
	_w = w;
}

Vector4::Vector4(const Vector4& v)
{
	Copy(v);
}

Vector4::~Vector4(void)
{
}


// Accessors and mutators
float Vector4::GetX(void) const
{
	return _x;
}
void Vector4::SetX(float x)
{
	_x = x;
}
float Vector4::GetY(void) const
{
	return _y;
}
void Vector4::SetY(float y)
{
	_y = y;
}
float Vector4::GetZ(void) const
{
	return _z;
}
void Vector4::SetZ(float z)
{
	_z = z;
}

float Vector4::GetW(void) const
{
	return _w;
}
void Vector4::SetW(float w)
{
	_w = w;
}


// Operator overloads
Vector4 Vector4::operator= (const Vector4 &rhs)
{
	if (this != &rhs)
	{
		Copy(rhs);
	}
	return Vector4(*this);
}

const Vector4 Vector4::operator+(const Vector4 &other) const
{
	return Vector4(*this) += other;
}

const Vector4 Vector4::operator-(const Vector4 &other) const
{
	return Vector4(*this) -= other;
}

const Vector4 Vector4::operator*(float scale) const
{
	return Vector4(*this) *= scale;
}

const Vector4 Vector4::operator/(float scale) const
{
	return Vector4(*this) /= scale;
}

Vector4 Vector4::operator +=(const Vector4& other)
{
	this->_x += other.GetX();
	this->_y += other.GetY();
	this->_z += other.GetZ();

	return Vector4(*this);
}

Vector4 Vector4::operator -=(const Vector4& other)
{
	this->_x -= other.GetX();
	this->_y -= other.GetY();
	this->_z -= other.GetZ();

	return Vector4(*this);
}

Vector4 Vector4::operator *=(const Vector4& other)
{
	this->_x *= other.GetX();
	this->_y *= other.GetY();
	this->_z *= other.GetZ();

	return Vector4(*this);
}

Vector4 Vector4::operator /=(const Vector4& other)
{
	this->_x /= other.GetX();
	this->_y /= other.GetY();
	this->_z /= other.GetZ();

	return Vector4(*this);
}

Vector4 Vector4::operator *=(const float& other)
{
	this->_x *= other;
	this->_y *= other;
	this->_z *= other;

	return Vector4(*this);
}

Vector4 Vector4::operator /=(const float& other)
{
	this->_x /= other;
	this->_y /= other;
	this->_z /= other;

	return Vector4(*this);
}

bool Vector4::operator==(const Vector4& that) const
{
	return (_x == that._x && _y == that._y && _z == that._z);
}
		
bool Vector4::operator!=(const Vector4& that) const
{
	return !(*this == that);
}

Vector3 Vector4::ToVector3()
{
	return Vector3(this->GetX(), this->GetY(), this->GetZ());
}

// Private methods
void Vector4::Init(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}

void Vector4::Copy(const Vector4& v)
{
	_x = v._x;
	_y = v._y;
	_z = v._z;
}


Vector4 Vector4::VectorUp		= Vector4(0.0f, 1.0f, 0.0f);
Vector4 Vector4::VectorDown		= Vector4(0.0f, -1.0f, 0.0f);
Vector4 Vector4::VectorRight	= Vector4(1.0f, 0.0f, 0.0f);
Vector4 Vector4::VectorLeft		= Vector4(-1.0f, 0.0f, 0.0f);
Vector4 Vector4::VectorForward	= Vector4(0.0f, 0.0f, 1.0f);
Vector4 Vector4::VectorBackward = Vector4(0.0f, 0.0f, -1.0f);


float Vector4::Length(const Vector4& v)
{
	return sqrt((float)(v.GetX() * v.GetX() + v.GetY() * v.GetY() + v.GetZ() * v.GetZ()));
}

const Vector4 Vector4::Normalize(const Vector4& input)
{
	return input / Length(input);
}

float Vector4::Dot(const Vector4& v1, const Vector4& v2)
{
	return v1.GetX() * v2.GetX() + v1.GetY() * v2.GetY() + v1.GetZ() * v2.GetZ();
}

const Vector4 Vector4::Cross(const Vector4& v1, const Vector4& v2)
{
	return Vector4(
		v1.GetY() * v2.GetZ() - v2.GetY() * v1.GetZ(),
		v2.GetX() * v1.GetZ() - v1.GetX() * v2.GetZ(),
		v1.GetX() * v2.GetY() - v1.GetY() * v2.GetX());
}