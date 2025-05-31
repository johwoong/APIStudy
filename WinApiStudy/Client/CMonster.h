#pragma once
#include "CObject.h"
class AI;

struct tMonInfo
{
	float fSpeed; // �ӵ�
	float fHP; // ü��
	float fRecogRange; // ���� ����
	float fAttRange; // ���� ����
	float fAtt; // ���ݷ�
};

class CMonster :
	public CObject
{
private:

	AI* m_pAI;
	tMonInfo m_tInfo;

public:
	float GetSpeed() { return m_tInfo.fSpeed; }
	void SetSpeed(float _f) { m_tInfo.fSpeed = _f; }

	void SetAI(AI* _AI);

private:
	void SetMonInfo(const tMonInfo& _info) { m_tInfo = _info; }
public:
	virtual void OnCollisionEnter(CColider* _pOther);
	const tMonInfo& GetInfo() { return m_tInfo; }
public:
	virtual void update();
	

	CLONE(CMonster);
public:
	CMonster();
	~CMonster();

	friend class CMonFactory;
};
