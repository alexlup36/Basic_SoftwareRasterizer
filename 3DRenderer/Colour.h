#pragma once
#include "Vector3.h"


class Colour : public Vector3
{
public:
	Colour(void);
	Colour(float x, float y, float z);
	~Colour(void);
	const Vector3 operator+(const Colour &other) const;
	const Vector3 operator*(const Colour& other) const;
};

