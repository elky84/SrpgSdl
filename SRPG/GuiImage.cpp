#include "GuiImage.h"
#include "GameMain.h"

GuiImage::GuiImage(int x, int y, SDL_Surface* surface, bool bVisible /* = true*/) : GuiParent(x, y, surface->w, surface->h, bVisible)
{
	m_Surface = surface;
}

GuiImage::~GuiImage()
{

}

void GuiImage::Draw()
{
	GetGameMain()->Blit(m_Surface);
}