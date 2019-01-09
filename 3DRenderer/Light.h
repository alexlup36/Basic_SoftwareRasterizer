#pragma once
#include "Vector3.h"
#include "Colour.h"

struct material
{
	Colour ka;
	Colour kd;
	Colour ks;
};

class Light
{
public:
	Light(void);
	Light(Vector3& pos, Vector3& dir, material& mat, float specularity);
	~Light(void);
	material m;
	Vector3 position;
	Vector3 direction;
	float spec;
};


