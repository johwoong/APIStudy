#include "CPanelUI.h"
#include "KeyManager.h"

CPanelUI::CPanelUI() : CUI(false)
{
}

CPanelUI::~CPanelUI()
{
}

void CPanelUI::update()
{
}

void CPanelUI::Render(HDC _dc)
{
	CUI::render(_dc);
}

void CPanelUI::MouseOn()
{
	if (IsLbnDown())
	{
		Vec2 vDiff = MOUSE_POS - m_vDragStart;

		Vec2 vCurPos = GetPos();
		vCurPos += vDiff;
		SetPos(vCurPos);

		m_vDragStart = MOUSE_POS;
	}
}

void CPanelUI::MouseLbtnDown()
{
	m_vDragStart = MOUSE_POS;

}

void CPanelUI::MouseLbtnUp()
{
}



