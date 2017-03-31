#pragma once

#include "main.h"

// ���A�C�e��
typedef enum {
	ITEM_TORCH,			//����
	ITEM_LOG,			//�ۑ�
	ITEM_ROPE,			//���[�v
	ITEM_BOTTLE,		//�r��
	ITEM_CLOTH,			//�z
	ITEM_FOOD,			//�H��
	ITEM_FLIPPERS,		//���Ђ�

	ITEM_NUM_MAX
} eItem; 

// ���f���̂���A�C�e��
typedef enum {
	ITEM_MODEL_TORCH,		//����
	ITEM_MODEL_LOG,			//�ۑ�
	ITEM_MODEL_ROPE,		//���[�v
	ITEM_MODEL_BOTTLE,		//�r��

	ITEM_MODEL_NUM_MAX
} eItemModel;

typedef struct {
	LPDIRECT3DTEXTURE9	pD3DTextureModel;	// �e�N�X�`���ւ̃|�C���^

	LPD3DXMESH		pD3DXMeshModel;			//���b�V��
	LPD3DXBUFFER	pD3DXBuffMatModel;		//�}�e���A��
	DWORD			nNumMatModel;			//�p�[�c��
	D3DXVECTOR3		posModel;				//�ʒu
	D3DXVECTOR3		moveModel;				//�ړ���
	D3DXVECTOR3		rotModel;				//��]
	D3DXVECTOR3		scaleModel;				//�g��
	D3DXVECTOR3		sizeModel;				//�傫��
	D3DXMATRIX		mtxWorld;				// ���[���h�}�g���N�X
	bool			bLive;					// ����(�\��)�t���O(���f����������̂̂�)
	bool			bHave;					// �����Ă��邩
	int nIdxShadow;

	D3DMATERIAL9*		pMeshMat;	// �}�e���A�����
	LPDIRECT3DTEXTURE9*	pMeshTex;	// ���b�V���̃e�N�X�`��
} tItemModelData;

typedef struct {
	LPDIRECT3DTEXTURE9 pTextureItemIcon;
	VERTEX_2D ItemVertex[NUM_VERTEX];

	float	fTexPosX;
	float	fTexPosY;
	int		nTexSizeX;
	int		nTexSizeY;

	bool	bLive;					// ����(�\��)�t���O(���f����������̂̂�)
	bool	bHave;					// �����Ă��邩
} tItemIconData;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitItem(LPDIRECT3DDEVICE9);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(LPDIRECT3DDEVICE9);

bool GetItemFlag(eItem);

void SetInfoItem(eItem, D3DXVECTOR3);
void SetInfoItemIcon(int nItem);
void AcquisitionItem(eItem);
void ItemSetting(int);

void DeleteItem();
void DeleteItem(eItem item);