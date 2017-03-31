//=============================================================================
//
// ビルボード処理 [billboard.h]
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBillboard(LPDIRECT3DDEVICE9 pDevice);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(LPDIRECT3DDEVICE9 pDevice);

#endif
