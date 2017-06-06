#include "BoxMesh.h"
#include "Graphics.h"

// コンストラクタ
CBoxMesh::CBoxMesh(void)
{
	m_pTexture = NULL;
}

// デストラクタ
CBoxMesh::~CBoxMesh(void)
{
}

//---------------------------------------------------------------------------------------
// メッシュ描画
//---------------------------------------------------------------------------------------
void CBoxMesh::Draw(D3DXMATRIX& world)
{
	// ワールド マトリックス設定
	CGraphics::GetDevice()->SetTransform(D3DTS_WORLD, &world);

	for (DWORD i = 0; i < m_dwNumMaterial; i++) {
		CGraphics::GetDevice()->SetMaterial(&m_pMaterial[i]);
		CGraphics::GetDevice()->SetTexture(0, m_pTexture);	// テクスチャを設定
		m_pD3DMesh->DrawSubset(i);							// 描画を実行
	}
}
