#pragma once
class CTexture;

class  CCore
{
	SINGLE(CCore)
private:
	HWND m_hWnd; // ���� ������ �ڵ�
	POINT m_ptResolution; // ���� ������ �ػ�
	HDC m_hDC; // ���� �����쿡 Draw �� DC

	CTexture* m_pMemTex; // ����� �ؽ���


	// ���� ����ϴ� GDI Object
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
