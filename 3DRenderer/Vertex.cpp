#include "StdAfx.h"
#include "Vertex.h"

// Constructors
Vertex::Vertex(void)
	: _position(Vector3::Zero()) { }

Vertex::Vertex(const Vector3& other)
	: _position(other) { }

Vertex::Vertex(const Vector3& other, const Vector3& color)
	: _position(other), _color(color) { }

Vertex::Vertex(const Vector3& other, const Vector3& color, const Vector3& normal)
	: _position(other), _color(color), _normal(normal) { }

// Destructor
Vertex::~Vertex(void) {}


Vector3 Vertex::Position()
{
	return _position;
}

Vector3 Vertex::Color()
{
	return this->_color;
}

Vector3 Vertex::Normal()
{
	return this->_normal;
}

void Vertex::SetPosition(const Vector3& newPosition)
{
	this->_position = newPosition;
}


void Vertex::SetColor(Vector3& otherColor)
{
	this->_color = otherColor;
}

Vector3 Vertex::Transform(const Matrix3& transformationMatrix)
{
	Vector3 temp = transformationMatrix * this->Position();

	this->SetPosition(temp);
	return temp;
}

void Vertex::updateNormal(Vector3 other)
{
	this->_normal = other;
}