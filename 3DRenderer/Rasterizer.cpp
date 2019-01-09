#include "StdAfx.h"
#include "Rasterizer.h"


Rasterizer::Rasterizer(UINT16 width, UINT16 height) 
{ 
	Rasterizer::screenHeight	= height; 
	Rasterizer::screenWidth		= width;

	// Create the backbuffer
	buffer = new ScreenBuffer(screenWidth, screenHeight);

	// Init light material properties
	material mLightDarkBlue;
	mLightDarkBlue.ka = Colour(0.05f, 0.0f, 0.0f);
	mLightDarkBlue.kd = Colour(0.5f, 0.0f, 0.0f);
	mLightDarkBlue.ks = Colour(1.0f, 1.0f, 1.0f);
	
	material mLightRed;
	mLightRed.ka = Colour(0.0f, 1.0f, 0.0f);
	mLightRed.kd = Colour(0.0f, 0.0f, 0.0f);
	mLightRed.ks = Colour(0.3f, 0.3f, 0.3f);

	// teapot
	lights.insert(lights.begin(), *(new Light(Vector3::Zero(), Vector3(1, 1, -1), mLightDarkBlue, 64)));

	// fighter
	//lights.insert(lights.begin(), *(new Light(Vector3::Zero(), Vector3(-1, -1, 1), mLightDarkBlue, 50)));

	//lights.insert(lights.begin(), *(new Light(Vector3::Zero(), Vector3::Zero(), mLightRed)));
	//lights.insert(lights.begin(), *(new Light(Vector3::Zero(), Vector3(1, -1, 0), mLightRed)));
}

Rasterizer::~Rasterizer(void)
{
}

void Rasterizer::drawText(HDC hdc, char* text, int x, int y, COLORREF color, size_t length)
{
	SetTextColor(hdc, color);
	SetBkMode(hdc, TRANSPARENT); 
	TextOut(hdc, x, y, text, length);
}

void Rasterizer::drawLineB(const Vector3& v1, const Vector3& v2, DWORD& c)
{
	drawLineB(v1.GetX(), v1.GetY(), v2.GetX(), v2.GetY(), c);
}

// Line drawing using Bresenham's algorithm
void Rasterizer::drawLineB(float x1, float y1, float x2, float y2, DWORD c)
{
	const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));

	if (steep)
	{
		swap(x1, y1);
		swap(x2, y2);
	}
 
	if (x1 > x2)
	{
		swap(x1, x2);
		swap(y1, y2);
	}
 
	const float dx = x2 - x1;
	const float dy = fabs(y2 - y1);
 
	float error = dx / 2.0f;
	const int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;
 
	const int maxX = (int)x2;
 
	for (int x = (int)x1; x < maxX; x++)
	{
		if (steep)
        {
			Rasterizer::buffer->setPixel(x * Rasterizer::buffer->GetScreenWidth() + y, c);
        }
		else
        {
			Rasterizer::buffer->setPixel(y * Rasterizer::buffer->GetScreenWidth() + x, c);
		}
 
        error -= dy;
		if(error < 0)
	    {
		    y += ystep;
		    error += dx;
	    }
	}
}

void Rasterizer::swap(float& x, float& y)
{
	float temp = x;
	x = y;
	y = temp;
}

void Rasterizer::swap(Vector3& x, Vector3& y)
{
	Vector3 temp = x;
	x = y;
	y = temp;
}

// Calculate the light per polygon, Draw polygon
void Rasterizer::scanFillPolyLight(Triangle& t, Vector3& eye)
{
	std::list<Light>::iterator it = lights.begin();
	Colour ra, rd, rs;
	
	// Iterate through the vector of lights (for multiple lights)
	for (; it != lights.end(); it++)
	{
		float x = Vector3::Vec3Dot(t.getNormal(), (*it).direction);

		// Ambient component
		ra += t.Material().ka * (*it).m.ka;
		// Diffuse component
		rd += t.Material().kd * (*it).m.kd * Vector3::Vec3Dot(t.getNormal(), (*it).direction);

		// Specular component
		Vector3 h = Vector3::Normalize((*it).direction + eye);
		rs += t.Material().ks * (*it).m.ks * pow(Vector3::Vec3Dot(t.getNormal(), h), (*it).spec);
	}
	// Reflectance model
	Vector3 light = ra + rd + rs;

	// Update the triangle's normal
	t.updateNormal();

	// Draw filled triangle, each vertex has the same color
	Draw_Triangle(t, light, light, light);
}

// Calculate the light per vertex, Draw polygon
void Rasterizer::scanFillVertexLight(Triangle& t, Vector3& eye)
{
	// For each vertex calculate the color
	for (int i = 0; i < 3; i++)
	{
		std::list<Light>::iterator it = lights.begin();
		Colour ra, rd, rs;

		for (; it != lights.end(); it++)
		{
			ra += t.Material().ka * (*it).m.ka;
			rd += t.Material().kd * (*it).m.kd * Vector3::Vec3Dot(t.vertices[i].TransformedNormal, (*it).direction);

			Vector3 h = Vector3::Normalize((*it).direction + eye);
			rs += t.Material().ks * (*it).m.ks * pow(Vector3::Vec3Dot(t.vertices[i].TransformedNormal, h), (*it).spec);
		}
		Vector3 light = ra + rd + rs;

		// Update vertex's color
		t.vertices[i].SetColor(light);
	}

	// Draw the triangle using interpolation
	Draw_Triangle(t);
}


void Rasterizer::drawLineB(const Vector3& v1, const Vector3& v2, Vector3& c1, Vector3& c2)
{
	float x1 = v1.GetX();
	float y1 = v1.GetY();
	float x2 = v2.GetX();
	float y2 = v2.GetY();

	const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));

	if (steep)
	{
		swap(x1, y1);
		swap(x2, y2);
	}
 
	if (x1 > x2)
	{
		swap(x1, x2);
		swap(y1, y2);
	}
 
	const float dx = x2 - x1;
	const float dy = fabs(y2 - y1);
 
	float error = dx / 2.0f;
	const int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;
 
	const int maxX = (int)x2;
 
	for (int x = (int)x1; x < maxX; x++)
	{
		if (steep)
        {
			float t = (float)(x1 - x) / abs(v2.GetX() - v1.GetX());
			Vector3 c = (c1 - c2) * t + c2;

			Rasterizer::buffer->setPixel(x * Rasterizer::buffer->GetScreenWidth() + y, RGB(c.GetX(), c.GetY(), c.GetZ()));
        }
		else
        {
			float t = (float)(x1 - x) / abs(v2.GetX() - v1.GetX());
			Vector3 c = (c1 - c2) * t + c2;

			Rasterizer::buffer->setPixel(y * Rasterizer::buffer->GetScreenWidth() + x, RGB(c.GetX(), c.GetY(), c.GetZ()));
		}
 
        error -= dy;
		if(error < 0)
	    {
		    y += ystep;
		    error += dx;
	    }
	}
}

float Rasterizer::Area(Vector3& v1, Vector3& v2, Vector3& v3)
{
	Vector3 x1 = v2 - v1;
	Vector3 x2 = v3 - v1;
	
	return x1.GetX() * x2.GetY() - x1.GetY() * x2.GetX();
}


// draw horizontal line using linear interpolation
void Rasterizer::drawHorizontal(float x1, float x2, const float y,  Vector3& c1, Vector3& c2)
{
	if (x1 > x2)
	{
		swap(x1, x2);
	}

	DWORD* dest = buffer->PixelData() + buffer->GetScreenWidth() * (unsigned int)y + (unsigned int)x1;
	size_t s = (int)x2 - (int)x1 + 1;

	DWORD* maxPtr = dest + s;
	DWORD* ptr = dest;
	while (ptr < maxPtr)
    {
		float t = (float)(ptr - dest) / s;
		Vector3 c = (c2 - c1) * t + c1;

		*ptr++ = RGB(c.GetX(), c.GetY(), c.GetZ());
	}
}

void Rasterizer::Draw_Triangle(Triangle& t)
{
	Draw_Triangle(t, t.vertices[0].Color(), t.vertices[1].Color(), t.vertices[2].Color());
}

// draw triangle using specified colors 
void Rasterizer::Draw_Triangle(Triangle& t, Vector3& c1, Vector3& c2, Vector3& c3)
{
	Draw_Triangle(t.transfCoordinates[0].GetX(), t.transfCoordinates[0].GetY(),
		t.transfCoordinates[1].GetX(), t.transfCoordinates[1].GetY(),
		t.transfCoordinates[2].GetX(), t.transfCoordinates[2].GetY(),
		c1,
		c2,
		c3);
}

// Function for drawing a general triangle using specified colors
void Rasterizer::Draw_Triangle(float x1, float y1,
	float x2, float y2,
	float x3, float y3,
	Vector3& c1, Vector3& c2, Vector3& c3)
{
	// this function draws a triangle on the destination buffer
	// it decomposes all triangles into a pair of flat top, flat bottom

	// separation line 
	float new_x;
		
	// test for h lines and v lines
	if ((FCMP(x1, x2) && FCMP(x2, x3)) || (FCMP(y1, y2) && FCMP(y2, y3)))
		return;

	// sort p1,p2,p3 in ascending y order
	if (y2 < y1)
	{
		swap(x1, x2);
		swap(y1, y2);
		swap(c1, c2);
	}

	// now we know that p1 and p2 are in order
	if (y3 < y1)
	{
		swap(x1, x3); 
		swap(y1, y3);
		swap(c1, c3);
	}

	// finally test y3 against y2
	if (y3 < y2)
	{
		swap(x2, x3);
		swap(y2, y3);
		swap(c2, c3);
	}

	// test if top of triangle is flat
	if (FCMP(y3, y2))
	{
		Draw_Top_Tri(x1, y1, x2, y2, x3, y3, c1, c2, c3);
	}
	else if (FCMP(y2, y1))
	{
		Draw_Bottom_Tri(x1, y1, x2, y2, x3, y3, c1, c2, c3);
	}
	else
	{
		// general triangle that’s needs to be broken up along long edge
		new_x = x1 + (y2-y1)*(x3-x1)/(y3-y1);

		float b1 = (float)Area(Vector3(new_x, y2, 0.0f), Vector3(x3, y3, 0.0f), Vector3(x2, y2, 0.0f)) 
			/ (Area(Vector3(x3, y3, 0.0f), Vector3(x2, y2, 0.0f), Vector3(x1, y1, 0.0f)));
		float b3 = 1.0f - b1;
		float b2 = 0.0f;

		Vector3 cfinal = c1 * b1 + c2 * b2 + c3 * b3;

		// draw each sub-triangle
		Draw_Top_Tri(x1, y1, new_x, y2, x2, y2, c1, c2, cfinal);
		Draw_Bottom_Tri(x2, y2, new_x, y2, x3, y3, c2, cfinal, c3);
	}
}

// Function for drawing a flat bottom triangle
void Rasterizer::Draw_Top_Tri(float x1, float y1, float x2, float y2, float x3, float y3, Vector3& c1, Vector3& c2, Vector3& c3)
{
	// this function draws a triangle that has a flat top
	float dx_right, // the dx/dy ratio of the right edge of line
	dx_left, // the dx/dy ratio of the left edge of line
	xs, xe, // the starting and ending points of the edges
	height; // the height of the triangle
	
	int iy1, iy3, loop_y;

	// test order
	if (x3 < x2)
	{
		swap(x2, x3);
	}

	// compute delta’s
	height = y3 - y1;
	dx_right = (x3 - x1) / height;
	dx_left = (x2 - x1) / height;

	// set starting points
	xs = x1;
	xe = x1;

	// make sure top left fill convention is observed
	iy1 = (int)ceil(y1);
	// bump xs and xe appropriately
	xs = xs + dx_left * (iy1 - y1);
	xe = xe + dx_right * (iy1 - y1);

	iy3 = (int)floor(y3);

	// draw the triangle
	for (loop_y = iy1; loop_y <= iy3; loop_y++)
	{
		// calculate color of endpoints using barycentric coordinates
		float b1 = (float)(y2 - loop_y) / (y2 - y1);
		float b2 = 1.0f - b1;
		float b3 = 0.0f;

		Vector3 cs = c1 * b1 + c2 * b2 + c3 * b3;

		b3 = 1.0f - b1;
		b2 = 0.0f;
		Vector3 ce = c1 * b1 + c2 * b2 + c3 * b3;

		// draw the line
		drawHorizontal(xs, xe, (float)loop_y, cs, ce);
		// adjust starting point and ending point
		xs += dx_left;
		xe += dx_right;
	}
}
	
// Function for drawing a flat top triangle
void Rasterizer::Draw_Bottom_Tri(float x1, float y1, float x2, float y2, float x3, float y3, Vector3& c1, Vector3& c2, Vector3& c3)
{
	// this function draws a triangle that has a flat bottom
	float dx_right, // the dx/dy ratio of the right edge of line
	dx_left, // the dx/dy ratio of the left edge of line
	xs, xe, // the starting and ending points of the edges
	height; // the height of the triangle
	
	int iy1, iy3, loop_y;

	// test order of x1 and x2
	if (x2 < x1)
	{
		swap(x2, x1);
	}

	// compute delta’s
	height = y3 - y1;
	dx_left = (x1 - x3) / height;
	dx_right = (x2 - x3) / height;

	// set starting points
	xs = x3;
	xe = x3;

	// make sure top left fill convention is observed
	iy3 = (int)floor(y3);
	// bump xs and xe appropriately
	xs = xs + dx_left * (y3 - iy3);
	xe = xe + dx_right * (y3 - iy3);

	iy1 = (int)floor(y1) + 1;

	// draw the triangle
	for (loop_y = iy3; loop_y >= iy1; loop_y--)
	{
		// calculate color of endpoints using barycentric coordinates
		float b1 = (float)(y3 - loop_y) / (y3 - y1);
		float b3 = 1.0f - b1;
		float b2 = 0.0f;

		Vector3 cs = c1 * b1 + c2 * b2 + c3 * b3;

		b2 =  Area(Vector3(x2, y2, 0.0f), Vector3(x3, y3, 0.0f), Vector3(xs, (float)loop_y, 0.0f)) 
			/ Area(Vector3(x1, y1, 0.0f), Vector3(x2, y2, 0.0f), Vector3(x3, y3, 0.0f));;
		b3 = 1.0f - b2;
		b1 = 0.0f;

		Vector3 ce = c1 * b1 + c2 * b2 + c3 * b3;

		// draw the line
		drawHorizontal(xs, xe, (float)loop_y, cs, ce);
		// adjust starting point and ending point
		xs += dx_left;
		xe += dx_right;
	}
}

void Rasterizer::swapColor(DWORD& c1, DWORD& c2)
{
	DWORD tempC = c1;
	c1 = c2;
	c2 = tempC;
}