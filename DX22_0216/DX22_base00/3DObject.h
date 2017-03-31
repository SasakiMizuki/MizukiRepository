#pragma once

#include "main.h"

// ���f���̂���A�C�e��
typedef enum {
	OBJECT_MODEL_HOUSE,		//��
	OBJECT_MODEL_PALM,		//���V
	OBJECT_MODEL_FENCE,		//�t�F���X
	OBJECT_MODEL_RAFT,		//�C�J�_
	OBJECT_MODEL_TREASURE,	//��

	OBJECT_MODEL_NUM_MAX
} eObjectModel;

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
	bool			bLive;					// ����(�\��)�t���O(���f����������̂̂�)
	bool			bHave;					// �����Ă��邩
	int nIdxShadow;

	D3DMATERIAL9*		pMeshMat;	// �}�e���A�����
	LPDIRECT3DTEXTURE9*	pMeshTex;	// ���b�V���̃e�N�X�`��
} tObjectModelData;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT Init3DObject(LPDIRECT3DDEVICE9);
void	Uninit3DObject(void);
void	Update3DObject(void);
void	Draw3DObject(LPDIRECT3DDEVICE9);

void HitCheckto3DObject();

void SetInfo3DObject(eObjectModel, D3DXVECTOR3 posModel, D3DXVECTOR3 rotModel, D3DXVECTOR3 sclModel);
void Setting3DObject(int);

void Delete3DObject();