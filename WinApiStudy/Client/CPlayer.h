#pragma once
#include "CObject.h"
#include "KeyManager.h"
#include "CTimeMgr.h"
class CTexture;
class CColider;
enum class PLAYER_STATE
{
	IDLE,
	WALK,
	ATTACK,
	JUMP,
	DEAD,
};

enum class PLAYER_ATTACK_STATE
{
	NORMAL_ATT_1,
	NORMAL_ATT_2,
};



enum class PLAYER_DIR
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
};
class CPlayer :
	public CObject
{
private:
	PLAYER_DIR m_eDir;
	PLAYER_STATE m_eCurState;
	PLAYER_STATE m_ePrevState;
	bool m_bMoving; // 이동 중 여부
	int m_iDir;

public:
	virtual void update();
	virtual void render(HDC _dc);

private:
	void update_move();
	void update_state();
	void update_animation();
	void update_gravity();
	virtual void OnCollisionEnter(CColider* _pOther);


private:
	void CreateMissile();
	CLONE(CPlayer);

public:
	CPlayer();
	~CPlayer();
};
