#include "CButtonUI.h"

CButtonUI::CButtonUI() : CUI(false), m_pFunc(nullptr), m_param1(0), m_param2(0), m_pSceneInst(nullptr), m_pSceneFunc(nullptr)
{
}

CButtonUI::~CButtonUI()
{
}


void CButtonUI::MouseOn()
{
}

void CButtonUI::MouseLbtnDown()
{
}

void CButtonUI::MouseLbtnUp()
{
}

void CButtonUI::MouseLbtnClicked()
{
	if (nullptr != m_pFunc)
	{
		m_pFunc(m_param1, m_param2);
	}

	if (m_pSceneInst && m_pSceneFunc)
	{
		((*m_pSceneInst).*m_pSceneFunc)();
	}
}

void CButtonUI::SetClickedCallBack(CScene* _pScene, SCENE_MEMFUC _pSceneFunc)
{
	m_pSceneInst = _pScene;
	m_pSceneFunc = _pSceneFunc;
}


