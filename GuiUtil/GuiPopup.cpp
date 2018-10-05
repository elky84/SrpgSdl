#include "GuiPopup.h"

GuiPopup::GuiPopup(int x, int y) 
: GuiGroup(x, y, 0, 0)
{
	
}

GuiPopup::~GuiPopup()
{
	m_mapGuiList.FreePtr();
}

bool GuiPopup::AddGui(GuiParent* gui)
{
	if(!m_mapGuiList.Exist(gui->GetIdx()))
	{
		if(GetWidth() < gui->GetWidth())
		{
			SetWidth(gui->GetWidth());
		}

		SetHeight(GetHeight() + gui->GetHeight());
		return m_mapGuiList.Add(gui->GetIdx(), gui);
	}
	delete gui;
	return false;
}