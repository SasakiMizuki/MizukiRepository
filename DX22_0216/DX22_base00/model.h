//=============================================================================
//
// ���f������ [model.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

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
	bool			bPlayerMove;
	bool			bPlayerJump;
	float			fJumpTime;
	int nIdxShadow;

	D3DMATERIAL9*		pMeshMat;	// �}�e���A�����
	LPDIRECT3DTEXTURE9*	pMeshTex;	// ���b�V���̃e�N�X�`��
} tPlayerData;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitModel(LPDIRECT3DDEVICE9);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(LPDIRECT3DDEVICE9);
D3DXVECTOR3 GetModelPos();				// ���W�擾
D3DXVECTOR3 GetModelRot();				// ��]�擾
tPlayerData* GetPlayerData();				// ���W�擾
void SetPlayerCanMove(bool);


#endif
