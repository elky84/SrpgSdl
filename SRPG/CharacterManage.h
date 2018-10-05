#pragma once

#include "Map.h"
#include "CharacterParent.h"

class CharacterManage
{
	CharacterParent* m_pSelectCharacterParent;

	CMap<int, CharacterParent*>m_mapCharacterParent;
	std::map<int, CharacterParent*>::iterator it;
public:
	CharacterManage();
	~CharacterManage();

	void SetSelectCharacterParent(CharacterParent* characterparent){m_pSelectCharacterParent = characterparent;}

	bool AddCharacterParent(CharacterParent* characterparent);
	bool RemoveCharacterParent(int characternumber);
	void Draw();

	CharacterParent* GetCharacterParent(int tilex, int tiley);
	bool MoveCharacterParent(CharacterParent* characterparent, int tilex, int tiley);
	CharacterParent* SelectCharacter(int tilex, int tiley);

	bool isValidArea(CharacterParent* character1, CharacterParent* character2, int area);
	static CharacterManage* GetInstancePtr(){
		static CharacterManage charactermanage;
		return &charactermanage;
	}
};

inline CharacterManage* GetCharacterManage()
{
	return CharacterManage::GetInstancePtr() ;
}