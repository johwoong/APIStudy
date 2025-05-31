#include "pch.h"
#include "CColider.h"
#include "CObject.h"
#include "CCore.h"
#include "SelectGDI.h"
#include "CCamera.h"

UINT CColider::g_iNextID = 0;

CColider::CColider() : m_pOwner(nullptr), m_iID(g_iNextID++), m_iCol(0), m_bActive(true)
{

}

CColider::CColider(const CColider& _origin) : m_pOwner(nullptr), m_vOffsetPos(_origin.m_vOffsetPos), m_vScale(_origin.m_vScale), m_iID(g_iNextID), m_bActive(_origin.m_bActive)
{
	
}

CColider::~CColider()
{

}

void CColider::finalupdate()
{
	// Object의 위치를 따라가겠다.
	Vec2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;

	assert(0 <= m_iCol);
	
}

void CColider::render(HDC _dc)
{
	PEN_TYPE ePen = PEN_TYPE::GREEN;

	if (m_iCol)
		ePen = PEN_TYPE::RED;

	SelectGDI p(_dc, ePen);
	SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vFinalPos);

	Rectangle(_dc
		, (int)(vRenderPos.x - m_vScale.x / 2.f)
		, (int)(vRenderPos.y - m_vScale.y / 2.f)
		, (int)(vRenderPos.x + m_vScale.x / 2.f)
		, (int)(vRenderPos.y + m_vScale.y / 2.f));
}

void CColider::OnCollision(CColider* _pOther)
{
	m_pOwner->OnCollision(_pOther);
}

void CColider::OnCollisionEnter(CColider* _pOther)
{
	m_pOwner->OnCollisionEnter(_pOther);
	++m_iCol;
}

void CColider::OnCollisionExit(CColider* _pOther)
{
	m_pOwner->OnCollisionExit(_pOther);
	--m_iCol;
}
