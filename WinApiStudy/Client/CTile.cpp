#include "pch.h"
#include "CTile.h"
#include "CTexture.h"
CTile::CTile() : m_pTileTex(nullptr), m_iImgIdx(12)
{
	SetScale(Vec2(TILE_SIZE, TILE_SIZE));
}

CTile::~CTile()
{

}

void CTile::update()
{

}

void CTile::render(HDC _dc)
{
	if (m_pTileTex == nullptr)
		return;

	UINT iWidth = m_pTileTex->Width();
	UINT iHeight = m_pTileTex->Height();

	UINT iMaxCol = iWidth / TILE_SIZE;
	UINT iMaxRow = iHeight / TILE_SIZE;

	UINT iCurRow = (UINT)m_iImgIdx / iMaxCol;
	UINT iCurCol = (UINT)m_iImgIdx % iMaxCol;

	// �̹��� ������ ��� �ε���
	if (iMaxRow <= iCurRow)
		assert(nullptr);

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();

	BitBlt(_dc
		, int(vRenderPos.x)
		, int(vRenderPos.y)
		, int(vScale.x)
		, int(vScale.y)
		, m_pTileTex->GetDC()
		, iCurCol * TILE_SIZE
		, iCurRow * TILE_SIZE
		, SRCCOPY);
}

void CTile::Save(FILE* pFile)
{
	fwrite(&m_iImgIdx, sizeof(int), 1, pFile);
}

void CTile::Load(FILE* pFile)
{
	fread(&m_iImgIdx, sizeof(int), 1, pFile);
}

