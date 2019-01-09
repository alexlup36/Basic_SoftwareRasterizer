#pragma once
#include "Triangle.h"
#include "TriMesh.h"
#include "ObjImporter.h"
#include "3DRenderer.h"
#include "ScreenBuffer.h"
#include "Util.h"
#include <map>
#include "Light.h"
#include <list>
#include "Colour.h"

class Triangle;

class Rasterizer
{
public:
	Rasterizer(UINT16 screenWidth, UINT16 screenHeight);
	virtual ~Rasterizer(void);

	static void drawText(HDC hdc, char* text, int x, int y, COLORREF color, size_t len);
	void drawLineB(float x1, float y1, float x2, float y2, DWORD c);
	void drawLineB(const Vector3& v1, const Vector3& v2, DWORD& c);
	void drawLineB(const Vector3& v1, const Vector3& v2, Vector3& c1, Vector3& c2);
	
	void drawHorizontal(float x1, float x2, float y, Vector3& c1, Vector3& c2);

	// draw triangle using specified colors 
	void Draw_Triangle(float x1, float y1, float x2, float y2, float x3, float y3, Vector3& c1, Vector3& c2, Vector3& c3);
	void Draw_Triangle(Triangle& t, Vector3& c1, Vector3& c2, Vector3& c3);
	// draw triangle using vertex color
	void Draw_Triangle(Triangle& t);
	void Draw_Bottom_Tri(float x1, float y1, float x2, float y2, float x3, float y3, Vector3& c1, Vector3& c2, Vector3& c3);
	void Draw_Top_Tri(float x1, float y1, float x2, float y2, float x3, float y3, Vector3& c1, Vector3& c2, Vector3& c3);

	void scanFillPolyLight(Triangle& t, Vector3& eye);
	void scanFillVertexLight(Triangle& t, Vector3& eye);

	ScreenBuffer* buffer;

private:
	void swap(float& x, float& y);
	void swapColor(DWORD& c1, DWORD& c2);
	void swap(Vector3& x, Vector3& y);
	inline float Area(Vector3& v1, Vector3& v2, Vector3& v3);

	UINT16 screenWidth;
	UINT16 screenHeight;

	std::list<Light> lights;
};

struct Point
{
	float x, y;
};