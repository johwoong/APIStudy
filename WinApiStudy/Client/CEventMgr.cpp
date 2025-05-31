#include "pch.h"
#include "CEventMgr.h"
#include "CObject.h"
#include "SceneManager.h"
#include "CScene.h"
#include "CUIMgr.h"
#include "AI.h"
#include "CState.h"

CEventMgr::CEventMgr()
{

}

CEventMgr::~CEventMgr()
{

}


void CEventMgr::update()
{
	// 이전 프레임에서 등록해둔 Dead Object들을 삭제한다.
	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		delete m_vecDead[i];
	}
	m_vecDead.clear();

	// Event 처리
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		Excute(m_vecEvent[i]);
	}

	m_vecEvent.clear();
}

void CEventMgr::Excute(const tEvent& _eve)
{
	switch (_eve.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParam : Object Address
		// wParam : Group Type
		CObject* pNewObj = (CObject*)_eve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;

		SceneManager::GetInst()->GetCurScene()->AddObject(pNewObj, eType);
	}
		break;
	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lParam : Objec Address
		// Object를 Dead 상태로 변경
		// 삭제 예정 오브젝트들을 모아둔다.
		CObject* pDeadObj = (CObject*)_eve.lParam;
		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);
	}
		break;
	case EVENT_TYPE::SCENE_CHANGE:
		SceneManager::GetInst()->ChangeScene((SCENE_TYPE)_eve.lParam);
		// 포커스 UI 해제(이전 Scene의 UI를 가리키고 있기 때문)
		CUIMgr::GetInst()->SetFocusedUI(nullptr);
		break;
	case EVENT_TYPE::CHANCE_AI_STATE:
		// lParam : AI
		// wParam : Next Type
		AI* pAI = (AI*)_eve.lParam;
		MON_STATE eNextState = (MON_STATE)_eve.wParam;
		pAI->ChangeState(eNextState);
		break;
	}
}
