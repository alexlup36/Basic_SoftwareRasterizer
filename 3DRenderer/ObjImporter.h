#pragma once
#include <vector>
#include "Vertex.h"

class ObjImporter
{
public:
	ObjImporter(void);
	~ObjImporter(void);

	static void getData(char* filename);

	static Vertex* Vertices();
	static unsigned int* Indices();
	static unsigned int NoOfVertices();
	static unsigned int NoOfIndices();

private:
	static std::vector<Vertex> _vertices;
	static std::vector<unsigned int> _indices;

	char* filename;
	static unsigned int noOfVertices;
	static unsigned int noOfIndices;
};

