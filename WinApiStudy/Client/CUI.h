#pragma once
#include "CObject.h"
class CUI :
    public CObject
{
private:
    vector<CUI*> m_vecChildUI;
    CUI* m_pParentUI;

    Vec2 m_vFinalPos;

    bool m_bCamAffected; // UI가 카메라에 영향을 받는 유무
    bool m_bMouseOn; // UI 위에 마우스가 있는지
    bool m_bLbtnDown; // UI에 왼쪽버튼이 눌린적이 있는지


public:
    Vec2 GetFinalPos() { return m_vFinalPos; }
    CUI* GetParent() { return m_pParentUI; }
    bool IsMouseOn() { return m_bMouseOn; }
    bool IsLbnDown() { return m_bLbtnDown; }
    const vector<CUI*>& GetChildUI() { return m_vecChildUI; }

    void AddChild(CUI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_pParentUI = this; }

public:
    virtual void update();
    virtual void finalupdate();
    virtual void render(HDC _dc);

public:
    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();
    virtual void MouseLbtnClicked();
    
    virtual CUI* Clone() = 0;

private:
    void update_child();
    void finalupdate_child();
    void render_child(HDC _dc);
    void MouseOnCheck();

    friend class CUIMgr;

public:
    CUI(bool _bCamAff);
    CUI(const CUI& _origin);
    virtual ~CUI();
};

