//=============================================================================
//
// モデル処理 [model.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

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
	bool			bPlayerMove;
	bool			bPlayerJump;
	float			fJumpTime;
	int nIdxShadow;

	D3DMATERIAL9*		pMeshMat;	// マテリアル情報
	LPDIRECT3DTEXTURE9*	pMeshTex;	// メッシュのテクスチャ
} tPlayerData;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitModel(LPDIRECT3DDEVICE9);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(LPDIRECT3DDEVICE9);
D3DXVECTOR3 GetModelPos();				// 座標取得
D3DXVECTOR3 GetModelRot();				// 回転取得
tPlayerData* GetPlayerData();				// 座標取得
void SetPlayerCanMove(bool);


#endif
