#include "pch.h"
#include "CCollisionMgr.h"
#include "SceneManager.h"
#include "CScene.h"
#include "CObject.h"
#include "CColider.h"

CCollisionMgr::CCollisionMgr() : m_arrCheck{}
{

}

CCollisionMgr::~CCollisionMgr() 
{

}


void CCollisionMgr::update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		m_arrCheck[iRow];
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionUpdateGroup((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}

void CCollisionMgr::CollisionUpdateGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = SceneManager::GetInst()->GetCurScene();
	pCurScene->GetGroupObject(_eRight);

	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// c�浹ü�� �������� �ʴ� ���
		if (nullptr == vecLeft[i]->GetColider())
			continue;
		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			// �浹ü�� ���ų�, �ڱ��ڽŰ��� �浹�� ���
			if (nullptr == vecRight[j]->GetColider() || vecLeft[i] == vecRight[j])
				continue;

			if (IsCollision(vecLeft[i]->GetColider(), vecRight[j]->GetColider()))
			{

			}
			else
			{

			}
		}
	}
}

bool CCollisionMgr::IsCollision(CColider* _pLeftCol, CColider* _pRightCol)
{
	
	return false;
}


void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// �� ���� ���� �׷� Ÿ���� ������,
	// ū ���� ��(��Ʈ)�� ���
	
	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;
	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol))
	{
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol);
	}
}


