#include "StdAfx.h"
#include "GfxStats.h"
#include <tchar.h>

GfxStats::GfxStats()
	:  mFPS(0.0f), mMilliSecPerFrame(0.0f), mNumTris(0), mNumVertices(0), mDisplayedTri(0), displayMode(1) {}

GfxStats::~GfxStats() {}

void GfxStats::addVertices(unsigned int n)
{
	mNumVertices += n;
}

void GfxStats::subVertices(unsigned int n)
{
	mNumVertices -= n;
}

void GfxStats::addTriangles(unsigned int n)
{
	mNumTris += n;
}

void GfxStats::subTriangles(unsigned int n)
{
	mNumTris -= n;
}

void GfxStats::setTriCount(unsigned int n)
{
	mNumTris = n;
}

void GfxStats::setVertexCount(unsigned int n)
{
	mNumVertices = n;
}

void GfxStats::setActiveTri(unsigned int n)
{
	mDisplayedTri = n;
}

void GfxStats::update(float dt)
{
	// Make static so that their values persist accross function calls.
	static float numFrames   = 0.0f;
	static float timeElapsed = 0.0f;

	// Increment the frame count.
	numFrames += 1.0f;

	// Accumulate how much time has passed.
	timeElapsed += dt;

	// Has one second passed?--we compute the frame statistics once 
	// per second.  Note that the time between frames can vary so 
	// these stats are averages over a second.
	if( timeElapsed >= 1.0f )
	{
		// Frames Per Second = numFrames / timeElapsed,
		// but timeElapsed approx. equals 1.0, so 
		// frames per second = numFrames.

		mFPS = numFrames;

		// Average time, in miliseconds, it took to render a single frame.
		mMilliSecPerFrame = 1000.0f / mFPS;

		// Reset time counter and frame count to prepare for computing
		// the average stats over the next second.
		timeElapsed = 0.0f;
		numFrames   = 0.0f;
	}
}

void GfxStats::display(HDC hdc)
{
	// Make static so memory is not allocated every frame.
	static char buffer[80];
	static COLORREF color = RGB(255, 255, 255);

	sprintf_s(buffer, "Frames Per Second = %.2f\n", mFPS);
	Rasterizer::drawText(hdc, buffer, 20, 20, color, std::strlen(buffer));
	
	sprintf_s(buffer, "Milliseconds Per Frame = %.4f\n", mMilliSecPerFrame);
	Rasterizer::drawText(hdc, buffer, 20, 40, color, std::strlen(buffer));
	
	sprintf_s(buffer, "Triangle Count = %d\n", mNumTris);
	Rasterizer::drawText(hdc, buffer, 20, 60, color, std::strlen(buffer));
	
	sprintf_s(buffer, "Triangles displayed = %d", mDisplayedTri);
	Rasterizer::drawText(hdc, buffer, 20, 80, color, std::strlen(buffer));

	sprintf_s(buffer, "Vertex Count = %d", mNumVertices);
	Rasterizer::drawText(hdc, buffer, 20, 100, color, std::strlen(buffer));

	// Display modes
	sprintf_s(buffer, "1 - Wireframe rendering - no backface culling");
	Rasterizer::drawText(hdc, buffer, 600, 20, color, std::strlen(buffer));

	sprintf_s(buffer, "2 - Wireframe rendering - backface culling");
	Rasterizer::drawText(hdc, buffer, 600, 40, color, std::strlen(buffer));

	sprintf_s(buffer, "3 - Import 2 3D models");
	Rasterizer::drawText(hdc, buffer, 600, 60, color, std::strlen(buffer));

	sprintf_s(buffer, "4 - One constant color rendering");
	Rasterizer::drawText(hdc, buffer, 600, 80, color, std::strlen(buffer));

	sprintf_s(buffer, "5 - Interpolated Shading - random colors");
	Rasterizer::drawText(hdc, buffer, 600, 100, color, std::strlen(buffer));

	sprintf_s(buffer, "6 - Flat shading - (1 ambient, 1 diffuse, 1 specular)");
	Rasterizer::drawText(hdc, buffer, 600, 120, color, std::strlen(buffer));

	sprintf_s(buffer, "7 - Gouraud Shading - (1 ambient, 1 diffuse, 1 specular)");
	Rasterizer::drawText(hdc, buffer, 600, 140, color, std::strlen(buffer));

	switch (displayMode)
	{
	case 1:
		sprintf_s(buffer, "Wireframe rendering - no backface culling");
		Rasterizer::drawText(hdc, buffer, 330, 620, color, std::strlen(buffer));
		break;
	case 2:
		sprintf_s(buffer, "Wireframe rendering - backface culling");
		Rasterizer::drawText(hdc, buffer, 330, 620, color, std::strlen(buffer));
		break;
	case 3:
		sprintf_s(buffer, "Import 2 3D models");
		Rasterizer::drawText(hdc, buffer, 330, 620, color, std::strlen(buffer));
		break;
	case 4:
		sprintf_s(buffer, "One constant color rendering");
		Rasterizer::drawText(hdc, buffer, 330, 620, color, std::strlen(buffer));
		break;
	case 5:
		sprintf_s(buffer, "Interpolated Shading - random colors");
		Rasterizer::drawText(hdc, buffer, 330, 620, color, std::strlen(buffer));
		break;
	case 6:
		sprintf_s(buffer, "Flat shading - (1 ambient, 1 diffuse, 1 specular)");
		Rasterizer::drawText(hdc, buffer, 330, 620, color, std::strlen(buffer));
		break;
	case 7:
		sprintf_s(buffer, "Gouraud Shading - (1 ambient, 1 diffuse, 1 specular)");
		Rasterizer::drawText(hdc, buffer, 330, 620, color, std::strlen(buffer));
		break;
	}
}