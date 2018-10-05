#pragma once

#include "GuiParent.h"
#include "GuiPopup.h"
#include "Map.h"

class GuiUtil
{
	CMap<int, GuiParent*>*m_pMapGuiList;
public:
	GuiUtil(CMap<int, GuiParent*>* mapguilist);
	~GuiUtil();

	GuiPopup* NewGuiPop(int guicount, GuiParent* guilist);
};