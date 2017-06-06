// レンダリング ターゲット変更
#pragma once
#include <d3d9.h>

#define MAX_TEXTURE	3
#define MAX_TARGET 2

class CRenderTarget
{
protected:
	// レンダリング ターゲット
	LPDIRECT3DTEXTURE9	m_pTexture[MAX_TEXTURE];	// 出力先テクスチャ
	LPDIRECT3DSURFACE9	m_pSurface[MAX_TEXTURE];	// 出力先(テクスチャを関連付)
	LPDIRECT3DSURFACE9	m_pZBuffer[MAX_TARGET];	// 出力先Zバッファ&ステンシルバッファ

	// バックバッファ退避
	LPDIRECT3DSURFACE9	m_pSaveBB[MAX_TARGET];
	LPDIRECT3DSURFACE9	m_pSaveZB;
	D3DVIEWPORT9		m_vpSave;
public:
	CRenderTarget(void);
	virtual ~CRenderTarget(void);

	HRESULT Init();						// 生成
	void Fin();							// 解放
	LPDIRECT3DTEXTURE9 GetTexture(UINT uIdx = 0)		// 参照
	{
		return m_pTexture[uIdx];
	}
	void Save();
	void Change(UINT uTarget);						// 切り替え
	void Reset();						// 元に戻す
};
