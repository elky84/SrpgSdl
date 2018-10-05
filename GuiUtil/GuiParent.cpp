#include "GuiParent.h"
#include "GuiManager.h"

GuiParent::GuiParent(int x, int y, int width, int height, bool bVisible)
{
	m_nIdx = GetGuiManager()->GetIdx();
	m_nX = x;
	m_nY = y;
	m_nWidth = width;
	m_nHeight = height;

	m_bVisible = bVisible;
	m_bMouseOver = false;
}

GuiParent::~GuiParent()
{

}