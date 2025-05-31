#include "pch.h"
#include "CTraceState.h"
#include "CScene.h"
#include "SceneManager.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CTimeMgr.h"

CTraceState::CTraceState() : CState(MON_STATE::TRACE)
{
}

CTraceState::~CTraceState()
{
}

void CTraceState::Enter()
{
}

void CTraceState::Exit()
{
}

void CTraceState::update()
{
	// Å¸°ÙÆÃ µÈ Player¸¦ ÂÑ¾Æ°£´Ù.
	CPlayer* pPlayer = (CPlayer*)SceneManager::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();

	Vec2 vMonPos = GetMonster()->GetPos();

	Vec2 vMonDir = vPlayerPos - vMonPos;
	vMonDir.Normalize();

	vMonPos += vMonDir * GetMonster()->GetInfo().fSpeed* fDT;

	GetMonster()->SetPos(vMonPos);
}

