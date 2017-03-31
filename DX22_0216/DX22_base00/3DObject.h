#pragma once

#include "main.h"

// モデルのあるアイテム
typedef enum {
	OBJECT_MODEL_HOUSE,		//家
	OBJECT_MODEL_PALM,		//ヤシ
	OBJECT_MODEL_FENCE,		//フェンス
	OBJECT_MODEL_RAFT,		//イカダ
	OBJECT_MODEL_TREASURE,	//宝箱

	OBJECT_MODEL_NUM_MAX
} eObjectModel;

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
	bool			bLive;					// 生存(表示)フラグ(モデルがあるもののみ)
	bool			bHave;					// 持っているか
	int nIdxShadow;

	D3DMATERIAL9*		pMeshMat;	// マテリアル情報
	LPDIRECT3DTEXTURE9*	pMeshTex;	// メッシュのテクスチャ
} tObjectModelData;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT Init3DObject(LPDIRECT3DDEVICE9);
void	Uninit3DObject(void);
void	Update3DObject(void);
void	Draw3DObject(LPDIRECT3DDEVICE9);

void HitCheckto3DObject();

void SetInfo3DObject(eObjectModel, D3DXVECTOR3 posModel, D3DXVECTOR3 rotModel, D3DXVECTOR3 sclModel);
void Setting3DObject(int);

void Delete3DObject();