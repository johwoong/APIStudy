#pragma once
#include "CObject.h"
class CGround :
    public CObject
{
private:
    virtual void start();
    virtual void update();
public:
    virtual void OnCollisionEnter(CColider* _pOther);
    virtual void OnCollision(CColider* _pOther);
    virtual void OnCollisionExit(CColider* _pOther);

    CLONE(CGround);
public:
    CGround();
    ~CGround();
};

