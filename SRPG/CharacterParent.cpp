#include "CharacterParent.h"
#include <math.h>
#include "GameMain.h"

CharacterParent::CharacterParent(int characternumber, SDL_Surface* tilesurface, int tilex, int tiley, int moveabletile /* = 3*/, int attackabletile /* = 5*/)
{
	m_nCharacterNumber = characternumber;
	m_TileSurface = tilesurface;
	m_nTileX = tilex;
	m_nTileY = tiley;
	m_nMoveableTile = moveabletile;
	m_nAttackableTile = attackabletile;
	m_CharacterState = CHARACTERSTATE_NONE;
	m_Rect.x = 0;
	m_Rect.y = 0;
	m_Rect.w = tilesurface->w;
	m_Rect.h = tilesurface->h;
	m_DestRect.x = tilex*  m_TileSurface->w;
	m_DestRect.y = tiley*  m_TileSurface->h;
	m_DestRect.w = tilex*  m_TileSurface->w + m_TileSurface->w;
	m_DestRect.h = tiley*  m_TileSurface->h + m_TileSurface->h;
	m_bDamaged = false;
}

CharacterParent::~CharacterParent()
{

}

void CharacterParent::Draw()
{
	if(m_bDamaged)
	{
		int iRandX = (rand() % 20) - 10;
		int iRandY = (rand() % 20) - 10;	
		m_DestRect.x = m_nTileX*  m_TileSurface->w + iRandX;
		m_DestRect.y = m_nTileY*  m_TileSurface->h + iRandY;
		m_DestRect.w = m_nTileX*  m_TileSurface->w + m_TileSurface->w + iRandX;
		m_DestRect.h = m_nTileY*  m_TileSurface->h + m_TileSurface->h + iRandY;
	}
	GetGameMain()->DrawBackSurface(GetTileSurface(), GetRect(), &m_DestRect);
}

void CharacterParent::SetDamage(bool bDamage)
{
	if(bDamage == false)
	{
		ReCalcDestRect();
	}
	m_bDamaged = bDamage;
}

void CharacterParent::DrawAttackArea()
{
	for(int x = -m_nAttackableTile; x < m_nAttackableTile; x++)
	{
		for(int y = -m_nAttackableTile; y < m_nAttackableTile; y++)
		{
			if(abs(x) + abs(y) == 0)
				continue;

			if(abs(x) + abs(y) < m_nAttackableTile)
			{
				SDL_Rect destrect = {(m_nTileX + x)*  GetWidth(), (m_nTileY + y)*  GetHeight(), (m_nTileX + x)*  GetWidth() + GetWidth(), (m_nTileY + y)*  GetHeight() + GetHeight()};
				GetGameMain()->DrawAttackableTile(&destrect);
			}
		}
	}
}

void CharacterParent::DrawMoveArea()
{
	for(int x = -m_nMoveableTile; x < m_nMoveableTile; x++)
	{
		for(int y = -m_nMoveableTile; y < m_nMoveableTile; y++)
		{
			if(abs(x) + abs(y) == 0)
				continue;

			if(abs(x) + abs(y) < m_nMoveableTile)
			{
				SDL_Rect destrect = {(m_nTileX + x)*  GetWidth(), (m_nTileY + y)*  GetHeight(), (m_nTileX + x)*  GetWidth() + GetWidth(), (m_nTileY + y)*  GetHeight() + GetHeight()};
				GetGameMain()->DrawMoveableTile(&destrect);
			}
		}
	}
}