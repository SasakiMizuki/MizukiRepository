#pragma once

#include "main.h"

typedef struct {
	LPDIRECT3DTEXTURE9	pD3DTextureModel;	// テクスチャへのポインタ

	LPD3DXMESH		pD3DXMeshModel;			//メッシュ
	LPD3DXBUFFER	pD3DXBuffMatModel;		//マテリアル
	DWORD			nNumMatModel;			//パーツ数
	D3DXVECTOR3		posModel;				//位置
	D3DXVECTOR3		moveModel;				//移動量
	D3DXVECTOR3		rotModel;				//回転
	D3DXVECTOR3		scaleModel;				//拡大
	D3DXMATRIX		mtxWorld;				// ワールドマトリクス

	D3DMATERIAL9*		pMeshMat;	// マテリアル情報
	LPDIRECT3DTEXTURE9*	pMeshTex;	// メッシュのテクスチャ
} tSkyData;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSky(LPDIRECT3DDEVICE9);
void UninitSky(void);
void UpdateSky(void);
void DrawSky(LPDIRECT3DDEVICE9);
