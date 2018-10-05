#pragma once

#include "GuiParent.h"

template<typename T> class GuiButton : public GuiParent
{
	T* m_pTemplateClass;
	void (T::*m_ActFunc)();
public:
	GuiButton(int x, int y, int width, int height, void (T::*actfunc)(), T* templateclass) : GuiParent(x, y, width, height), m_ActFunc(actfunc), m_pTemplateClass(templateclass)
	{
	}

	virtual void Draw() = 0;
	virtual bool MouseButtonDown(MOUSE_BUTTON MouseButton, int x, int y)
	{
		if(MouseButton == MOUSEBUTTON_LEFT)
		{
			if(m_ActFunc)
			{
				(m_pTemplateClass->*m_ActFunc)();
			}
		}
		return TRUE;	
	}
};