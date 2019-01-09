#include "StdAfx.h"
#include "Colour.h"


Colour::Colour(void)
{
	_x = 0.0f;
	_y = 0.0f;
	_z = 0.0f;
}

Colour::Colour(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}


Colour::~Colour(void)
{
}


const Vector3 Colour::operator+(const Colour &other) const
{
	/*return Vector3(
		max(255, this->GetX() + other.GetX()),
		max(255, this->GetY() + other.GetY()),
		max(255, this->GetZ() + other.GetZ()));*/
	return Vector3(
		this->GetX() + other.GetX(),
		this->GetY() + other.GetY(),
		this->GetZ() + other.GetZ());
}
	
const Vector3 Colour::operator*(const Colour& other) const
{
	/*return Vector3(
		max(255, this->GetX() * other.GetX()),
		max(255, this->GetY() * other.GetY()),
		max(255, this->GetZ() * other.GetZ()));*/
	return Vector3(
		this->GetX() * other.GetX(),
		this->GetY() * other.GetY(),
		this->GetZ() * other.GetZ());
}