#include "StdAfx.h"
#include "ObjImporter.h"
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

std::vector<Vertex>ObjImporter::_vertices;
std::vector<unsigned int>ObjImporter:: _indices;

unsigned int ObjImporter::noOfVertices = 0;
unsigned int ObjImporter::noOfIndices = 0;

ObjImporter::ObjImporter(void)
{
}


ObjImporter::~ObjImporter(void)
{
	delete this->filename;
}


Vertex* ObjImporter::Vertices()
{
	std::vector<Vertex>::iterator it(_vertices.begin());
	return &(*it);
}
	
unsigned int* ObjImporter::Indices()
{
	std::vector<unsigned int>::iterator it(_indices.begin());
	return &(*it);
}

unsigned int ObjImporter::NoOfVertices()
{
	return noOfVertices;
}
	
unsigned int ObjImporter::NoOfIndices()
{
	return noOfIndices;
}

void ObjImporter::getData(char* filename)
{
	_vertices.clear();
	_indices.clear();

	noOfIndices = 0;
	noOfVertices = 0;

	std::string buffer;
	char op;
	float x, y, z;

	std::ifstream infile;
	infile.open(filename, std::ifstream::in);

	while (!infile.eof())
	{
		std::getline(infile, buffer);

		std::istringstream iss(buffer, std::istringstream::in);
		iss>>op;
		switch (op)
		{
			case '#':
				
			break;
			case 'v':
				iss>>x>>y>>z;
				_vertices.push_back(Vertex(Vector3(x, y, z), Vector3(255, 0, 0)));
				noOfVertices++;
			break;
			case 'f':
				iss>>x>>y>>z;
				_indices.push_back((unsigned int)x);
				_indices.push_back((unsigned int)y);
				_indices.push_back((unsigned int)z);
				noOfIndices+=3;
			break;
		}
		op = ' ';
	}

	infile.close();
}