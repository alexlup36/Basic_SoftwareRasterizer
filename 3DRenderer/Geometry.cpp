#include "StdAfx.h"
#include "Geometry.h"

Geometry::Geometry() {}

Geometry::Geometry(Vertex* vertices, int quantity)
{
	for (int i = 0; i < quantity; i++)
	{
		this->vertices[i] = vertices[i];
	}
}


Geometry::~Geometry(void)
{
}


void Geometry::SetQuantity(int quantity)
{
	this->quantity = quantity;
}
	
int Geometry::GetQuantity()
{
	return quantity;
}

void Geometry::updateNormals() 
{

}
