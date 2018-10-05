#pragma once

#include "Map.h"
#include "Tile.h"
#include "Singleton.h"

class CTileManage : public CSingleton<CTileManage>
{
	int m_nTileXSize, m_nTileYSize;
	CMap<int, CTile*>m_mapTile;
	std::map<int, CTile*>::iterator it;
public:
	CTileManage(int tilexsize, int tileysize);
	~CTileManage();

	CTile* AddTile(int idx, SDL_Surface* surface);
	bool RemoveTile(int tileidx);
	CTile* GetTile(int idx);
	void Draw();
};

inline CTileManage* GetTileManage()
{
	return CTileManage::GetInstancePtr() ;
}