//=============================================================================
//
// 爆発処理 [explosion.h]
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitExplosion(LPDIRECT3DDEVICE9 pDevice);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(LPDIRECT3DDEVICE9 pDevice);

int SetExplosion(D3DXVECTOR3 pos, float fSizeX, float fSizeY);

#endif
