//=============================================================================
//
// ビルボード処理 [billboard.h]
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

class CBullet{
public:
	HRESULT MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 BulletPos);
	void SetVertexBullet(float fSizeX, float fSizeY);

	HRESULT InitBullet(LPDIRECT3DDEVICE9 pDevice);
	void UninitBullet(void);
	void UpdateBullet(void);
	void DrawBullet(LPDIRECT3DDEVICE9 pDevice);

private:
	LPDIRECT3DTEXTURE9		m_pD3DTextureBullet = NULL;	// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pD3DVtxBuffBullet = NULL;	// 頂点バッファインターフェースへのポインタ
							
	D3DXMATRIX				m_mtxWorldBullet;			// ワールドマトリックス
	D3DXVECTOR3				m_posBullet;					// 位置
	D3DXVECTOR3				m_sclBullet;					// スケール
	D3DXVECTOR3				m_vecBullet;					// 移動量
	int						m_nIdxShadowBullet;			// 影ID
	bool					m_bEnableGravity = true;		// 重力使用フラグ

};

#endif
