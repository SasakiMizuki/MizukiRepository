//=============================================================================
//
// 影処理 [shadow.h]
//
//=============================================================================
#ifndef ___SHADOW_H___
#define ___SHADOW_H___

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitShadow(LPDIRECT3DDEVICE9);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(LPDIRECT3DDEVICE9);

int CreateShadow(D3DXVECTOR3 pos, float fSizeX, float fSizeZ);
void ReleaseShadow(int nIdxShadow);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);
void SetVertexShadow(int nIdxShadow, float fSizeX, float fSizeZ);
void SetColorShadow(int nIdxShadow, D3DXCOLOR col);

#endif
