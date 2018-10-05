#pragma once

#include "GuiCommon.h"

class GuiParent
{
private:
	int m_nIdx;

protected:
	bool m_bMouseOver;
	bool m_bVisible;
	int m_nX, m_nY;
	int m_nWidth, m_nHeight;
public:
	GuiParent(int x, int y, int width, int height, bool bVisible = true);
	virtual ~GuiParent();

	void SetVisible(bool visible){m_bVisible = visible;} //자신이 보이는 상태 여부 세팅
	bool isVisible(){return m_bVisible;}
	int GetIdx(){return m_nIdx;}
	int GetX(){return m_nX;}
	int GetY(){return m_nY;}
	virtual void SetX(int x){m_nX = x;}
	virtual void SetY(int y){m_nY = y;}
	int GetHeight(){return m_nHeight;}
	int GetWidth(){return m_nWidth;}

	virtual void SetMouseOver(bool bMouseOver){
		m_bMouseOver = bMouseOver;
	}

	bool isValidArea(int x, int y){
		if(m_bVisible && m_nX <= x && x <= m_nX + m_nWidth &&
			m_nY <= y && y <= m_nY + m_nHeight)
		{
			return true;
		}
		return false;
	}

	void SetWidth(int width) {m_nWidth = width;}
	void SetHeight(int height){m_nHeight = height;}

	virtual bool MouseMove(int x, int y){
		if(isValidArea(x, y)){
			return true;
		}
		return false;
	} //마우스 움직임

	virtual bool MouseButtonDown(MOUSE_BUTTON MouseButton, int x, int y){return false;}
	virtual bool MouseButtonUp(MOUSE_BUTTON MouseButton, int x, int y){return false;}
	virtual bool KeyDown(int keyvalue){return false;}
	virtual bool KeyUp(int keyvalue){return false;}
	virtual void Draw() = 0;
};