#pragma once
#include "CUI.h"
#include "CObject.h"
#include "CScene.h"

typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

typedef void(CScene::*SCENE_MEMFUC)(void);
typedef void(CObject::*OBJECT_MEMFUC)(void);

class CButtonUI :
    public CUI
{
private:
    BTN_FUNC m_pFunc;
    DWORD_PTR m_param1;
    DWORD_PTR m_param2;

    SCENE_MEMFUC m_pSceneFunc;
    CScene* m_pSceneInst;

public:
    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();
    virtual void MouseLbtnClicked();

    void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2)
    {
        m_pFunc = _pFunc;
        m_param1 = _param1;
        m_param2 = _param2;
    }

    void SetClickedCallBack(CScene* _pScene, SCENE_MEMFUC _pSceneFunc);

    CLONE(CButtonUI)
public:
    CButtonUI();
    ~CButtonUI();
};

