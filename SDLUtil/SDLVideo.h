#pragma once

#include "SDLCommon.h"

#include "SDL_image.h"

#pragma comment(lib, "sdl_image.lib")

#define EffectFuncPtr void (SDLVideo::*)()

class SDLVideo
{
public:
	static void SetAlpha(SDL_Surface* surface, BYTE alpha);
	static SDL_Surface*  LoadImg(char* filename);
	static SDL_Surface*  LoadImgColorKey(char* filename, DWORD colorkey = RGB(255, 0, 255));
	static SDL_Surface*  LoadImgAlpha(char* filename, BYTE alpha = 128);
	static void SetColorKey(SDL_Surface* image, DWORD colorkey = RGB(255, 0, 255));
	static SDL_Surface*  InvertImage(SDL_Surface* image, SDL_Rect* srcrect);
	static bool Lock(SDL_Surface* image);
	static void Unlock(SDL_Surface* image);
	static SDL_Surface*  CreateSurface(DWORD flag, int width, int height, BYTE bpp = DEFAULT_SURFACE_DEPTH, BYTE rMask = 0, BYTE gMask = 0, BYTE bMask = 0, BYTE aMask = 0);
	static void Fill(SDL_Surface* surface, DWORD color = RGB(0, 0, 0));

private:
	int m_nWidth, m_nHeight;
	BYTE m_nBpp;
	SDL_Surface* m_Screen;
	SDL_Surface* m_EffectSurface;

	void (SDLVideo::*m_Effect)();

protected:
	int GetWidth(){return m_nWidth;}
	int GetHeight(){return m_nHeight;}

public:
	SDLVideo(int width, int height, BYTE bpp, DWORD flag);
	~SDLVideo();

	void Blit(SDL_Surface* src, SDL_Rect* srcrect, SDL_Surface* dest, SDL_Rect* destrect);
	void Blit(SDL_Surface* image);
	void Blit(SDL_Surface* image, int x, int y);
	void Blit(SDL_Surface* image, SDL_Rect* srcrect, int x, int y);
	void DrawPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b);
	void Flip();
	void SetFadeOut();
	void FadeOut();

	void SetEffect(void (SDLVideo::*EffectFunc)());

	void SetFadeIn();
	void FadeIn();

	virtual void EffectEnd();
};