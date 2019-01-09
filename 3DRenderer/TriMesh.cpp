#include "StdAfx.h"
#include "TriMesh.h"


TriMesh::TriMesh(Vertex* vertices, int noOfVertices, unsigned int* indices, int noOfIndices)
{
	this->vertices = new Vertex[noOfVertices];
	this->indices = new unsigned int[noOfIndices];

	_noOfVertices = noOfVertices;

	for (int i = 0; i < noOfVertices; i++)
	{
		this->vertices[i] = vertices[i];
	}

	for (int i = 0; i < noOfIndices; i++)
	{
		this->indices[i] = indices[i];
	}

	vertexQuantity		= noOfVertices;
	indexQuantity		= noOfIndices;
	triangleQuantity	= noOfIndices / 3;

	buildEdgeSet();

	this->triangleList = new Triangle[triangleQuantity];
	bulidTriangleList();

	activeTriangles = 0;
}


TriMesh::~TriMesh(void)
{
}

int TriMesh::GetTriangleQuantity()
{
	return triangleQuantity;
}

void TriMesh::buildEdgeSet()
{
	for (int i = 0; i < indexQuantity; i+=3)
	{
		edges.insert(std::pair<int, int>(indices[i] - 1, indices[i + 1] - 1));
		edges.insert(std::pair<int, int>(indices[i + 1] - 1, indices[i + 2] - 1));
		edges.insert(std::pair<int, int>(indices[i] - 1, indices[i + 2] - 1));
	}
}

void TriMesh::bulidTriangleList()
{
	triangleList = new Triangle[triangleQuantity];

	for (int i = 0; i < indexQuantity; i+=3)
	{
		triangleList[(int)(i / 3)] = Triangle(vertices[indices[i] - 1], vertices[indices[i + 1] - 1], vertices[indices[i + 2] - 1]);

		// vertex adjacency
		vertexAdjacency.insert(std::pair<int, Triangle>(indices[i] - 1, triangleList[(int)(i / 3)]));
		vertexAdjacency.insert(std::pair<int, Triangle>(indices[i + 1] - 1, triangleList[(int)(i / 3)]));
		vertexAdjacency.insert(std::pair<int, Triangle>(indices[i + 2] - 1, triangleList[(int)(i / 3)]));
	}

	// Calculate normal for each vertex
	std::pair<std::multimap<int, Triangle>::iterator, std::multimap<int, Triangle>::iterator> ppp;

	for (int i = 0; i < vertexQuantity; i++)
	{
		ppp = vertexAdjacency.equal_range(i);
		Vector3 tempNormal = Vector3::Zero();
		SHORT count = 0;

		for (std::multimap<int, Triangle>::iterator it = ppp.first; it!=ppp.second; it++)
		{
			count++;
			tempNormal += (*it).second.origNormal();
		}

		tempNormal /= count;
		vertices[i].updateNormal(Vector3::Normalize(tempNormal));
	}

	for (int i = 0; i < indexQuantity; i+=3)
	{
		triangleList[(int)(i / 3)] = Triangle(vertices[indices[i] - 1], vertices[indices[i + 1] - 1], vertices[indices[i + 2] - 1]);
	}
}

void TriMesh::SetWorld(const Matrix4& transformation)
{
	this->_world = transformation;
}
	
void TriMesh::SetView(const Matrix4& transformation)
{
	this->_view = transformation;
}
	
void TriMesh::SetProjection(const Matrix4& transformation)
{
	this->_projection = transformation;
}

void TriMesh::transform(const Matrix4& transformationMatrix)
{
	for (unsigned int i = 0; i < _noOfVertices; i++)
	{
		Vector4 aux = this->vertices[i].Position().ToVector4();
		Vector4 temp = transformationMatrix * aux;

		this->vertices[i].SetPosition(Vector3(temp.GetX(), temp.GetY(), temp.GetZ()));
	}
}

void TriMesh::SetTransformation(const Matrix4& transformation)
{
	this->_transformation = transformation;
}

void TriMesh::drawWireFrameBackFaceCulling(Rasterizer* raster, Vector3& view, DWORD c)
{
	activeTriangles = 0;

	// wireframe rendering based on triangle list
	for (int i = 0; i < triangleQuantity; i++)
	{
		triangleList[i].transform(_transformation);
		if (Vector3::Vec3Dot(view, triangleList[i].getNormal()) < 0)
		{
			triangleList[i].draw(raster, c);

			activeTriangles++;
		}
	}
}

void TriMesh::drawWireFrameNoBackFaceCulling(Rasterizer* raster, DWORD c)
{
	// wireframe rendering based on edge list - no duplicate edges
	for (std::set<std::pair<int, int>>::iterator i = edges.begin(); i != edges.end(); i++)
	{
		std::pair<int, int> temp = *i;
		
		raster->drawLineB(vertices[i->first].Position().Transform(_transformation),
			vertices[i->second].Position().Transform(_transformation), c);
	}
}

void TriMesh::drawFlatShadedOneColor(Rasterizer* raster, Vector3& view, Vector3& c)
{
	activeTriangles = 0;

	for (int i = 0; i < triangleQuantity; i++)
	{
		triangleList[i].transform(_transformation);
		if (Vector3::Vec3Dot(view, triangleList[i].getNormal()) < 0) // Backface culling
		{
			raster->Draw_Triangle(triangleList[i].transfCoordinates[0].GetX(),
				triangleList[i].transfCoordinates[0].GetY(),
				triangleList[i].transfCoordinates[1].GetX(),
				triangleList[i].transfCoordinates[1].GetY(),
				triangleList[i].transfCoordinates[2].GetX(),
				triangleList[i].transfCoordinates[2].GetY(), c, c, c);
			
			activeTriangles++;
		}
	}
}

void TriMesh::drawFlatShadedRandomColors(Rasterizer* raster, Vector3& view, Vector3& c)
{
	activeTriangles = 0;

	for (int i = 0; i < triangleQuantity; i++)
	{
		triangleList[i].transform(_transformation);
		if (Vector3::Vec3Dot(view, triangleList[i].getNormal()) < 0) // Backface culling
		{
			Vector3 c1 = Vector3((float)(rand() % 255), (float)(rand() % 255), (float)(rand() % 255));
			Vector3 c2 = Vector3((float)(rand() % 255), (float)(rand() % 255), (float)(rand() % 255));
			Vector3 c3 = Vector3((float)(rand() % 255), (float)(rand() % 255), (float)(rand() % 255));

			raster->Draw_Triangle(triangleList[i].transfCoordinates[0].GetX(),
				triangleList[i].transfCoordinates[0].GetY(),
				triangleList[i].transfCoordinates[1].GetX(),
				triangleList[i].transfCoordinates[1].GetY(),
				triangleList[i].transfCoordinates[2].GetX(),
				triangleList[i].transfCoordinates[2].GetY(), c1, c2, c3);
			
			activeTriangles++;
		}
	}
}

void TriMesh::drawFlatShadedLight(Rasterizer* raster, Vector3& view)
{
	activeTriangles = 0;

	for (int i = 0; i < triangleQuantity; i++)
	{
		triangleList[i].transform(_world);
		triangleList[i].updateNormal();
		triangleList[i].transform(_transformation);

		if (Vector3::Vec3Dot(view, triangleList[i].getNormal()) < 0) // Backface culling
		{
			raster->scanFillPolyLight(triangleList[i], view);

			activeTriangles++;
		}
	}
}

void TriMesh::drawPerVertexShading(Rasterizer* raster, Vector3& view)
{
	activeTriangles = 0;

	for (int i = 0; i < triangleQuantity; i++)
	{
		triangleList[i].transformPosNormal(_transformation);

		if (Vector3::Vec3Dot(view, triangleList[i].getNormal()) < 0) // Backface culling
		{
			raster->scanFillVertexLight(triangleList[i], view);
			activeTriangles++;
		}
	}
}
