#include "pch.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "SceneManager.h"
#include "CScene.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "ResourceManager.h"
#include "CColider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidbody.h"
#include "CGravity.h"

CPlayer::CPlayer() : m_eCurState(PLAYER_STATE::IDLE) , m_iDir(1)
{
	// Texture 로딩하기
	//m_pTex = ResourceManager::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player.bmp");

	CreateColider();
	CreateRigidbody();

	GetColider()->SetOffsetPos(Vec2(0.f, 10.f));
	GetColider()->SetScale(Vec2(50.f, 100.f));
	CTexture* pIdleTex = ResourceManager::GetInst()->LoadTexture(L"PlayerIdle", L"texture\\Idle.bmp");
	CTexture* pMoveTex = ResourceManager::GetInst()->LoadTexture(L"PlayerMove", L"texture\\Move.bmp");
	CTexture* pJumpStartTex = ResourceManager::GetInst()->LoadTexture(L"PlayerJumpSTART", L"texture\\Jump_Start.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"IDLE_LEFT", pIdleTex, Vec2(0.f, 0.f), Vec2(256.f, 128.f), Vec2(0.f, 128.f), 0.1f, 8);
	GetAnimator()->CreateAnimation(L"IDLE_RIGHT", pIdleTex, Vec2(256.f, 0.f), Vec2(256.f, 128.f), Vec2(0.f, 128.f), 0.1f, 8); // _vStep 수정


	GetAnimator()->CreateAnimation(L"MOVE_LEFT", pMoveTex, Vec2(0.f, 0.f), Vec2(256.f, 128.f), Vec2(0.f, 128.f), 0.1f, 7);
	GetAnimator()->CreateAnimation(L"MOVE_RIGHT", pMoveTex, Vec2(256.f, 0.f), Vec2(256.f, 128.f), Vec2(0.f, 128.f), 0.1f, 7);

	GetAnimator()->CreateAnimation(L"JumpStart_LEFT", pJumpStartTex, Vec2(0.f, 0.f), Vec2(256.f, 128.f), Vec2(0.f, 128.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"JumpStart_RIGHT", pJumpStartTex, Vec2(256.f, 0.f), Vec2(256.f, 128.f), Vec2(0.f, 128.f), 0.1f, 5);

	GetAnimator()->Play(L"IDLE_LEFT", true);
	
	//CAnimation* pAnim = GetAnimator()->FindAnimation(L"IDLE_LEFT");
	//for (int i = 0; i < pAnim->GetMaxFrame(); ++i)
	//{
	//	pAnim->GetFrame(i).vOffset = Vec2(0.f, -20.f);
	//}D
	//pAnim = GetAnimator()->FindAnimation(L"MOVE_LEFT");
	//for (int i = 0; i < pAnim->GetMaxFrame(); ++i)
	//{
	//	pAnim->GetFrame(i).vOffset = Vec2(0.f, -20.f);
	//}

	m_eDir = PLAYER_DIR::LEFT;
	m_bMoving = false;

	CreateGravity();
}

CPlayer::~CPlayer()
{

}

void CPlayer::update()
{
	update_move();
	update_state();
	update_animation();
	// 애니메이션 상태 전환
	//if (m_bMoving)
	//{
	//	if (m_eDir == PLAYER_DIR::LEFT)
	//		GetAnimator()->Play(L"MOVE_LEFT", true);
	//	else
	//		GetAnimator()->Play(L"MOVE_RIGHT", true);
	//}
	//else
	//{
	//	if (m_eDir == PLAYER_DIR::LEFT)
	//		GetAnimator()->Play(L"IDLE_LEFT", true);
	//	else
	//		GetAnimator()->Play(L"IDLE_RIGHT", true);
	//}

	GetAnimator()->update();

	m_ePrevState = m_eCurState;
}

void CPlayer::render(HDC _dc)
{
	component_render(_dc);
	/*CTexture* pTex = ResourceManager::GetInst()->LoadTexture(L"Plane", L"texture\\Player.bmp");

	Vec2 vPos = GetPos();
	vPos = CCamera::GetInst()->GetRenderPos(vPos);

	float width = (float)pTex->Width();
	float height = (float)pTex->Height();

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 127;

	AlphaBlend(_dc
		, int(vPos.x - width / 2.f)
		, int(vPos.y - height / 2.f)
		, int(width), int(height)
		, pTex->GetDC()
		, 0, 0, int(width), int(height)
		, bf);*/
}

void CPlayer::update_move()
{
	m_bMoving = false; // ← 여기에 반드시 초기화

	CRigidbody* pRigid = GetRigidbody();

	if (KEY_HOLD(KEY::A))
	{
		pRigid->AddForce(Vec2(-100.f, 0.f));
		m_eDir = PLAYER_DIR::LEFT;
		m_bMoving = true;
	}

	if (KEY_HOLD(KEY::D))
	{
		pRigid->AddForce(Vec2(100.f, 0.f));
		m_eDir = PLAYER_DIR::RIGHT;
		m_bMoving = true;
	}
	 
	if (KEY_TAP(KEY::A))
	{
		pRigid->SetVelocity(Vec2(-100.f, pRigid->GetVelocity().y));
	}

	if (KEY_TAP(KEY::D))
	{
		pRigid->SetVelocity(Vec2(-100.f, pRigid->GetVelocity().y));
	}
}

void CPlayer::update_state()
{
	if (KEY_HOLD(KEY::A))
	{
		m_iDir = -1;
		if (PLAYER_STATE::JUMP != m_eCurState)
			m_eCurState = PLAYER_STATE::WALK;
	}

	if (KEY_HOLD(KEY::D))
	{
		m_iDir = 1;
		if (PLAYER_STATE::JUMP != m_eCurState)
			m_eCurState = PLAYER_STATE::WALK;
	}

	if (0.f == GetRigidbody()->GetSpeed() && PLAYER_STATE::JUMP != m_eCurState)
	{
		m_eCurState = PLAYER_STATE::IDLE;
	}

	if (KEY_TAP(KEY::SPACE))
	{
		m_eCurState = PLAYER_STATE::JUMP;

		if (GetRigidbody())
		{
			GetRigidbody()->SetVelocity(Vec2(GetRigidbody()->GetVelocity().x, -500.f));
		}
	}
}

void CPlayer::update_animation()
{
	if (m_ePrevState == m_eCurState)
		return;

	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
	{
		if (m_iDir == -1)
			GetAnimator()->Play(L"IDLE_LEFT", true);
		else
			GetAnimator()->Play(L"IDLE_RIGHT", true);
	}
		break;
	case PLAYER_STATE::WALK:
	{
		if (m_iDir == -1)
			GetAnimator()->Play(L"MOVE_LEFT", true);
		else
			GetAnimator()->Play(L"MOVE_RIGHT", true);
	}
		break;
	case PLAYER_STATE::JUMP:
	{
		if (m_iDir == -1)
			GetAnimator()->Play(L"JumpStart_LEFT", true);
		else
			GetAnimator()->Play(L"JumpStart_RIGHT", true);
	}
	break;
	}
}

void CPlayer::update_gravity()
{
	GetRigidbody()->AddForce(Vec2(0.f, 500.f)); 
}

void CPlayer::OnCollisionEnter(CColider* _pOther)
{
	if (L"Ground" == _pOther->GetObj()->GetName())
	{
		Vec2 vPos = GetPos();
		if (vPos.y < _pOther->GetObj()->GetPos().y)
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}
	}
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f));

	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}