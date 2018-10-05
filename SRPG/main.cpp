#include <Windows.h>
#include "gamemain.h"
#include "sdlvideo.h"

#pragma comment(lib, "winmm.lib")

int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPTSTR    lpCmdLine,
					 int       nCmdShow)
{
	CGameMain* main = new CGameMain(SDL_INIT_VIDEO, 60);
	main->Loop();
	delete GetGameMain();
	return 0;
}