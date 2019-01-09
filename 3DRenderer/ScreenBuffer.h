#pragma once
#include <Windows.h>
#include <iostream>

class ScreenBuffer
{
public:
	ScreenBuffer(UINT width, UINT height);
	~ScreenBuffer(void);

	HBITMAP GetBitmap();
	UINT16 GetScreenWidth();
	UINT16 GetScreenHeight();

	DWORD getPixel(UINT index);
	void setPixel(UINT index, DWORD color);
	void printBitmap();
	void clearScreen(DWORD color);
	DWORD* PixelData();

private:
	UINT16 screenWidth;
	UINT16 screenHeight;
	UINT noOfPixels;

	// pointer to the begining of the array of pixels
	BITMAPINFOHEADER bmih;
	BITMAPINFO info;
	DWORD* pBits ;
	HBITMAP hBitmap ;
};

