#pragma once

#include "SDL_video.h"

class CTile
{
	int m_nIdx;
	SDL_Surface* m_Surface;
	SDL_Rect m_Rect;
public:
	CTile(int idx, SDL_Surface* surface);
	~CTile();

	int GetIdx(){return m_nIdx;}
	SDL_Surface* GetSurface(){return m_Surface;}
	SDL_Rect* GetRect(){return &m_Rect;}
	int GetWidth(){return m_Surface->w;}
	int GetHeight(){return m_Surface->h;}
};