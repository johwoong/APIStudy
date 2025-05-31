#include "pch.h"
#include "CObject.h"
#include "CColider.h"
#include "CAnimator.h"
#include "CRigidbody.h"
#include "CGravity.h"

CObject::CObject() : m_vPos{}, m_vScale{}, m_pColider(nullptr), m_bAlive(true) , m_pAnimator(nullptr), m_pRigidbody(nullptr), m_pGravity(nullptr)
{
}

CObject::CObject(const CObject& _origin) : m_strName(_origin.m_strName), m_vPos(_origin.m_vPos), m_vScale(_origin.m_vScale), m_pColider(nullptr), m_bAlive(true), m_pAnimator(nullptr), m_pRigidbody(nullptr), m_pGravity(nullptr)
{
	if (_origin.m_pColider)
	{
		m_pColider = new CColider(*_origin.m_pColider);
		m_pColider->m_pOwner = this;
	}
	if (_origin.m_pAnimator)
	{
		m_pAnimator = new CAnimator(*_origin.m_pAnimator);
		m_pAnimator->m_pOwner = this;
	}

	if (_origin.m_pRigidbody)
	{
		m_pRigidbody = new CRigidbody(*_origin.m_pRigidbody);
		m_pRigidbody->m_pOwner = this;
	}

	if (_origin.m_pGravity)
	{
		m_pGravity = new CGravity(*_origin.m_pGravity);
		m_pGravity->m_pOwner = this;
	}

}

CObject::~CObject()
{
	if (nullptr != m_pColider)
		delete m_pColider;

	if (nullptr != m_pAnimator)
		delete m_pAnimator;

	if (nullptr != m_pRigidbody)
		delete m_pRigidbody;

	if (nullptr != m_pGravity)
		delete m_pGravity;
}

void CObject::CreateColider()
{
	m_pColider = new CColider;
	m_pColider->m_pOwner = this;
}



void CObject::finalupdate()
{

	if (m_pAnimator)
		m_pAnimator->finalupdate();

	if (m_pGravity)
		m_pGravity->finalupdate();

	if (m_pRigidbody)
		m_pRigidbody->finalupdate();

	if (m_pColider)
		m_pColider->finalupdate();
}

void CObject::render(HDC _dc)
{
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vPos);
	Rectangle(_dc, (int)(vRenderPos.x - m_vScale.x / 2.f), (int)(vRenderPos.y - m_vScale.y / 2.f),
		(int)(vRenderPos.x + m_vScale.x / 2.f), (int)(vRenderPos.y + m_vScale.y / 2.f));

	component_render(_dc);
}

void CObject::component_render(HDC _dc)
{

	if (nullptr != m_pAnimator)
	{
		m_pAnimator->render(_dc);
	}

	if (nullptr != m_pColider)
	{
		m_pColider->render(_dc);
	}
}

void CObject::CreateAnimator()
{
	m_pAnimator = new CAnimator;
	m_pAnimator->m_pOwner = this;
}

void CObject::CreateRigidbody()
{
	m_pRigidbody = new CRigidbody;
	m_pRigidbody->m_pOwner = this;
}

void CObject::CreateGravity()
{
	m_pGravity = new CGravity;
	m_pGravity->m_pOwner = this;
}

