#pragma once

#include "GuiParent.h"
#include <SDL.h>

class GuiImage : public GuiParent
{
	SDL_Surface* m_Surface;
public:
	GuiImage(int x, int y, SDL_Surface* surface, bool bVisible = true);
	~GuiImage();
	virtual void Draw();
};