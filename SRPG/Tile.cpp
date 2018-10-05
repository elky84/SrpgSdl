#include "Tile.h"

CTile::CTile(int idx, SDL_Surface* surface)
{
	m_nIdx = idx;
	m_Rect.x = 0;
	m_Rect.y  = 0;
	m_Rect.w = surface->w;
	m_Rect.h = surface->h;
	m_Surface = surface;
}

CTile::~CTile()
{
	SDL_FreeSurface(m_Surface);
}