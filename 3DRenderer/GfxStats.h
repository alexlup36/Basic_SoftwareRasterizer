#pragma once
#include <stdio.h>
#include <string>
#include "Rasterizer.h"

class GfxStats
{
public:
	GfxStats();
	~GfxStats();

	void addVertices(unsigned int n);
	void subVertices(unsigned int n);
	void addTriangles(unsigned int n);
	void subTriangles(unsigned int n);

	void setTriCount(unsigned int n);
	void setActiveTri(unsigned int n);
	void setVertexCount(unsigned int n);

	void update(float dt);
	void display(HDC hdc);

	int displayMode;

private:
	// Prevent copying
	GfxStats(const GfxStats& rhs);
	GfxStats& operator=(const GfxStats& rhs);
	
private:
	float mFPS;
	float mMilliSecPerFrame;
	unsigned int mNumTris;
	unsigned int mNumVertices;
	unsigned int mDisplayedTri;
};