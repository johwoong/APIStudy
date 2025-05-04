#include "pch.h"
#include "CCore.h"
#include "CObject.h"
CObject g_obj;

CCore::CCore() : m_hWnd(0), m_ptResoulution{}, m_hDC(0)
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);
}


int CCore::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResoulution = _ptResolution;
	// �ػ󵵿� �°� ������ ũ�� ����
	RECT rt = {0, 0, m_ptResoulution.x, m_ptResoulution.y};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd); // DCȰ���ؼ� �׸��� �׷�����

	g_obj.m_ptPos = POINT{ m_ptResoulution.x / 2, m_ptResoulution.y / 2};
	g_obj.m_ptScale = POINT{ 100, 100 };
	return 0;
}

void CCore::Update()
{
	static int callcount = 0;
	++callcount;
	static int iPrevCount = GetTickCount();

	int iCurCount = GetTickCount();
	if (iCurCount - iPrevCount > 1000) // 1�ʸ��� �ѹ��� ����
	{
		iPrevCount = iCurCount;
		callcount = 0;
	}
	update();
	render();
}

void CCore::update() // ��ü�� ������ üũ
{
	// �񵿱� Ű ����� �Լ� - Ű�� ������ ������ �ٷ�üũ
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		g_obj.m_ptPos.x -= 1;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		g_obj.m_ptPos.x += 1;
	}
}

void CCore::render() // ó���Ǵ¼ӵ�������
{	// �׸���
	Rectangle(m_hDC, g_obj.m_ptPos.x - g_obj.m_ptScale.x / 2, 
		g_obj.m_ptPos.y - g_obj.m_ptScale.y / 2,
		g_obj.m_ptPos.x + g_obj.m_ptScale.x / 2, 
		g_obj.m_ptPos.y + g_obj.m_ptScale.y / 2);
}
