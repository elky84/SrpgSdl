#include "Character.h"

Character::Character(int characternumber, SDL_Surface* tilesurface, int tilex, int tiley, int moveabletile /* = 3*/, int attackabletile /* = 5*/)
: CharacterParent(characternumber, tilesurface, tilex, tiley, moveabletile, attackabletile)
{
	m_pGui = NULL;
}

Character::~Character()
{
	SAFE_DELETE(m_pGui);
}