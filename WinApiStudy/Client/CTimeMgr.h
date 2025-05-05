#pragma once
class CTimeMgr // �ð� ����ȭ
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;
	LARGE_INTEGER m_llCurCount;
	// FPS
	// 1 �����Ӵ� �ð� Delta Time
	double m_dDT; // ������ ������ �ð���
	double m_dAcc; // 1�� üũ�� ���� ���� �ð�
	UINT  m_iCallCount;  // �Լ� ȣ�� Ƚ�� üũ
	UINT m_iFPS; // �ʴ� ȣ�� Ƚ��

public:
	void init();
	void update();

public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }
};

