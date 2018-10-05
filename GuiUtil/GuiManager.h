#pragma once

#include "GuiParent.h"
#include "Map.h"
#include <vector>
#include <queue>
#include "Singleton.h"

class GuiManager : public CSingleton<GuiManager>
{
protected:
	GuiParent* m_pFocusGui;
	GuiParent* m_pPreemitiveGui;
	CMap<int, GuiParent*> m_mapGuiParent;

	std::vector<GuiParent*> m_vGuiParent;
	std::vector<GuiParent*>::iterator it;
	std::vector<GuiParent*>::reverse_iterator reverse_it;
	bool m_bPreemitiveMode;
	int& m_ScrollX;
	int& m_ScrollY;
	std::queue<int>m_qIdx;

public:
	GuiManager(int& ScrollX, int& ScrollY, bool bPreemitiveMode);
	virtual ~GuiManager();

	int GetIdx(){
		if(m_qIdx.empty()){
			return -1;
		}
		int idx = m_qIdx.front();
		m_qIdx.pop();
		return idx;
	}
	bool AddGui(GuiParent* guiparent);
	bool RemoveGui(int idx);
	void SetPreemitiveMode(bool bPreemitiveMode){m_bPreemitiveMode = bPreemitiveMode;}
	void SetPreemitiveGui(GuiParent* gui){
		m_pPreemitiveGui = gui;
		if(m_pPreemitiveGui)
		{
			SetPreemitiveMode(true);
		}
		else
		{
			SetPreemitiveMode(false);
		}
	}

	virtual bool PreemitiveDraw(); //선점 그리기 모드. 

	void AdjustPos(int &x, int &y);

	void SetMouseOver(GuiParent* gui); //파라미터로 넘긴 gui 만 키고 나머진 모두 꺼! 이 함수 호출하면 it 바뀐다. 호출 하고 나면 루프 돌지 말자

	virtual bool MouseButtonDown(MOUSE_BUTTON MouseButton, int x, int y);
	virtual bool MouseButtonUp(MOUSE_BUTTON MouseButton,int x, int y);

	virtual bool KeyDown(int keyvalue);
	virtual bool KeyUp(int keyvalue);
	virtual bool MouseMove(int x, int y); //마우스 움직임

	virtual void Draw();

	GuiParent* GetGui(int idx);
};

inline GuiManager* GetGuiManager()
{
	return GuiManager::GetInstancePtr() ;
}