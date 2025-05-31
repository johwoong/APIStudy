#include "CGround.h"
#include "CColider.h"
#include "CGravity.h"


CGround::CGround()
{
	CreateColider();

}

CGround::~CGround()
{
}


void CGround::start()
{
	GetColider()->SetScale(Vec2(GetScale()));
}

void CGround::update()
{ 
}

void CGround::OnCollisionEnter(CColider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		pOtherObj->GetGravity()->SetGround(true);

		Vec2 vObjPos = _pOther->GetFinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = GetColider()->GetFinalPos();
		Vec2 vScale = GetColider()->GetScale();

		float fLen = abs(vObjPos.y - vPos.y);
		float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen; // ��ģ ����


		vObjPos = pOtherObj->GetPos();
		// �浹�� ���ѻ��·� �����ϱ� ���ؼ� �Ϻη� 1�ȼ� �� �÷���
		vObjPos.y -= fValue;

		pOtherObj->SetPos(vObjPos);
	}
}

void CGround::OnCollision(CColider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		pOtherObj->GetGravity()->SetGround(true);

		Vec2 vObjPos = _pOther->GetFinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = GetColider()->GetFinalPos();
		Vec2 vScale = GetColider()->GetScale();

		float fLen = abs(vObjPos.y - vPos.y);
		float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen; // ��ģ ����

		vObjPos = pOtherObj->GetPos();
		// �浹�� ���ѻ��·� �����ϱ� ���ؼ� �Ϻη� 1�ȼ� �� �÷���
		vObjPos.y -= fValue;

		pOtherObj->SetPos(vObjPos);
	}
}

void CGround::OnCollisionExit(CColider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		pOtherObj->GetGravity()->SetGround(false);

	}
}

