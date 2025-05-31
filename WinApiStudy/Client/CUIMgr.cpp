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

	// 기존 포커싱 UI를 받아두고 변경되었는지 확인한다.
	CUI* pFocusedUI = m_pFocusedUI;

	if (!bLBtnTap)
	{
		return pFocusedUI;
	}

	// 왼쪽버튼 TAP이 발생했따는 전제
	vector<CObject*>::iterator targetiter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (((CUI*)*iter)->IsMouseOn())
		{
			targetiter = iter;
		}
	}

	// 이번에 Focuse된 UI가 없다.
	if (vecUI.end() == targetiter)
	{
		return nullptr;
	}

	pFocusedUI = (CUI*)*targetiter;

	// 벡터 내에서 맨 뒤로 순번 교체
	vecUI.erase(targetiter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}

void CUIMgr::update()
{
	// 1.FocusedUI 확인
	m_pFocusedUI = GetFocusedUI();

	if (!m_pFocusedUI)
		return;

	// 2. FocusedUI 내에서, 부모 UI 포함, 자식 UI 들 중 실제 타겟팅 된 UI를 가져온다.
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
			// 왼쪽 버튼 떼면, 눌렀던 체크를 다시 해제한다.
			pTargetUI->m_bLbtnDown = false;
		}
	}

}

void CUIMgr::SetFocusedUI(CUI* _pUI)
{
	// 이미 포커싱 중인 경우 or 포커싱 해제요청인 경우
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
		// 벡터 내에서 맨 뒤로 순번 교체
		vecUI.erase(iter);
		vecUI.push_back(m_pFocusedUI);
	}

}

CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{
	bool bLBtnAway = KEY_AWAY(KEY::LBTN);
	
	// 1. 부모 UI 포함, 모든 자식들을 검사 한다.
	CUI* pTargetUI = nullptr;

	static list<CUI*> queue;
	static vector<CUI*> vecNoneTarget;

	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);
	while (!queue.empty())
	{
		// 큐에서 데이터 하나 꺼내기
		CUI* pUI = queue.front();
		queue.pop_front();

		// 큐에서 꺼내온 UI가 TargetUI인지 확인
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
	
	// 왼쪽버튼 떼면, 눌렀던 체크를 다시 해제한다.
	for (size_t i = 0; i < vecNoneTarget.size(); ++i)
	{
		vecNoneTarget[i]->m_bLbtnDown = false;
	}

	//return _pParentUI;
	// 2. 타겟 UI들 중, 우선순위가 높은 기준은 더 낮은 계층의 자식 UI
	return pTargetUI;

}

