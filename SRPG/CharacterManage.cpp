#include "CharacterManage.h"
#include "GameMain.h"

CharacterManage::CharacterManage()
{
	m_pSelectCharacterParent = NULL;
}

CharacterManage::~CharacterManage()
{
	m_mapCharacterParent.FreePtr();
}

bool CharacterManage::AddCharacterParent(CharacterParent* characterparent)
{
	return m_mapCharacterParent.Add(characterparent->GetCharacterNumber(), characterparent);
}

bool CharacterManage::RemoveCharacterParent(int characternumber)
{
	return m_mapCharacterParent.RemovePtr(characternumber);
}

void CharacterManage::Draw()
{
	for(it = m_mapCharacterParent.m_Map.begin(); it != m_mapCharacterParent.m_Map.end(); ++it)
	{
		CharacterParent* characterparent = it->second;
		characterparent->Draw();
	}
}

CharacterParent* CharacterManage::GetCharacterParent(int tilex, int tiley)
{
	for(it = m_mapCharacterParent.m_Map.begin(); it != m_mapCharacterParent.m_Map.end(); ++it)
	{
		CharacterParent* characterparent = it->second;
		if(characterparent->GetTileX() == tilex && characterparent->GetTileY() == tiley)
		{
			return characterparent;
		}
	}
	return NULL;
}

bool CharacterManage::MoveCharacterParent(CharacterParent* characterparent, int tilex, int tiley)
{
	if(!characterparent->isMove())
		return false;

	if(GetCharacterParent(tilex, tiley))
		return false;

	if(abs(characterparent->GetTileX() - tilex) + abs(characterparent->GetTileY() - tiley) < characterparent->GetMoveableTile())
	{
		characterparent->SetTilePos(tilex, tiley);
		return true;
	}
	return false;
}

CharacterParent* CharacterManage::SelectCharacter(int tilex, int tiley)
{
	CharacterParent* characterparent = GetCharacterParent(tilex, tiley);
	if(characterparent && characterparent->isSelect())
	{
		return characterparent;
	}
	return NULL;
}

bool CharacterManage::isValidArea(CharacterParent* character1, CharacterParent* character2, int area)
{
	if(character1 == NULL || character2 == NULL)
		return false;

	if(character1 == character2)
		return false;

	if(area <= abs(character1->GetTileX() - character2->GetTileX()) + abs(character1->GetTileY() - character2->GetTileY()))
		return false;

	return true;
}