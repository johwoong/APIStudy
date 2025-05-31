#pragma once
#include "CState.h"
class CTraceState :
    public CState
{

private:


public:
	virtual void Enter();
	virtual void Exit();
	virtual void update();
public:
	CTraceState();
	~CTraceState();
};

