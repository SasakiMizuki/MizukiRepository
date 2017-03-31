//=============================================================================
//
// �G�t�F�N�g���� [effect.h]
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEffect(LPDIRECT3DDEVICE9 pDevice);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(LPDIRECT3DDEVICE9 pDevice);

int SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fSizeX, float fSizeY, int nTimer);

#endif