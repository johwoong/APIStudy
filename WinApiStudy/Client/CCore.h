#pragma once
class  CCore
{

	SINGLE(CCore);
private:
	HWND m_hWnd; // ���� ������ �ڵ�
	POINT m_ptResoulution; // ���� ������ �ػ�
	HDC m_hDC;

public:
	int Init(HWND _hWnd, POINT _ptResolution);
	void Update();

private:
	void update();
	void render();

private:
	CCore();
	~CCore();
};


