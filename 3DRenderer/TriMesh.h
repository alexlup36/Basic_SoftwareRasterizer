#pragma once
#include "Triangle.h"

class Triangle;
class Rasterizer;

class TriMesh : public Geometry
{
public:
	TriMesh(Vertex* vertices, int noOfVertices, unsigned int* indices, int noOfIndices);
	virtual ~TriMesh(void);

	int vertexQuantity;
	int indexQuantity;
	int triangleQuantity;

	Triangle* triangleList;
	std::set<std::pair<int, int>> edges;
	void transform(const Matrix4& transformationMatrix);
	void SetTransformation(const Matrix4& transformation);
	void SetWorld(const Matrix4& transformation);
	void SetView(const Matrix4& transformation);
	void SetProjection(const Matrix4& transformation);

	int GetTriangleQuantity();

	// Mesh drawing methods
	void drawWireFrameNoBackFaceCulling(Rasterizer* raster, DWORD c);
	void drawWireFrameBackFaceCulling(Rasterizer* raster, Vector3& view, DWORD c);
	void drawFlatShadedOneColor(Rasterizer* raster, Vector3& view, Vector3& c);
	void drawFlatShadedRandomColors(Rasterizer* raster, Vector3& view, Vector3& c);
	void drawFlatShadedLight(Rasterizer* raster, Vector3& view);
	void drawPerVertexShading(Rasterizer* raster, Vector3& view);

	int activeTriangles;

private:
	void buildEdgeSet();
	void bulidTriangleList();

	Matrix4 _transformation;
	Matrix4 _world;
	Matrix4 _view;
	Matrix4 _projection;

	std::multimap<int, Triangle> vertexAdjacency;
	unsigned int _noOfVertices;
};

