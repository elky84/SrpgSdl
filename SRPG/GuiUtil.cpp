#include "GuiUtil.h"

GuiUtil::GuiUtil(CMap<int, GuiParent*>* mapguilist)
{
	m_pMapGuiList = mapguilist;
}

GuiUtil::~GuiUtil()
{

}

GuiPopup* GuiUtil::NewGuiPop(int guicount, GuiParent* guilist)
{
	GuiPopup* guipopup = new GuiPopup(0, 0);
	for(int i = 0; i < guicount; i++)
	{
		guipopup->AddGui(&guilist[i]);
	}
	return guipopup;
}