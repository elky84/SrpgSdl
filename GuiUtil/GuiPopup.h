#pragma once

#include "GuiGroup.h"
#include "Map.h"

class GuiPopup : public GuiGroup
{	
public:
	GuiPopup(int x, int y);
	virtual ~GuiPopup();

	bool AddGui(GuiParent* gui);
};