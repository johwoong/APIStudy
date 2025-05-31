#pragma once
#include "global.h"
#include "CCamera.h"
class CColider;
class CAnimator;
class CRigidbody;
class CGravity;
class CObject
{
private:
	wstring m_strName;
	Vec2 m_vPos;
	Vec2 m_vScale;

	// Component
	CColider* m_pColider;
	CAnimator* m_pAnimator;
	CRigidbody* m_pRigidbody;
	CGravity* m_pGravity;
	 
	bool m_bAlive;
public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject();

	friend class CEventMgr;

public:
	const wstring& GetName() { return m_strName; }
	void SetName(const wstring& _strName) { m_strName = _strName; }

	void SetPos(Vec2  _vPos) { m_vPos = _vPos; }
	Vec2 GetPos() { return m_vPos; }

	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	Vec2 GetScale() { return m_vScale; }

	CColider* GetColider() { return m_pColider; }
	CAnimator* GetAnimator() { return m_pAnimator; }
	CRigidbody* GetRigidbody() { return m_pRigidbody; }
	CGravity* GetGravity() { return m_pGravity; }
	void CreateColider();
	void CreateAnimator();
	void CreateRigidbody();
	void CreateGravity();
	void component_render(HDC _dc);

	bool IsDead() { return !m_bAlive; }

public:
	virtual void OnCollision(CColider* _pOther) { }
	virtual void OnCollisionEnter(CColider* _pOther) { }
	virtual void OnCollisionExit(CColider* _pOther) {}

private:
	void SetDead() { m_bAlive = false; }
public:
	virtual CObject* Clone() = 0;
	virtual void start() {} // Scene이 시작되기 직전에 호출되는 함수
	virtual void update() = 0;
	virtual void finalupdate();
	virtual void render(HDC _dc);
};
