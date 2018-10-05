#pragma once

#include "SDLCommon.h"
#include "GuiManager.h"
#include "SDLFont.h"
#include "SDLVideo.h"

#pragma comment(lib, "sdl.lib")

class SDLMain : public SDLVideo
{
	bool m_bInputMode;
	Uint32 m_nFps;
protected:
	bool m_KeyBuffer[SDLK_LAST];
	bool m_MouseButtonDown[MOUSEBUTTON_LAST];
	SDLFont* m_Font;
	int m_nMouseX, m_nMouseY;

public:
	SDLMain(DWORD flag, Uint32 fps, int width = DEFAULT_SURFACE_WIDTH, int height = DEFAULT_SURFACE_HEIGHT, BYTE bpp = DEFAULT_SURFACE_DEPTH, 
		DWORD videoflag = SDL_HWSURFACE | SDL_DOUBLEBUF);
	virtual ~SDLMain();

	SDLFont*  GetFont(){return m_Font;}

	virtual void EffectEnd();
	void SetInputMode(bool bMode){m_bInputMode = bMode;}

	virtual void MouseMove(int x, int y); //마우스 움직임
	virtual void MouseButtonDown(MOUSE_BUTTON eMouseButton, int x, int y);
	virtual void MouseButtonUp(MOUSE_BUTTON eMouseButton, int x, int y);
	virtual void KeyDown(int keyvalue);
	virtual void KeyUp(int keyvalue);
	virtual void Draw() = 0;
	virtual void Act() = 0;

	bool isKeyDown(int keyvalue);

	void SetCaption(char* caption, char* iconfilename = NULL);

	virtual void Loop();
	void ShowCursor(bool bShow);
};