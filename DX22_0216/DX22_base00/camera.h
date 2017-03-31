//=============================================================================
//
// カメラ処理 [camera.h]
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);

void SetCamera(LPDIRECT3DDEVICE9);
D3DXVECTOR3 GetRotCamera(void);
D3DXMATRIX	GetMtxView();

#endif
