#include "pch.h"
#include "ResourceManager.h"
#include "CPathMgr.h"
#include "CTexture.h"
ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
    Safe_Delete_Map(m_mapTex);
}

CTexture* ResourceManager::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
    CTexture* pTex = FindTexture(_strKey);
    if (nullptr != pTex)
    {
        return pTex;
    }
    wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
    strFilePath += _strRelativePath;

    pTex = new CTexture;
    pTex->Load(strFilePath);
    pTex->SetKey(_strKey);
    pTex->SetRelativePath(_strRelativePath);

    m_mapTex.insert(make_pair(_strKey, pTex));
    return pTex;
}

CTexture* ResourceManager::CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight)
{
    CTexture* pTex = FindTexture(_strKey);
    if (nullptr != pTex)
    {
        return pTex;
    }

    pTex = new CTexture;
    pTex->Create(_iWidth, _iHeight);
    pTex->SetKey(_strKey);
    m_mapTex.insert(make_pair(_strKey, pTex));

    return pTex;
}

CTexture* ResourceManager::FindTexture(const wstring& _strKey)
{
    map<wstring, CRes*>::iterator iter = m_mapTex.find(_strKey);

    if (iter == m_mapTex.end())
    {
        return nullptr;
    }
    return (CTexture*)iter->second;
}
