#include "GuiGroup.h"

GuiGroup::GuiGroup(int x, int y, int width, int height) 
: GuiParent(x, y, width, height)
{

}

GuiGroup::~GuiGroup()
{
	m_mapGuiList.FreePtr();
}

void GuiGroup::Draw()
{
	for(it = m_mapGuiList.m_Map.begin(); it != m_mapGuiList.m_Map.end(); ++it)
	{
		GuiParent* gui = it->second;
		gui->Draw();
	}
}

bool GuiGroup::MouseButtonDown(MOUSE_BUTTON MouseButton, int x, int y)
{
	for(it = m_mapGuiList.m_Map.begin(); it != m_mapGuiList.m_Map.end(); ++it)
	{
		GuiParent* gui = it->second;
		if(gui->isValidArea(x, y))
		{
			if(gui->MouseButtonDown(MouseButton, x, y))
			{
				SetVisible(false);
				return true;
			}
		}
	}
	return false;
}

bool GuiGroup::MouseMove(int x, int y)
{
	for(it = m_mapGuiList.m_Map.begin(); it != m_mapGuiList.m_Map.end(); ++it)
	{
		GuiParent* gui = it->second;
		if(gui->isValidArea(x, y))
		{
			if(gui->MouseMove(x, y))
			{
				SetMouseOver(gui);
				return true;
			}
		}
	}
	SetMouseOver((GuiParent*)NULL);
	return false;
}

void GuiGroup::SetMouseOver(GuiParent* mouseovergui)
{
	for(it = m_mapGuiList.m_Map.begin(); it != m_mapGuiList.m_Map.end(); ++it)
	{
		GuiParent* gui = it->second;
		if(gui == mouseovergui){
			gui->SetMouseOver(true);
		}
		else{
			gui->SetMouseOver(false);
		}
	}
}

void GuiGroup::SetMouseOver(bool bMouseOver)
{
	if(bMouseOver == false)
	{
		SetMouseOver((GuiParent*)NULL);
	}
}

bool GuiGroup::AddGui(GuiParent* gui)
{
	if(!m_mapGuiList.Exist(gui->GetIdx()))
	{
		return m_mapGuiList.Add(gui->GetIdx(), gui);
	}
	return false;
}

void GuiGroup::SetX(int x)
{
	GuiParent::SetX(x);
	for(it = m_mapGuiList.m_Map.begin(); it != m_mapGuiList.m_Map.end(); ++it)
	{
		GuiParent* gui = it->second;
		gui->SetX(x);
	}
}

void GuiGroup::SetY(int y)
{
	GuiParent::SetY(y);
	for(it = m_mapGuiList.m_Map.begin(); it != m_mapGuiList.m_Map.end(); ++it)
	{
		GuiParent* gui = it->second;
		gui->SetY(y);
		y += gui->GetHeight();
	}
}