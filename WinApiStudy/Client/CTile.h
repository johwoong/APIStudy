#pragma once
#include "pch.h"
#include "CObject.h"
class CTexture;


class CTile :
    public CObject
{
private:
    CTexture* m_pTileTex;
    int     m_iImgIdx;

public:
    void SetTexture(CTexture* _pTex)
    {
        m_pTileTex = _pTex;
    }

    void AddImgIdx()
    {
        ++m_iImgIdx;
    }
private:
    virtual void update();
    virtual void render(HDC _dc);

public:
    virtual void Save(FILE* pFile);
    virtual void Load(FILE* pFile);
   

    CLONE(CTile);

public:
    CTile();
    ~CTile();
};

