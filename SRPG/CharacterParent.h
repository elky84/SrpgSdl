#pragma once

#include "SDLVideo.h"
#include "GuiParent.h"

enum CHARACTER_STATE{
	CHARACTERSTATE_NONE = -1,
	CHARACTERSTATE_MENU,
	CHARACTERSTATE_MOVE,
	CHARACTERSTATE_ATTACK,
	CHARACTERSTATE_INFO,
};

class CharacterParent
{
	int m_nCharacterNumber;
	CHARACTER_STATE m_CharacterState;
	SDL_Surface* m_TileSurface;
	int m_nTileX, m_nTileY; //X, Y 타일 좌표
	int m_nMoveableTile; //이동 가능 타일 크기
	int m_nAttackableTile; //이동 가능 타일 크기
	SDL_Rect m_Rect;
	SDL_Rect m_DestRect;
	bool m_bDamaged;
public:
	CharacterParent(int characternumber, SDL_Surface* tilesurface, int tilex, int tiley, int moveabletile = 3, int attackabletile = 5);
	virtual ~CharacterParent();

	virtual void SetCharacterState(CHARACTER_STATE charactertype){
		m_CharacterState = charactertype;
	}

	virtual void SetDamage(bool bDamage);

	virtual void Draw();
	virtual void DrawAttackArea();
	virtual void DrawMoveArea();

	int GetCharacterNumber(){return m_nCharacterNumber;}

	int GetWidth(){return m_TileSurface->w;}
	int GetHeight(){return m_TileSurface->h;}

	int GetTileX(){return m_nTileX;}
	int GetTileY(){return m_nTileY;}
	SDL_Surface*  GetTileSurface(){return m_TileSurface;}
	SDL_Rect* GetRect(){return &m_Rect;}
	SDL_Rect* GetDestRect(){return &m_DestRect;}

	void ReCalcDestRect(){
		m_DestRect.x = m_nTileX*  m_TileSurface->w;
		m_DestRect.y = m_nTileY*  m_TileSurface->h;
		m_DestRect.w = m_nTileX*  m_TileSurface->w + m_TileSurface->w;
		m_DestRect.h = m_nTileY*  m_TileSurface->h + m_TileSurface->h;
	}

	void SetTilePos(int x, int y){
		m_nTileX = x;
		m_nTileY = y;
		ReCalcDestRect();
	}

	virtual bool isSelect() = 0;

	void Move(){SetCharacterState(CHARACTERSTATE_MOVE);}
	void Attack(){SetCharacterState(CHARACTERSTATE_ATTACK);}
	void Info(){SetCharacterState(CHARACTERSTATE_INFO);}

	CHARACTER_STATE GetCharacterState(){return m_CharacterState;}
	bool isMove(){
		if(m_CharacterState == CHARACTERSTATE_MOVE){
			return TRUE;
		}
		return FALSE;
	}

	bool isAttack(){
		if(m_CharacterState == CHARACTERSTATE_ATTACK){
			return TRUE;
		}
		return FALSE;
	}

	bool isInfo(){
		if(m_CharacterState == CHARACTERSTATE_INFO){
			return TRUE;
		}
		return FALSE;
	}

	bool isMenu(){
		if(m_CharacterState == CHARACTERSTATE_MENU){
			return TRUE;
		}
		return FALSE;
	}

	int GetMoveableTile(){return m_nMoveableTile;}
	int GetAttackableTile(){return m_nAttackableTile;}

	bool isDamaged(){return m_bDamaged;}
};