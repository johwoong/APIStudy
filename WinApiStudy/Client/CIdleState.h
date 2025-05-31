#pragma once
#include "CState.h"
class CIdleState : public CState
{
private:


public:
	virtual void Enter();
	virtual void Exit();
	virtual void update();
public:
	CIdleState();
	~CIdleState();
};

