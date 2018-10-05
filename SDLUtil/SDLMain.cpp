#include "SDLMain.h"

SDLMain::SDLMain(DWORD flag, Uint32 fps, int width, int height, BYTE bpp, DWORD videoflag) : SDLVideo(width, height, bpp, videoflag)
{
	m_nMouseX = m_nMouseY = 0;
	m_nFps = fps;
	m_bInputMode = true;

	m_Font = new SDLFont;
	if(SDL_Init(flag) < 0) {
		fprintf(stderr, "SDLMain::SDLMain() Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	}

	memset(m_KeyBuffer, 0, sizeof(m_KeyBuffer));
	memset(m_MouseButtonDown, 0, sizeof(m_MouseButtonDown));
}

SDLMain::~SDLMain()
{
	SAFE_DELETE(m_Font);
	atexit(SDL_Quit);
}

void SDLMain::SetCaption(char* caption, char* iconfilename)
{
	SDL_WM_SetCaption(caption, iconfilename); 
}

void SDLMain::Loop()
{
	while(1)
	{
		SDL_Event event;
		if(SDL_PollEvent(&event))
		{
			if(m_bInputMode)
			{
				switch (event.type)
				{
				case SDL_MOUSEMOTION:
					{
						if(!GetGuiManager()->MouseMove(event.motion.x, event.motion.y))
							MouseMove(event.motion.x, event.motion.y);
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					{
						MOUSE_BUTTON eButton = (MOUSE_BUTTON)(event.button.button - 1);
						if(!GetGuiManager()->MouseButtonDown(eButton, event.button.x, event.button.y))
							MouseButtonDown(eButton, event.button.x, event.button.y);
					}
					break;
				case SDL_MOUSEBUTTONUP:
					{
						MOUSE_BUTTON eButton = (MOUSE_BUTTON)(event.button.button - 1);
						if(!GetGuiManager()->MouseButtonUp(eButton, event.button.x, event.button.y))
							MouseButtonUp(eButton, event.button.x, event.button.y);
					}
					break;
				case SDL_KEYDOWN:
					if(!GetGuiManager()->KeyDown(event.key.keysym.sym))
						KeyDown(event.key.keysym.sym);
					break;
				case SDL_KEYUP:
					if(!GetGuiManager()->KeyUp(event.key.keysym.sym))
						KeyUp(event.key.keysym.sym);
					break;
				}
			}

			switch(event.type)
			{
			case SDL_QUIT:
				exit(1);
				break;
			}
		}
		else
		{
			static Uint32 lasttime = SDL_GetTicks();
			Uint32 curtime = SDL_GetTicks();
			Uint32 gaptime = curtime-lasttime;
			if (gaptime >= 1000/m_nFps) 
			{
				lasttime += 1000/m_nFps;
				Act();
				if(GetGuiManager()->PreemitiveDraw())
				{
					Flip();
				}
				else
				{
					Draw();
				}
			}
			else
			{
				SDL_Delay(max(1000/m_nFps - gaptime, 1));
			}
		}		
	}
}

void SDLMain::EffectEnd()
{
	m_bInputMode = true;
	__super::EffectEnd();
}

void SDLMain::ShowCursor(bool bShow)
{
	SDL_ShowCursor(bShow);
}

void SDLMain::KeyDown(int keyvalue)
{
	if(0 <= keyvalue && keyvalue <= SDLK_LAST)
	{
		m_KeyBuffer[keyvalue] = true;
	}
}

void SDLMain::KeyUp(int keyvalue)
{
	if(0 <= keyvalue && keyvalue <= SDLK_LAST)
	{
		m_KeyBuffer[keyvalue] = false;
	}
}

bool SDLMain::isKeyDown(int keyvalue)
{
	if(0 <= keyvalue && keyvalue <= SDLK_LAST)
	{
		return m_KeyBuffer[keyvalue];
	}
	return false;
}

void SDLMain::MouseMove(int x, int y)
{
	m_nMouseX = x;
	m_nMouseY = y;
}

void SDLMain::MouseButtonDown(MOUSE_BUTTON eMouseButton, int x, int y)
{
	m_MouseButtonDown[eMouseButton] = true;
}

void SDLMain::MouseButtonUp(MOUSE_BUTTON eMouseButton, int x, int y)
{
	m_MouseButtonDown[eMouseButton] = false;
}