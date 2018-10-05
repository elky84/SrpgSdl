#include "GameMain.h"
#include "Character.h"
#include "GuiPopup.h"
#include "Button.h"
#include "Tile.h"
#include "CharacterManage.h"
#include "TileManage.h"
#include "GuiImage.h"
#include "Npc.h"

const int TILE_SIZE = 64;

CGameMain::CGameMain(DWORD flag, unsigned long fps) : SDLMain(flag, fps)
{
	new GuiManager(m_nScrollX, m_nScrollY, false);

	m_pSelectCharacter = NULL;
	m_pEffectCharacter = NULL;
	m_nScrollX = m_nScrollY = 0;
	m_Font->OpenFont("YW_DOTUM.TTF", 15);
	SetCaption("Super Park Ji Sung War");

	new CTileManage((MAX_SCROLL_X / TILE_SIZE) + 1, (MAX_SCROLL_Y / TILE_SIZE) + 1);

	SDL_Surface* surface = LoadImg("zandi.png");
	GetTileManage()->AddTile(1, surface);
	surface = LoadImgAlpha("red.png");
	m_pTileRed = GetTileManage()->AddTile(2, surface);

	surface = LoadImgColorKey("cursor.png");
	m_pTileCursor = GetTileManage()->AddTile(3, surface);

	surface = LoadImgColorKey("select.png");
	m_pTileSelect = GetTileManage()->AddTile(4, surface);

	surface = LoadImgAlpha("white.png");
	m_pTileWhite = GetTileManage()->AddTile(5, surface);

	m_BackSurface = CreateSurface(SDL_HWSURFACE | SDL_DOUBLEBUF, MAX_SCROLL_X, MAX_SCROLL_Y);

	new CharacterManage;
	surface = LoadImg("박지성.png");
	Character* character1 = new Character(1, surface, 2, 2, 3);
	GetCharacterManage()->AddCharacterParent(character1);
	Character* character2 = new Character(2, surface, 3, 3, 5, 3);
	GetCharacterManage()->AddCharacterParent(character2);

	GuiPopup* guipopup1 = new GuiPopup(2*  TILE_SIZE, 2*  TILE_SIZE);
	guipopup1->SetVisible(FALSE);

	GuiPopup* guipopup2 = new GuiPopup(2*  TILE_SIZE, 2*  TILE_SIZE);
	guipopup2->SetVisible(FALSE);

	SDL_Surface* menu_surface1 = LoadImg("menu_move.png");
	SDL_Surface* menu_surface1_1 = LoadImg("menu_move_over.png");

	SDL_Surface* menu_surface2 = LoadImg("menu_attack.png");
	SDL_Surface* menu_surface2_1 = LoadImg("menu_attack_over.png");

	SDL_Surface* menu_surface3 = LoadImg("menu_info.png");
	SDL_Surface* menu_surface3_1 = LoadImg("menu_info_over.png");

	CButton<Character>* guibutton1 = new CButton<Character>(2*  TILE_SIZE, 2*  TILE_SIZE, menu_surface1, menu_surface1_1, &Character::Move, character1);
	guipopup1->AddGui(guibutton1);
	CButton<Character>* guibutton2 = new CButton<Character>(2*  TILE_SIZE, 2*  TILE_SIZE, menu_surface2, menu_surface2_1, &Character::Attack, character1);
	guipopup1->AddGui(guibutton2);
	CButton<Character>* guibutton3 = new CButton<Character>(2*  TILE_SIZE, 2*  TILE_SIZE, menu_surface3, menu_surface3_1, &Character::Info, character1);
	guipopup1->AddGui(guibutton3);
	character1->SetGui(guipopup1);

	GetGuiManager()->AddGui(guipopup1);

	CButton<Character>* guibutton1_1 = new CButton<Character>(2*  TILE_SIZE, 2*  TILE_SIZE, menu_surface1, menu_surface1_1, &Character::Move, character2);
	guipopup2->AddGui(guibutton1_1);
	CButton<Character>* guibutton2_1 = new CButton<Character>(2*  TILE_SIZE, 2*  TILE_SIZE, menu_surface2, menu_surface2_1, &Character::Attack, character2);
	guipopup2->AddGui(guibutton2_1);
	CButton<Character>* guibutton3_1 = new CButton<Character>(2*  TILE_SIZE, 2*  TILE_SIZE, menu_surface3, menu_surface3_1, &Character::Info, character2);
	guipopup2->AddGui(guibutton3_1);
	character2->SetGui(guipopup2);

	GetGuiManager()->AddGui(guipopup2);

	surface = LoadImg("midnight.png");
	m_pLogoGui = new GuiImage(0, 0, surface);

	surface = LoadImg("호날두.png");
	Npc* npc = new Npc(3, surface, 7, 5, 3, 3);
	GetCharacterManage()->AddCharacterParent(npc);
}

CGameMain::~CGameMain()
{

}

void CGameMain::Act()
{
	
}

void CGameMain::Draw()
{
	GetTileManage()->Draw();
	GetCharacterManage()->Draw();
	DrawCursor();

	if(m_pSelectCharacter)
	{
		GetGameMain()->DrawSelectCursor(m_pSelectCharacter->GetDestRect());

		if(m_pSelectCharacter->isMove())
		{
			m_pSelectCharacter->DrawMoveArea();			
		}

		if(m_pSelectCharacter->isAttack())
		{
			m_pSelectCharacter->DrawAttackArea();
		}
	}

	GetGuiManager()->Draw();

	SDL_Rect rectsurface = {0 + m_nScrollX, 0 + m_nScrollY, 640 + m_nScrollX, 480 + m_nScrollY};
	Blit(m_BackSurface, &rectsurface, 0, 0);

	SDL_Surface* surface = m_Font->SetText("MousePos x : %d, y : %d", m_nMouseX, m_nMouseY);
	if(surface)
	{
		Blit(surface, 20, 30);
	}
	Flip();
}

void CGameMain::DrawCursor()
{
	if(isShowCursor())
	{
		SDL_Rect destrect = {(m_nScrollX + m_nMouseX) / TILE_SIZE*  TILE_SIZE,  (m_nScrollY + m_nMouseY) / TILE_SIZE*  TILE_SIZE, (m_nScrollX + m_nMouseX) / TILE_SIZE*  TILE_SIZE + TILE_SIZE,  (m_nScrollY + m_nMouseY) / TILE_SIZE*  TILE_SIZE + TILE_SIZE};
		DrawBackSurface(m_pTileCursor->GetSurface(), m_pTileCursor->GetRect(), &destrect);
	}
}

void CGameMain::DrawSelectCursor(SDL_Rect* dstrect)
{
	DrawBackSurface(m_pTileSelect->GetSurface(), m_pTileSelect->GetRect(), dstrect);
}

void CGameMain::DrawAttackableTile(SDL_Rect* destrect)
{
	DrawBackSurface(m_pTileRed->GetSurface(), m_pTileRed->GetRect(), destrect);
}

void CGameMain::DrawMoveableTile(SDL_Rect* destrect)
{
	int iTileX = destrect->x / TILE_SIZE;
	int iTileY = destrect->y / TILE_SIZE;
	if(GetCharacterManage()->GetCharacterParent(iTileX, iTileY))
		return;

	DrawBackSurface(m_pTileWhite->GetSurface(), m_pTileWhite->GetRect(), destrect);
}

bool CGameMain::isShowCursor()
{
	if(m_pSelectCharacter && m_pSelectCharacter->isMenu()){
		return FALSE;
	}
	return TRUE;
}

void CGameMain::Scroll()
{
	if(m_nMouseX < 30)
	{
		m_nScrollX -= SCROLL_VALUE;
	}
	else if(610 < m_nMouseX)
	{
		m_nScrollX += SCROLL_VALUE;
	}
	if(m_nMouseY < 30)
	{
		m_nScrollY -= SCROLL_VALUE;
	}
	else if(450 < m_nMouseY)
	{
		m_nScrollY += SCROLL_VALUE;
	}

	if(m_nScrollX < 0)
	{
		m_nScrollX = 0;
	}
	else if(MAX_SCROLL_X - GetWidth() < m_nScrollX)
	{
		m_nScrollX = MAX_SCROLL_X - GetWidth();
	}

	if(m_nScrollY < 0)
	{
		m_nScrollY = 0;
	}
	else if(MAX_SCROLL_Y - GetHeight() < m_nScrollY)
	{
		m_nScrollY = MAX_SCROLL_Y - GetHeight();
	}
}

void CGameMain::DrawBackSurface(SDL_Surface* surface, SDL_Rect* srcrect, SDL_Rect* dstrect)
{
	Blit(surface, srcrect, m_BackSurface, dstrect);
}

void CGameMain::KeyUp(int keyvalue)
{
	SDLMain::KeyUp(keyvalue);

	if(keyvalue == SDLK_RETURN)
	{
		SetInputMode(false);
		SetFadeOut();
	}

	if(keyvalue == SDLK_SPACE)
	{
		SetFadeOut();
		SetInputMode(false); 
		GetGuiManager()->SetPreemitiveGui(m_pLogoGui);
	}

	if(keyvalue == SDLK_ESCAPE)
	{
		GetGuiManager()->SetPreemitiveGui(NULL);
	}
}

void CGameMain::UnselectCharacter()
{
	if(m_pSelectCharacter){
		m_pSelectCharacter->SetCharacterState(CHARACTERSTATE_NONE);
		m_pSelectCharacter = NULL;
	}
}

void CGameMain::Damage()
{
	if(m_pEffectCharacter)
		m_pEffectCharacter->SetDamage(true);

	static int i = 0;
	i += 5;
	if(50 <= i)
	{
		i = 0;
		EffectEnd();
	}
}

void CGameMain::EffectEnd()
{
	if(m_pEffectCharacter)
	{
		m_pEffectCharacter->SetDamage(false);
		m_pEffectCharacter = NULL;
	}

	__super::EffectEnd();
}

void CGameMain::MouseMove(int x, int y)
{
	SDLMain::MouseMove(x, y);

	Scroll();
}

void CGameMain::MouseButtonDown(MOUSE_BUTTON eMouseButton, int x, int y)
{
	if(eMouseButton == MOUSEBUTTON_LEFT)
	{
		int iTileX = (m_nScrollX + x) / TILE_SIZE;
		int iTileY = (m_nScrollY + y) / TILE_SIZE;
		if(m_pSelectCharacter == NULL)
		{
			m_pSelectCharacter = GetCharacterManage()->SelectCharacter(iTileX, iTileY);
			if(m_pSelectCharacter)
			{
				m_pSelectCharacter->SetCharacterState(CHARACTERSTATE_MENU);
				return;
			}
		}

		if(m_pSelectCharacter)
		{
			CharacterParent* pcCharacterParent = GetCharacterManage()->GetCharacterParent(iTileX, iTileY);
			if(m_pSelectCharacter->isAttack() && GetCharacterManage()->isValidArea(m_pSelectCharacter, pcCharacterParent, m_pSelectCharacter->GetAttackableTile()))
			{
				m_pEffectCharacter = pcCharacterParent;
				SetEffect((EffectFuncPtr)(&CGameMain::Damage));
				return;
			}

			if(GetCharacterManage()->MoveCharacterParent(m_pSelectCharacter, iTileX, iTileY))
			{
				UnselectCharacter();
			}
			return;
		}
	}
	else if(eMouseButton == MOUSEBUTTON_RIGHT)
	{
		UnselectCharacter();
	}
}