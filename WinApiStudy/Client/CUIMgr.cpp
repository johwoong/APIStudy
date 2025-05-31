#include "pch.h"
#include "CUIMgr.h"
#include "SceneManager.h"
#include "CScene.h"
#include "CUI.h"
#include "KeyManager.h"

CUIMgr::CUIMgr() : m_pFocusedUI(nullptr)
{

}

CUIMgr::~CUIMgr()
{

}

CUI* CUIMgr::GetFocusedUI()
{

	CScene* pCurScene = SceneManager::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	bool bLBtnTap = KEY_TAP(KEY::LBTN);

	// ���� ��Ŀ�� UI�� �޾Ƶΰ� ����Ǿ����� Ȯ���Ѵ�.
	CUI* pFocusedUI = m_pFocusedUI;

	if (!bLBtnTap)
	{
		return pFocusedUI;
	}

	// ���ʹ�ư TAP�� �߻��ߵ��� ����
	vector<CObject*>::iterator targetiter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (((CUI*)*iter)->IsMouseOn())
		{
			targetiter = iter;
		}
	}

	// �̹��� Focuse�� UI�� ����.
	if (vecUI.end() == targetiter)
	{
		return nullptr;
	}

	pFocusedUI = (CUI*)*targetiter;

	// ���� ������ �� �ڷ� ���� ��ü
	vecUI.erase(targetiter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}

void CUIMgr::update()
{
	// 1.FocusedUI Ȯ��
	m_pFocusedUI = GetFocusedUI();

	if (!m_pFocusedUI)
		return;

	// 2. FocusedUI ������, �θ� UI ����, �ڽ� UI �� �� ���� Ÿ���� �� UI�� �����´�.
	CUI* pTargetUI = GetTargetedUI(m_pFocusedUI);

	bool bLBtnTap = KEY_TAP(KEY::LBTN);
	bool bLBtnAway = KEY_AWAY(KEY::LBTN);

	if (nullptr != m_pFocusedUI)
	{
		pTargetUI->MouseOn();
		if (bLBtnTap)
		{
			pTargetUI->MouseLbtnDown();
			pTargetUI->m_bLbtnDown = true;
		}
		else if (bLBtnAway)
		{
			pTargetUI->MouseLbtnUp();

			if (pTargetUI->m_bLbtnDown)
			{
				pTargetUI->MouseLbtnClicked();
			}
			// ���� ��ư ����, ������ üũ�� �ٽ� �����Ѵ�.
			pTargetUI->m_bLbtnDown = false;
		}
	}

}

void CUIMgr::SetFocusedUI(CUI* _pUI)
{
	// �̹� ��Ŀ�� ���� ��� or ��Ŀ�� ������û�� ���
	if (m_pFocusedUI == _pUI || nullptr == m_pFocusedUI)
	{
		m_pFocusedUI = _pUI;
		return;
	}

	m_pFocusedUI = _pUI;

	CScene* pCurScene = SceneManager::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (m_pFocusedUI == *iter)
		{
			break;
		}
		// ���� ������ �� �ڷ� ���� ��ü
		vecUI.erase(iter);
		vecUI.push_back(m_pFocusedUI);
	}

}

CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{
	bool bLBtnAway = KEY_AWAY(KEY::LBTN);
	
	// 1. �θ� UI ����, ��� �ڽĵ��� �˻� �Ѵ�.
	CUI* pTargetUI = nullptr;

	static list<CUI*> queue;
	static vector<CUI*> vecNoneTarget;

	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);
	while (!queue.empty())
	{
		// ť���� ������ �ϳ� ������
		CUI* pUI = queue.front();
		queue.pop_front();

		// ť���� ������ UI�� TargetUI���� Ȯ��
		if (pUI->IsMouseOn())
		{
			if (nullptr != pTargetUI)
			{
				vecNoneTarget.push_back(pTargetUI);
			}
			pTargetUI = pUI;
		}
		else
		{
			vecNoneTarget.push_back(pUI);
		}

		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}
	}
	
	// ���ʹ�ư ����, ������ üũ�� �ٽ� �����Ѵ�.
	for (size_t i = 0; i < vecNoneTarget.size(); ++i)
	{
		vecNoneTarget[i]->m_bLbtnDown = false;
	}

	//return _pParentUI;
	// 2. Ÿ�� UI�� ��, �켱������ ���� ������ �� ���� ������ �ڽ� UI
	return pTargetUI;

}

