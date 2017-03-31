#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "main.h"

//----- 列挙型 -----
typedef enum {
	OBJECT_TREE,
	OBJECT_FENCE,
	OBJECT_HOUSE,

	OBJECT_NUM_MAX
} enum_object;


//----- 構造体 -----
typedef struct {
	LPDIRECT3DTEXTURE9		pD3DTextureBillboard;	// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 pD3DVtxBuffBillboard;	// 頂点バッファインターフェースへのポインタ

	D3DXMATRIX				mtxWorldBillboard;			// ワールドマトリックス
	D3DXVECTOR2				sizeBillboard;				// 大きさ
	D3DXVECTOR3				posBillboard;				// 位置
	D3DXVECTOR3				sclBillboard;				// 拡大率
	D3DXVECTOR3				vecBillboard;				// 移動量
	int						nIdxShadowBillboard;		// 影ID
	bool					bEnableGravity;				// 重力使用フラグ
	bool					bLive;						//生存フラグ

	enum_object eObject;
	LPDIRECT3DTEXTURE9  pTextureObject;	//テクスチャへのポインタ
	VERTEX_3D *pVertex;		//頂点格納庫
} object;

//----- プロトタイプ -----
void InitObject();
void UninitObject();
void UpdateObject();
void DrawObject();

void DeleteObject();
void DeleteObject(int);

void HitChecktoObject();
void SetInfoObject(enum_object, float, float, float);

//void PlayerPos();



#endif