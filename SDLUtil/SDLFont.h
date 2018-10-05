#pragma once

#include "SDLCommon.h"
#include "sdl_ttf.h"

class SDLFont
{
	SDL_Surface* m_Message; 
	SDL_Color m_TextColor;
	TTF_Font* m_Font; 
public:
	SDLFont();
	~SDLFont();

	bool OpenFont(char* fontname, int size);
	void SetColor(SDL_Color color);
	SDL_Surface* SetText(char* text, ...);
};