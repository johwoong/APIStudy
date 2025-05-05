#pragma once
class CScene;
class SceneManager
{
	SINGLE(SceneManager)

private:
	CScene* m_arrScene[(UINT)SCENE_TYPE::END]; // ��� �� ���
	CScene* m_pCurScene; // ���� ��

public:
	void init();
	void update();
	void render(HDC _dc);

};

