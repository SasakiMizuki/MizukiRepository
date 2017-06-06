#pragma once
#include<d3d9.h>

class CRenderTarget
{
protected:
	// レンダリングターゲット
	LPDIRECT3DTEXTURE9 m_pTexture;	// 出力先テクスチャ
	LPDIRECT3DSURFACE9 m_pSurface;	// 出力先(テクスチャ関連付け)
	LPDIRECT3DSURFACE9 m_pZBuffer;	// 出力先Zバッファ&ステンシルバッファ

	// バックバッファ退避
	LPDIRECT3DSURFACE9 m_pSaveBB;
	LPDIRECT3DSURFACE9 m_pSaveZB;

public:
	CRenderTarget();
	virtual ~CRenderTarget();

	HRESULT Init();					// 生成
	void Fin();						// 解放
	LPDIRECT3DTEXTURE9 GetTexture() {	// 参照
		return m_pTexture;
	}
	void Change();					// 切り替え
	void Reset();					// 元に戻す
};

