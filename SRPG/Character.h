#pragma once

#include "CharacterParent.h"

class Character : public CharacterParent
{
	GuiParent* m_pGui;
	
public:
	Character(int characternumber, SDL_Surface* tilesurface, int tilex, int tiley, int moveabletile = 3, int attackabletile = 5);
	virtual ~Character();

	void SetGui(GuiParent* gui){
		m_pGui = gui;
	}

	virtual void SetCharacterState(CHARACTER_STATE characterstate){
		switch(characterstate)
		{
		case CHARACTERSTATE_MENU:
			if(m_pGui)
			{
				m_pGui->SetX(GetTileX()*  GetWidth() + GetWidth());
				m_pGui->SetY(GetTileY()*  GetHeight());
				m_pGui->SetVisible(TRUE);
			}
			break;
		case CHARACTERSTATE_MOVE:
			if(m_pGui)
			{
				m_pGui->SetVisible(FALSE);
			}
			break;
		case CHARACTERSTATE_ATTACK:
		case CHARACTERSTATE_INFO:
		case CHARACTERSTATE_NONE:
			if(m_pGui)
			{
				m_pGui->SetVisible(FALSE);
			}
			break;
		}
		__super::SetCharacterState(characterstate);
	}

	virtual bool isSelect(){return true;}
};