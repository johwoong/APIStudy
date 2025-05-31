#pragma once
#include "pch.h"
class CObject;
class CColider
{
private:
	static UINT g_iNextID;
	
	CObject* m_pOwner; // colider�� �����ϰ� �ִ� ������Ʈ
	Vec2 m_vOffsetPos; // ������Ʈ�κ��� ����ϴ� ��ġ
	Vec2 m_vFinalPos; // finalupdate���� �� ������ ���� ���
	Vec2 m_vScale; // �浹ü�� ũ��
	bool m_bActive; // Ȱ��ȭ ����
	
	UINT m_iID; // �浹ü ������ ID ��
	UINT m_iCol;

public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }
	Vec2 GetFinalPos() { return m_vFinalPos; }
	CObject* GetObj() { return m_pOwner; }
	UINT GetID() { return m_iID; }
public:
	void finalupdate();
	void render(HDC _dc);


public:
	// �浹 ���� �Լ�
	void OnCollision(CColider* _pOther); // �浹 ���� ��� ȣ��Ǵ� �Լ�
	void OnCollisionEnter(CColider* _pOther); // �浹 ���� ��
	void OnCollisionExit(CColider* _pOther); // �浹 ���� ��

	CColider& operator = (CColider* _origin) = delete;


public:
	CColider();
	CColider(const CColider& _origin);
	~CColider();
	friend class CObject;
};

