//=============================================================================
//
// 地面処理 [field.h]
//
//=============================================================================
#ifndef _FIELD_H_
#define _FIELD_H_

#include "main.h"

typedef enum{
	FIELD_GRASS,
	FIELD_BEACH,

	MAX_FIELD_TYPE
}eFieldType;
typedef struct {
	LPDIRECT3DTEXTURE9		pD3DTextureField[MAX_FIELD_TYPE];	// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 pD3DVtxBuffField;	// 頂点バッファインターフェースへのポインタ
	D3DXMATRIX				mtxField;

	int						nNumVertexField;	//総頂点数
	int						nNumPolygonField;	//総ポリゴン数
	LPDIRECT3DINDEXBUFFER9	pD3DIdxBuffField;	// インデックスバッファインタフェースへのポインタ
	int						nNumVertexIndex;	// 総インデックス数

	int						nFieldNumber;
	eFieldType				FieldType;
} FIELD;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitField(LPDIRECT3DDEVICE9, int, int, float, float);
void UninitField(void);
void UpdateField(void);
void DrawField(LPDIRECT3DDEVICE9);
int  GetFieldNumber();
void SetObjectinField();

#endif
