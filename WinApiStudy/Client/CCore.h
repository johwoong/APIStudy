#pragma once
class  CCore
{
	SINGLE(CCore)
private:
	HWND m_hWnd; // ���� ������ �ڵ�
	POINT m_ptResoulution; // ���� ������ �ػ�
	HDC m_hDC;

	HBITMAP m_hBit;
	HDC     m_memDC;

public:
	int Init(HWND _hWnd, POINT _ptResolution);
	void Update();


public:
	HWND GetMainHwnd() { return m_hWnd; }
};


