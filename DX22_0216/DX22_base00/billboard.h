//=============================================================================
//
// �r���{�[�h���� [billboard.h]
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBillboard(LPDIRECT3DDEVICE9 pDevice);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(LPDIRECT3DDEVICE9 pDevice);

#endif
