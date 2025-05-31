#pragma once
class CPathMgr
{
	SINGLE(CPathMgr);

private:
	wchar_t m_szContentPath[255];
	wchar_t m_szRelativePath[255];

public:
	void init();
	const wchar_t* GetContentPath() { return m_szContentPath; }
	wstring GetRelativePath(const wchar_t* _filepath);
};
