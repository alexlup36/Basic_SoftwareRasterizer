#include "StdAfx.h"
#include "ScreenBuffer.h"


ScreenBuffer::ScreenBuffer(UINT width, UINT height)
	: screenHeight(height), screenWidth(width), noOfPixels(height * width) 
{
	ZeroMemory(&info, sizeof(BITMAPINFO));
	info.bmiHeader.biWidth = width;
	info.bmiHeader.biHeight = height;
	info.bmiHeader.biBitCount = 32;
	info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	info.bmiHeader.biPlanes = 1;
	info.bmiHeader.biCompression = BI_RGB;
	hBitmap = CreateDIBSection(NULL, &info, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
	if (!hBitmap)
	{
		std::cout<<"err"<<std::endl;
	}
}


ScreenBuffer::~ScreenBuffer(void)
{
}

HBITMAP ScreenBuffer::GetBitmap()
{
	return hBitmap;
}
	
UINT16 ScreenBuffer::GetScreenWidth()
{
	return screenWidth;
}

UINT16 ScreenBuffer::GetScreenHeight()
{
	return screenHeight;
}

DWORD ScreenBuffer::getPixel(UINT index)
{
	return pBits[index];
}
	
void ScreenBuffer::setPixel(UINT index, DWORD color)
{
	if (index >= 0 && index <= noOfPixels)
	pBits[index] = color;
}

void ScreenBuffer::clearScreen(DWORD color)
{
	for (UINT i = 0; i < noOfPixels; i++)
	{
		pBits[i] = color;
	}
}	

DWORD* ScreenBuffer::PixelData()
{
	return this->pBits;
}

void ScreenBuffer::printBitmap()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			std::cout<< pBits[i * 10 + j]<< " ";
		}
		std::cout<<std::endl;
	}
}