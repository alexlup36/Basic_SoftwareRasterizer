#pragma once
#include "Rasterizer.h"
#include "TriMesh.h"
#include "GfxStats.h"

#define PI 3,14159265
class TriMesh;
class GfxStats;
class Rasterizer;

enum TRANS
{
	VIEW, PROJECTION, WORLD
};

class Renderer
{
public:
	Renderer(HWND hwdn);
	~Renderer(void);

	void Draw();
	void Update(float dt);
	void swapBuffer();

	HWND hwnd;
	GfxStats* gfx;
	int displayOption;

private:
	Rasterizer* rasterizer;
	
	float angle;

	TriMesh* model1;
	TriMesh* model2;

	Matrix4 _view;
	Matrix4 _projection;
	Matrix4 _worldViewProjection;
	Matrix4 _worldTeapot;
	Matrix4 _worldFighter;

	Vector3 _cameraPosition;
	Vector3 _cameraUp;
	Vector3 _cameraTarget;
	Vector3 eye;

	HDC			backDC;
	HBITMAP		hbmBuf;
	int			backBufferCX;
	int			backBufferCY;

	int			screenWidth;
	int			screenHeight;
};

