#include "GuiManager.h"

GuiManager::GuiManager(int& ScrollX, int& ScrollY, bool bPreemitiveMode)
: m_ScrollX(ScrollX)
, m_ScrollY(ScrollY)
{
	for(int i = 0; i < 10000; i++)
		m_qIdx.push(i);

	m_bPreemitiveMode = bPreemitiveMode;
	m_pPreemitiveGui = NULL;
	m_pFocusGui = NULL;
}

GuiManager::~GuiManager()
{
	m_mapGuiParent.FreePtr();
}

void GuiManager::AdjustPos(int &x, int &y)
{
	if(!m_bPreemitiveMode)
	{
		x += m_ScrollX;
		y += m_ScrollY;
	}
}

bool GuiManager::AddGui(GuiParent* guiparent)
{
	if(!m_mapGuiParent.Exist(guiparent->GetIdx()))
	{
		m_vGuiParent.push_back(guiparent);
		return m_mapGuiParent.Add(guiparent->GetIdx(), guiparent);
	}
	delete guiparent;
	return false;
}

bool GuiManager::RemoveGui(int idx)
{
	for(it = m_vGuiParent.begin(); it != m_vGuiParent.end(); ++it)
	{
		GuiParent* guiparent = (*it);
		if(guiparent->GetIdx() == idx){
			m_qIdx.push(idx);
			m_vGuiParent.erase(it);
			return m_mapGuiParent.RemovePtr(idx);
		}
	}
	return false;
}

bool GuiManager::PreemitiveDraw() //선점 그리기 모드. 선점 그리기 Gui가 던져 진게 있다면, 그것만 그린다.
{
	if(m_pPreemitiveGui)
	{
		m_pPreemitiveGui->Draw();
		return true;
	}
	return false;
}

void GuiManager::Draw() //늦게 들어온 애들 먼저 그려~~ 
{
	for(reverse_it = m_vGuiParent.rbegin(); reverse_it != m_vGuiParent.rend(); ++reverse_it)
	{
		GuiParent* guiparent = (*reverse_it);
		if(guiparent->isVisible())
			guiparent->Draw();
	}
}

bool GuiManager::MouseMove(int x, int y) //늦게 들어온 애들 먼저 그려~~ 
{
	AdjustPos(x,y);
	if(m_pPreemitiveGui) return m_pPreemitiveGui->MouseMove(x, y);
	for(it = m_vGuiParent.begin(); it != m_vGuiParent.end(); ++it)
	{
		GuiParent* guiparent = (*it);
		if(guiparent->isValidArea(x, y)){
			if(guiparent->MouseMove(x, y))
			{
				SetMouseOver(guiparent); 
				return true;
			}
		}
	}
	SetMouseOver(NULL);
	return false;
}

void GuiManager::SetMouseOver(GuiParent* gui)
{
	for(it = m_vGuiParent.begin(); it != m_vGuiParent.end(); ++it)
	{
		GuiParent* guiparent = (*it);
		if(guiparent == gui){
			guiparent->SetMouseOver(true);
		}
		else{
			guiparent->SetMouseOver(false);
		}
	}
}

bool GuiManager::KeyDown(int keyvalue)
{
	if(m_pPreemitiveGui) return m_pPreemitiveGui->KeyDown(keyvalue);

	for(it = m_vGuiParent.begin(); it != m_vGuiParent.end(); ++it)
	{
		GuiParent* guiparent = (*it);
		if(guiparent->KeyDown(keyvalue))
			return true;
	}
	return false;
}

bool GuiManager::KeyUp(int keyvalue)
{
	if(m_pPreemitiveGui) return m_pPreemitiveGui->KeyUp(keyvalue);

	for(it = m_vGuiParent.begin(); it != m_vGuiParent.end(); ++it)
	{
		GuiParent* guiparent = (*it);
		if(guiparent->KeyUp(keyvalue))
			return true;
	}
	return false;
}

bool GuiManager::MouseButtonUp(MOUSE_BUTTON MouseButton, int x, int y)
{
	AdjustPos(x,y);

	if(m_pPreemitiveGui) return m_pPreemitiveGui->MouseButtonUp(MouseButton, x, y);

	for(it = m_vGuiParent.begin(); it != m_vGuiParent.end(); ++it)
	{
		GuiParent* guiparent = (*it);
		if(guiparent->isValidArea(x, y)){
			if(guiparent->MouseButtonUp(MouseButton, x, y)){
				return true;
			}
		}
	}
	return false;
}

bool GuiManager::MouseButtonDown(MOUSE_BUTTON MouseButton, int x, int y)
{
	AdjustPos(x,y);

	if(m_pPreemitiveGui) return m_pPreemitiveGui->MouseButtonDown(MouseButton, x, y);

	for(it = m_vGuiParent.begin(); it != m_vGuiParent.end(); ++it)
	{
		GuiParent* guiparent = (*it);
		if(guiparent->isValidArea(x, y)){
			if(guiparent->MouseButtonDown(MouseButton, x, y)){
				return true;
			}
		}
	}
	return false;
}



GuiParent*  GuiManager::GetGui(int idx)
{
	GuiParent* guiparent;
	if(m_mapGuiParent.Get(idx, &guiparent))
	{
		return guiparent;
	}
	return NULL;
}