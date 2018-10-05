#pragma once

#include "sdlmain.h"
#include "sdlvideo.h"
#include "sdlfont.h"
#include "Singleton.h"

class CharacterParent;
class CTile;
class GuiParent;

const int MAX_SCROLL_X = 1280;
const int MAX_SCROLL_Y = 1280;

const int SCROLL_VALUE = 64;

class CGameMain : public SDLMain , public CSingleton<CGameMain>
{ 
	GuiParent* m_pLogoGui;
	SDL_Surface* m_BackSurface;

	CharacterParent* m_pSelectCharacter;
	CharacterParent* m_pEffectCharacter;

	CTile* m_pTileWhite;
	CTile* m_pTileRed;
	CTile* m_pTileSelect;
	CTile* m_pTileCursor;

	int m_nScrollX, m_nScrollY;

public:
	CGameMain(DWORD flag, unsigned long fps);
	~CGameMain();

	bool isShowCursor();
	void Scroll();

	void DrawSelectCursor(SDL_Rect* dstrect);

	void Damage();

	virtual void EffectEnd();

	void DrawBackSurface(SDL_Surface* surface, SDL_Rect* srcrect, SDL_Rect* dstrect);
	void DrawCursor();
	void DrawMoveableTile(SDL_Rect* destrect);
	void DrawAttackableTile(SDL_Rect* destrect);

	virtual void Draw();
	virtual void Act();
	virtual void KeyUp(int keyvalue);
	virtual void MouseMove(int x, int y);
	virtual void MouseButtonDown(MOUSE_BUTTON eMouseButton, int x, int y);

	void UnselectCharacter();
};

inline CGameMain* GetGameMain()
{
	return CGameMain::GetInstancePtr() ;
}
