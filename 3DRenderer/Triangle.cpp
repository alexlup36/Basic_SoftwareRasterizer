#include "StdAfx.h"
#include "Triangle.h"

std::ostream& operator<< (std::ostream& out, const Triangle& triangle)
{
	out<< "Triangle vertex data: "<< std::endl;

	for (int i = 0; i < 3; i++)
	{	
		out<< "|" <<triangle.vertices[i].Position().GetX() << ", ";
		out<< triangle.vertices[i].Position().GetY() << ", ";
		out<< triangle.vertices[i].Position().GetZ() << "|" <<std::endl;
	}

	return out;
}

Triangle::Triangle()
{
	vertices = new Vertex[3];
	normals = new Vector3;
}

Triangle::Triangle(const Vector3& v1, const Vector3& v2, const Vector3& v3)
{
	vertices = new Vertex[3];
	normals = new Vector3;

	vertices[0].SetPosition(v1);
	vertices[1].SetPosition(v2);
	vertices[2].SetPosition(v3);

	SetQuantity(3);

	buildEdgeSet();
	updateNormal();

	_m.ka = Colour(255, 255, 0);
	_m.kd = Colour(255, 255, 0);
	_m.ks = Colour(255, 255, 255);
}

Triangle::Triangle(const Vertex& v1, const Vertex& v2, const Vertex& v3)
{
	vertices = new Vertex[3];
	normals = new Vector3;

	vertices[0] = v1;
	vertices[1] = v2;
	vertices[2] = v3;

	SetQuantity(3);

	buildEdgeSet();
	updateNormal();

	_m.ka = Colour(255, 255, 0);
	_m.kd = Colour(255, 255, 0);
	_m.ks = Colour(255, 255, 255);
}


Triangle::~Triangle(void)
{
}

void Triangle::buildEdgeSet()
{
	edges.insert(std::pair<int, int>(0, 1));
	edges.insert(std::pair<int, int>(1, 2));
	edges.insert(std::pair<int, int>(2, 0));
}

Vector3 Triangle::getNormal()
{
	return Vector3::Normalize(Vector3::Vec3Cross(
		transfCoordinates[1] - transfCoordinates[0],
		transfCoordinates[2] - transfCoordinates[1]));
}

void Triangle::updateNormal()
{
	normals[0] = Vector3::Normalize(Vector3::Vec3Cross(
		transfCoordinates[1] - transfCoordinates[0],
		transfCoordinates[2] - transfCoordinates[1]));
}

Vector3 Triangle::origNormal()
{
	return Vector3::Normalize(Vector3::Vec3Cross(
		vertices[1].Position() - vertices[0].Position(),
		vertices[2].Position() - vertices[1].Position()));
}

material Triangle::Material()
{
	return this->_m;
}

void Triangle::draw(Rasterizer* raster, DWORD c)
{
	// draw tri from trans coord
	raster->drawLineB(transfCoordinates[0], transfCoordinates[1], c);
	raster->drawLineB(transfCoordinates[1], transfCoordinates[2], c);
	raster->drawLineB(transfCoordinates[2], transfCoordinates[0], c);
}

// Transform triagle coordinates based on the transformation matrix passed as parameter
void Triangle::transform(const Matrix4& transformation)
{
	transfCoordinates[0] = this->vertices[0].Position().Transform(transformation);
	transfCoordinates[1] = this->vertices[1].Position().Transform(transformation);
	transfCoordinates[2] = this->vertices[2].Position().Transform(transformation);
}

// Transform triagle coordinates and vertices normals 
//based on the transformation matrix passed as parameter
void Triangle::transformPosNormal(const Matrix4& transformation)
{
	transfCoordinates[0] = this->vertices[0].Position().Transform(transformation);
	transfCoordinates[1] = this->vertices[1].Position().Transform(transformation);
	transfCoordinates[2] = this->vertices[2].Position().Transform(transformation);

	vertices[0].TransformedNormal = Vector3::Normalize(this->vertices[0].Normal().Transform(transformation));
	vertices[1].TransformedNormal = Vector3::Normalize(this->vertices[1].Normal().Transform(transformation));
	vertices[2].TransformedNormal = Vector3::Normalize(this->vertices[2].Normal().Transform(transformation));
}
