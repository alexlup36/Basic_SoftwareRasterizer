#pragma once
#include "Vertex.h"

class Geometry
{
public:
	Geometry(Vertex* vertices, int quantity);
	~Geometry(void);

	Vertex*			vertices;
	unsigned int*	indices;
	Vector3*		normals;

	int quantity;
protected:
	Geometry(void);

	virtual void updateNormals();

public:
	enum GeometryType
	{
		GT_POLYPOINT,
		GT_POLYLINE,
		GT_TRIMESH
	};
	void SetQuantity(int quantity);
	int GetQuantity();

	int GeometryType;

};

