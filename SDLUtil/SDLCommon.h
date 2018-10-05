#pragma once

#include <sdl.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

#define SAFE_DELETE(x) if(x) delete x; x = NULL;
#define SAFE_DELETE_ARRAY(x) if(x) delete []x; x = NULL;
#define SAFE_RELEASE(x) if(x) x->Release(); x = NULL;
#define SAFE_DELTE_OBJECT(x) if(x) DeleteObject(x);

const float EPSILON = 0.000001f;

const int UNDEFINED = -1;
const int DEFAULT_SURFACE_WIDTH = 640;
const int DEFAULT_SURFACE_HEIGHT = 480;
const int DEFAULT_SURFACE_DEPTH = 16;

//매개 변수 r,g,b 각각을 RGB값을 조합한 DWORD형으로 변환해주는 인라인 함수
inline DWORD RGBAUTO(int r, int g, int b) { return ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF); } 

//매개 변수 r,g,b,a 각각을 RGB값을 조합한 DWORD형으로 변환해주는 인라인 함수
inline DWORD RGBAAUTO(int r, int g, int b, int a) { return ((r & 0xFF) << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | (a & 0xFF); } 
//RGB형식인 DWORD형에서, Red값만 읽어오는 인라인 함수
inline BYTE RGBRed(DWORD rgb) {return (BYTE)(rgb >> 16); }
//RGB형식인 DWORD형에서, Green값만 읽어오는 인라인 함수
inline BYTE RGBGreen(DWORD rgb) {return (BYTE)(rgb >> 8);}
//RGB형식인 DWORD형에서, Blue값만 읽어오는 인라인 함수
inline BYTE RGBBlue(DWORD rgb) {return (BYTE)rgb;}

inline WORD Convert15(BYTE r, BYTE g, BYTE b){return (WORD)(((r&248)<<7) + ((g&248)<<2) + (b>>3));}
inline WORD Convert16(BYTE r, BYTE g, BYTE b){return (WORD)(((r&248)<<8) + ((g&252)<<3) + (b>>3));}

enum COLOR_TYPE{
	COLORTYPE_NONE = -1,
	COLORTYPE_555 = 0,
	COLORTYPE_565,
	COLORTYPE_8BIT,
	COLORTYPE_24BIT,
	COLORTYPE_32BIT,
};

struct CImageData{
	char* m_pData; //픽셀 데이터
	int m_nWidth; //이미지 넓이
	int m_nHeight; //이미지 높이
	int m_nPixelPerByte; //픽셀 당 몇 바이트인지 여부
	COLOR_TYPE m_ColorType; //어떤 색상값이 기본인지
	int GetWidth(){
		return m_nWidth;
	}
	int GetHeight(){
		return m_nHeight;
	}
	char* GetData(){
		return m_pData;
	}
	int GetPixelPerByte(){
		return m_nPixelPerByte;
	}
	COLOR_TYPE GetColorType(){
		return m_ColorType;
	}
	CImageData(){
		memset(this, 0, sizeof(CImageData));
	}
	CImageData(char* data, int width, int height, int pixelperbyte, COLOR_TYPE colortype) : m_pData(data), m_nWidth(width),
		m_nHeight(height), m_nPixelPerByte(pixelperbyte), m_ColorType(colortype)
	{
	}
};