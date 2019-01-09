#pragma once
#include "ScreenBuffer.h"
#include "Vector3.h"
#include "Matrix3.h"
#include <map>

class Vertex
{
public:
	Vertex(void);
	Vertex(const Vector3& other);
	Vertex(const Vector3& other, const Vector3& color);
	Vertex(const Vector3& other, const Vector3& color, const Vector3& normal);
	~Vertex();

	Vector3	TransformedNormal;

	Vector3 Position();
	Vector3 Color();
	Vector3 Normal();
	inline void SetPosition(const Vector3& newPosition);
	void SetColor(Vector3& otherColor);
	Vector3 Transform(const Matrix3& transformationMatrix);
	void updateNormal(Vector3 other);
	
private:
	Vector3		 _position;
	Vector3		 _normal;
	Vector3		 _color;
};

