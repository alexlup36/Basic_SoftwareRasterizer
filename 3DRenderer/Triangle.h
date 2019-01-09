#pragma once
#include <list>
#include <set>
#include "Geometry.h"
#include "Rasterizer.h"
#include "Light.h"

#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#include <hash_map>

class Rasterizer;

class Triangle : public Geometry
{
public:

	friend std::ostream& operator<< (std::ostream& out, const Triangle& triangle);

	Triangle();
	Triangle(const Vector3& v1, const Vector3& v2, const Vector3& v3);
	Triangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);
	virtual ~Triangle(void);

	std::set<std::pair<int, int>> edges;
	Vector3 transfCoordinates[3];
	std::hash_map<int, std::pair<int, int>> lookUpTable;

	void draw(Rasterizer* raster, DWORD c);

	Vector3 getNormal();
	void updateNormal();
	Vector3 origNormal();

	void transform(const Matrix4& transformation);
	void transformPosNormal(const Matrix4& transformation);
	
	material Material();

private:
	void buildEdgeSet();
	material _m;
};

