#pragma once

#include "main.h"

// 総アイテム
typedef enum {
	ITEM_TORCH,			//松明
	ITEM_LOG,			//丸太
	ITEM_ROPE,			//ロープ
	ITEM_BOTTLE,		//ビン
	ITEM_CLOTH,			//布
	ITEM_FOOD,			//食糧
	ITEM_FLIPPERS,		//足ひれ

	ITEM_NUM_MAX
} eItem; 

// モデルのあるアイテム
typedef enum {
	ITEM_MODEL_TORCH,		//松明
	ITEM_MODEL_LOG,			//丸太
	ITEM_MODEL_ROPE,		//ロープ
	ITEM_MODEL_BOTTLE,		//ビン

	ITEM_MODEL_NUM_MAX
} eItemModel;

typedef struct {
	LPDIRECT3DTEXTURE9	pD3DTextureModel;	// テクスチャへのポインタ

	LPD3DXMESH		pD3DXMeshModel;			//メッシュ
	LPD3DXBUFFER	pD3DXBuffMatModel;		//マテリアル
	DWORD			nNumMatModel;			//パーツ数
	D3DXVECTOR3		posModel;				//位置
	D3DXVECTOR3		moveModel;				//移動量
	D3DXVECTOR3		rotModel;				//回転
	D3DXVECTOR3		scaleModel;				//拡大
	D3DXVECTOR3		sizeModel;				//大きさ
	D3DXMATRIX		mtxWorld;				// ワールドマトリクス
	bool			bLive;					// 生存(表示)フラグ(モデルがあるもののみ)
	bool			bHave;					// 持っているか
	int nIdxShadow;

	D3DMATERIAL9*		pMeshMat;	// マテリアル情報
	LPDIRECT3DTEXTURE9*	pMeshTex;	// メッシュのテクスチャ
} tItemModelData;

typedef struct {
	LPDIRECT3DTEXTURE9 pTextureItemIcon;
	VERTEX_2D ItemVertex[NUM_VERTEX];

	float	fTexPosX;
	float	fTexPosY;
	int		nTexSizeX;
	int		nTexSizeY;

	bool	bLive;					// 生存(表示)フラグ(モデルがあるもののみ)
	bool	bHave;					// 持っているか
} tItemIconData;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitItem(LPDIRECT3DDEVICE9);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(LPDIRECT3DDEVICE9);

bool GetItemFlag(eItem);

void SetInfoItem(eItem, D3DXVECTOR3);
void SetInfoItemIcon(int nItem);
void AcquisitionItem(eItem);
void ItemSetting(int);

void DeleteItem();
void DeleteItem(eItem item);