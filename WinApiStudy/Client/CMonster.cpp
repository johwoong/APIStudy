#include "pch.h"
#include "CMonster.h"
#include "CTimeMgr.h"
#include "CColider.h"
#include "AI.h"

CMonster::CMonster() : m_tInfo{}
{
	CreateColider();

	GetColider()->SetScale(Vec2(40.f, 40.f));
}

CMonster::~CMonster()
{
	if (nullptr != m_pAI)
		delete m_pAI;
}


void CMonster::update()
{
	if(nullptr != m_pAI)
		m_pAI->update();
}

void CMonster::SetAI(AI* _AI)
{
	m_pAI = _AI;
	m_pAI->m_pOwner = this;
}

void CMonster::OnCollisionEnter(CColider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Missile_Player")
	{
		m_tInfo.fHP -= 1;
		if(m_tInfo.fHP <= 0)
			DeleteObject(this);
	}
}