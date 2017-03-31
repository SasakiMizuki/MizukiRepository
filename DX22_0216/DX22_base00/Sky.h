#pragma once

#include "main.h"

typedef struct {
	LPDIRECT3DTEXTURE9	pD3DTextureModel;	// �e�N�X�`���ւ̃|�C���^

	LPD3DXMESH		pD3DXMeshModel;			//���b�V��
	LPD3DXBUFFER	pD3DXBuffMatModel;		//�}�e���A��
	DWORD			nNumMatModel;			//�p�[�c��
	D3DXVECTOR3		posModel;				//�ʒu
	D3DXVECTOR3		moveModel;				//�ړ���
	D3DXVECTOR3		rotModel;				//��]
	D3DXVECTOR3		scaleModel;				//�g��
	D3DXMATRIX		mtxWorld;				// ���[���h�}�g���N�X

	D3DMATERIAL9*		pMeshMat;	// �}�e���A�����
	LPDIRECT3DTEXTURE9*	pMeshTex;	// ���b�V���̃e�N�X�`��
} tSkyData;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSky(LPDIRECT3DDEVICE9);
void UninitSky(void);
void UpdateSky(void);
void DrawSky(LPDIRECT3DDEVICE9);
