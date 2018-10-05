#include "TileManage.h"
#include "GameMain.h"

CTileManage::CTileManage(int tilexsize, int tileysize)
{
	m_nTileXSize = tilexsize;
	m_nTileYSize = tileysize;
}

CTileManage::~CTileManage()
{
	m_mapTile.FreePtr();
}

CTile*  CTileManage::AddTile(int idx, SDL_Surface* surface)
{
	CTile*  tile = new CTile(idx, surface);
	if(m_mapTile.Add(tile->GetIdx(), tile))
	{
		return tile;
	}
	delete tile;
	return NULL;
}

bool CTileManage::RemoveTile(int tileidx)
{
	return m_mapTile.RemovePtr(tileidx);
}

CTile* CTileManage::GetTile(int idx)
{
	CTile* tile;
	if(m_mapTile.Get(idx, &tile))
	{
		return tile;
	}
	return NULL;
}

void CTileManage::Draw()
{
	for(int x = 0; x < m_nTileXSize; x++)
	{
		for(int y = 0; y < m_nTileYSize; y++)
		{
			CTile* tile = GetTile(1);
			if(tile)
			{
				SDL_Rect destrect = {x*  tile->GetWidth(), y*  tile->GetHeight(), (x*  tile->GetWidth()) + tile->GetWidth(), (y*  tile->GetHeight()) + tile->GetHeight()};
				GetGameMain()->DrawBackSurface(tile->GetSurface(), tile->GetRect(), &destrect);
			}
			else
			{
				return;
			}
		}
	}
}