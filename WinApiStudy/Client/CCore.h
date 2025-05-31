#pragma once
class CTexture;

class  CCore
{
	SINGLE(CCore)
private:
	HWND m_hWnd; // 메인 윈도우 핸들
	POINT m_ptResolution; // 메인 윈도우 해상도
	HDC m_hDC; // 메인 윈도우에 Draw 할 DC

	CTexture* m_pMemTex; // 백버퍼 텍스쳐


	// 자주 사용하는 GDI Object
	HBRUSH m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN m_arrPen[(UINT)PEN_TYPE::END];

private:
	void Clear();
	void CreateBrushPen();

public:
	int Init(HWND _hWnd, POINT _ptResolution);
	void Update();

public:
	HWND GetMainHwnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }
	POINT GetResolution() { return m_ptResolution; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }
};
