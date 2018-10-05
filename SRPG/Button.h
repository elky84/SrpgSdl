#pragma once

#include "GuiButton.h"
#include "GameMain.h"

template<typename T> class CButton : public GuiButton<T>
{
	SDL_Surface* m_ImgSurface[2];
	SDL_Rect m_DestRect;
	SDL_Rect m_SrcRect;
public:
	CButton(int x, int y, SDL_Surface* surface1, SDL_Surface* surface2, void (T::*actfunc)(), T* inter) :  GuiButton<T>(x, y, surface1->w, surface1->h, actfunc, inter)
	{
		m_ImgSurface[0] = surface1;
		m_ImgSurface[1] = surface2;

		m_SrcRect.x = 0;
		m_SrcRect.y = 0;
		m_SrcRect.w = surface1->w;
		m_SrcRect.h = surface1->h;

		m_DestRect.x = x;
		m_DestRect.y = y;
		m_DestRect.w = x + surface1->w;
		m_DestRect.h = y + surface1->h;
	}

	virtual void Draw()
	{
		GetGameMain()->DrawBackSurface(m_ImgSurface[m_bMouseOver], &m_SrcRect, &m_DestRect);
	}

	SDL_Rect* GetDestRect(){
		return &m_DestRect;
	}

	SDL_Rect* GetSrcRect(){
		return &m_SrcRect;
	}

	virtual void SetX(int x){
		GuiParent::SetX(x);
		m_DestRect.x = m_nX;
		m_DestRect.w = m_nX + m_nWidth;
	}
	virtual void SetY(int y){
		GuiParent::SetY(y);
		m_DestRect.y = m_nY;
		m_DestRect.h = m_nY + m_nHeight;
	}
};