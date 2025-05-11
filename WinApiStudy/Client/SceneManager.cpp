#include "pch.h"
#include "SceneManager.h"
#include "CScene_Start.h"

SceneManager::SceneManager() :m_arrScene{}, m_pCurScene(nullptr)
{
}

SceneManager::~SceneManager()
{
	// �� ���� ����
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}
	}
}

void SceneManager::init()
{
	// Scene ����
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");

	//m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Start;
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CScene_Start;
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_Start;

	// ���� �� ����
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
	m_pCurScene->Enter();
}

void SceneManager::update()
{
	m_pCurScene->update();
	m_pCurScene->finalupdate();
}


void SceneManager::render(HDC _dc)
{
	m_pCurScene->render(_dc);
}