#pragma once

#include "GuiParent.h"
#include "Map.h"

class GuiGroup : public GuiParent
{
protected:
	CMap<int, GuiParent*> m_mapGuiList;
	std::map<int, GuiParent*>::iterator it;
public:
	GuiGroup(int x, int y, int width, int height);
	virtual ~GuiGroup();

	bool AddGui(GuiParent* gui);

	virtual void SetX(int x);
	virtual void SetY(int y);

	virtual void Draw();
	virtual bool MouseButtonDown(MOUSE_BUTTON MouseButton, int x, int y);
	virtual bool MouseMove(int x, int y);
	void SetMouseOver(GuiParent* mouseovergui);

	virtual void SetMouseOver(bool bMouseOver);
};