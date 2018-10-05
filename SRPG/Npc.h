#pragma once

#include "CharacterParent.h"

class Npc : public CharacterParent
{
public:
	Npc(int characternumber, SDL_Surface* tilesurface, int tilex, int tiley, int moveabletile = 3, int attackabletile = 5);
	virtual ~Npc();

	virtual bool isSelect(){return false;}
};