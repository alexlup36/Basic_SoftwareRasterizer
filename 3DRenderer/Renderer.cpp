#include "StdAfx.h"
#include "Renderer.h"


Renderer::Renderer(HWND hwnd)
{
	this->hwnd = hwnd;
	// Create a new GfxStats object
	gfx = new GfxStats();

	// Init screen dimensions
	RECT r;
	GetClientRect(hwnd, &r);
	screenWidth		= r.right;
	screenHeight	= r.bottom;

	// Create a rasterizer
	rasterizer = new Rasterizer(screenWidth, screenHeight);

	// Load model 1
	ObjImporter::getData("teapot.obj");
	model1 = new TriMesh(
		ObjImporter::Vertices(), 
		ObjImporter::NoOfVertices(), 
		ObjImporter::Indices(),
		ObjImporter::NoOfIndices());

	// Load model 2
	ObjImporter::getData("tie_fighter.obj");
	model2 = new TriMesh(
		ObjImporter::Vertices(), 
		ObjImporter::NoOfVertices(), 
		ObjImporter::Indices(),
		ObjImporter::NoOfIndices());

	// Init camera information
	_cameraPosition = Vector3(0.0f, 0.0f, 10.0f);
	_cameraTarget	= Vector3(0.0f, 0.0f, 0.0f);
	_cameraUp		= Vector3(0.0f, 1.0f, 0.0f);

	_view = Camera::CreateViewMatrix(_cameraPosition, _cameraTarget, _cameraUp);
	_projection = Camera::CreatePerspectiveFieldOfView((PI / 4.0f), (float)screenWidth / screenHeight, 1.0f, 500.0f);

	// Compute the vector from camera position to its target
	eye = Vector3::Normalize(_cameraTarget - _cameraPosition);

	// Set the world matrix for model1 and the world * view * projection matrix
	_worldTeapot = Matrix4::Matrix4Scale(150) *
		Matrix4::Matrix4Translation(3.5f, 0.3f, 0);

	_worldViewProjection = _projection * _view * _worldTeapot;
	model1->SetProjection(_projection);
	model1->SetView(_view);

	// Rotation angle
	angle = 0;
	displayOption = 1;
}


Renderer::~Renderer(void)
{
	ReleaseDC(hwnd, backDC);
	DeleteObject(hbmBuf);
	DeleteDC(backDC);
	delete gfx;
}


void Renderer::Draw()
{
	rasterizer->buffer->clearScreen(0x00000000);

	model1->SetTransformation(_worldViewProjection * Matrix4::Matrix4CreateRotationY(angle));
	model1->SetWorld(_worldTeapot * Matrix4::Matrix4CreateRotationY(angle));
	
	// Draws mesh in different ways

	switch (displayOption)
	{
	case 1:
		// wireframe no back face
		gfx->displayMode = 1;
		gfx->setTriCount(model1->GetTriangleQuantity());
		gfx->setVertexCount(model1->vertexQuantity);

		model1->drawWireFrameNoBackFaceCulling(rasterizer, RGB(255, 255, 255));
		break;
	case 2:
		// wireframe back face
		gfx->displayMode = 2;
		gfx->setActiveTri(model1->activeTriangles);
		gfx->setTriCount(model1->GetTriangleQuantity());
		gfx->setVertexCount(model1->vertexQuantity);

		model1->drawWireFrameBackFaceCulling(rasterizer, eye, RGB(0, 0, 255));
		break;
	case 3:
		// Import 2 3D model1s
		gfx->displayMode = 3;
		gfx->setTriCount(model1->GetTriangleQuantity() + model2->GetTriangleQuantity());
		gfx->setVertexCount(model1->vertexQuantity + model2->vertexQuantity);
		gfx->setActiveTri(model1->activeTriangles + model2->activeTriangles);

		// Set world matrix for teapot
		_worldTeapot = Matrix4::Matrix4Scale(140) * Matrix4::Matrix4Translation(3.5f, 0.5f, 0) * Matrix4::Matrix4CreateRotationX(15);

		// Set world matrix for fighter
		_worldFighter = Matrix4::Matrix4Scale(50) * Matrix4::Matrix4Translation(25.0f, 5.0f, 0);

		model1->SetTransformation(_projection * _view * _worldTeapot * Matrix4::Matrix4CreateRotationY(angle));
		model1->SetWorld(_worldTeapot * Matrix4::Matrix4CreateRotationY(angle));

		model2->SetTransformation(_projection * _view * _worldFighter * Matrix4::Matrix4CreateRotationY(angle) * Matrix4::Matrix4CreateRotationX(angle));
		model2->SetWorld(_worldFighter * Matrix4::Matrix4CreateRotationY(angle));

		model1->drawWireFrameBackFaceCulling(rasterizer, eye, RGB(0, 0, 255));
		model2->drawWireFrameBackFaceCulling(rasterizer, eye, RGB(0, 0, 255));

		break;
	case 4:
		// flat shaded no light, interpolated colors for triangles - one color
		gfx->displayMode = 4;
		gfx->setActiveTri(model1->activeTriangles);
		gfx->setTriCount(model1->GetTriangleQuantity());
		gfx->setVertexCount(model1->vertexQuantity);

		model1->drawFlatShadedOneColor(rasterizer, eye, Vector3(255.0f, 255.0f, 0.0f));
		break;
	case 5:
		// flat shaded no light, interpolated colors for triangles - random colors
		gfx->displayMode = 5;
		gfx->setActiveTri(model1->activeTriangles);
		gfx->setTriCount(model1->GetTriangleQuantity());
		gfx->setVertexCount(model1->vertexQuantity);

		model1->drawFlatShadedRandomColors(rasterizer, eye, Vector3(255.0f, 255.0f, 0.0f));
		break;
	case 6:
		//flat shaded lighting / polygon
		gfx->displayMode = 6;
		gfx->setActiveTri(model1->activeTriangles);
		gfx->setTriCount(model1->GetTriangleQuantity());
		gfx->setVertexCount(model1->vertexQuantity);

		_worldTeapot = Matrix4::Matrix4Scale(140) * Matrix4::Matrix4Translation(3.5f, 0.7f, 0) * Matrix4::Matrix4CreateRotationX(10)
			* Matrix4::Matrix4CreateRotationY(angle);
		model1->SetTransformation(_projection * _view * _worldTeapot);
		model1->SetWorld(_worldTeapot * Matrix4::Matrix4CreateRotationY(angle));

		model1->drawFlatShadedLight(rasterizer, eye);
		break;
	case 7:
		//per vertex shading
		gfx->displayMode = 7;
		gfx->setActiveTri(model1->activeTriangles);
		gfx->setTriCount(model1->GetTriangleQuantity());
		gfx->setVertexCount(model1->vertexQuantity);

		_worldTeapot = Matrix4::Matrix4Scale(140) * Matrix4::Matrix4Translation(3.5f, 0.7f, 0) * Matrix4::Matrix4CreateRotationX(10)
			* Matrix4::Matrix4CreateRotationY(angle);
		model1->SetTransformation(_projection * _view * _worldTeapot);
		model1->SetWorld(_worldTeapot * Matrix4::Matrix4CreateRotationY(angle));

		model1->drawPerVertexShading(rasterizer, eye);
		break;
	}
}

void Renderer::Update(float dt)
{
	angle += 1.5f;

	gfx->update(dt);
}

// Swap buffer
// Gets the current bitmap from the rasterizer and selects it into a temp device context
// and then copies the information from the bitmap to application main device context
void Renderer::swapBuffer()
{
	HDC winhdc = GetDC(hwnd);

	HBITMAP hBitmap = rasterizer->buffer->GetBitmap();
	HDC hdcMem = CreateCompatibleDC(winhdc);
	HGDIOBJ oldObj = SelectObject(hdcMem, hBitmap);

	BitBlt(winhdc, 0, 0, rasterizer->buffer->GetScreenWidth(), rasterizer->buffer->GetScreenHeight(), hdcMem, 0, 0, SRCCOPY);
	gfx->display(winhdc);

	SelectObject(hdcMem, oldObj);
	DeleteDC(hdcMem);

	ReleaseDC(hwnd, winhdc);
}