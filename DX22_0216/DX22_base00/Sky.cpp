//=============================================================================
//
// ���f������ [model.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "Sky.h"
#include "shadow.h"
#include "effect.h"
#include "Object.h"

#include <math.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FILE_NAME "data/XFILE/sky.x"
const float MOVE_VOL(3.5);
const float ROTE_VOL(0.05);
const float SCALE_VOL(0.5);
const float JUMP_VOL(4.0f);
const float GRAVITY_VOL(-0.4f);
const D3DXVECTOR3 DEFAULTSKY_POS(0.0f, 10.0f, 0.0f);

//const char FILE_NAME[] = "data/XFILE/tokage.x";

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
tSkyData Sky;


//=============================================================================
// ����������
//=============================================================================
HRESULT InitSky(LPDIRECT3DDEVICE9 pDevice)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();

	Sky.pD3DXMeshModel = NULL;
	//Sky.pD3DXBuffMatModel = NULL;
	Sky.nNumMatModel  = 0;

	LPD3DXBUFFER	pMatBuf	= NULL;

	//X�t�@�C���ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(
		FILE_NAME,				//X�t�@�C����
		D3DXMESH_SYSTEMMEM,		//���b�V���쐬�̃I�v�V����
		pDevice,				//�f�o�C�X�ւ̃|�C���^
		NULL,					//�אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
		&Sky.pD3DXBuffMatModel,	//�}�e���A���f�[�^���܂ރo�b�t�@
		NULL,					//�G�t�F�N�g�C���X�^���X�ւ̔z����܂ރ|�C���^
		&Sky.nNumMatModel,		//D3DXMATERIAL�\���̂̐�
		&Sky.pD3DXMeshModel		//���b�V���̃|�C���^
		))) {
		return E_FAIL;
	}

	if (!(Sky.pD3DXMeshModel->GetFVF() & D3DFVF_NORMAL)) {
		ID3DXMesh * pTempMesh = NULL;
		Sky.pD3DXMeshModel->CloneMeshFVF(Sky.pD3DXMeshModel->GetOptions(),
			Sky.pD3DXMeshModel->GetFVF() | D3DFVF_NORMAL,
			pDevice,
			&pTempMesh);
		D3DXComputeNormals(pTempMesh, NULL);
		Sky.pD3DXMeshModel->Release();
		Sky.pD3DXMeshModel = pTempMesh;
	}
	Sky.pMeshMat = new D3DMATERIAL9[Sky.nNumMatModel];
	Sky.pMeshTex = new LPDIRECT3DTEXTURE9[Sky.nNumMatModel];
	D3DXMATERIAL * d3Mat = (D3DXMATERIAL *)Sky.pD3DXBuffMatModel->GetBufferPointer();
	for (unsigned int i = 0; i < Sky.nNumMatModel; i++) {
		Sky.pMeshMat[i] = d3Mat[i].MatD3D;
		Sky.pMeshMat[i].Ambient = Sky.pMeshMat[i].Diffuse;
		Sky.pMeshTex[i] = NULL;

		//�g�p���Ă���e�N�X�`��������Γǂݍ���
		if (d3Mat[i].pTextureFilename != NULL &&
			lstrlen(d3Mat[i].pTextureFilename) > 0)
		{
			if (FAILED(D3DXCreateTextureFromFile(
				pDevice,
				d3Mat[i].pTextureFilename,
				&Sky.pMeshTex[i])))
			{
				return E_FAIL;
			}
		}
	}

	//�ʒu�A��]�A�X�P�[���̏����ݒ�
	Sky.posModel = DEFAULTSKY_POS;
	Sky.rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Sky.scaleModel = D3DXVECTOR3(8.0f, 8.0f, 8.0f);

	// �e�̐���
	//Sky.nIdxShadow = CreateShadow(Sky.posModel, 25.0f, 25.0f);

	//pMatBuf->Release();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitSky(void)
{
	if (Sky.pD3DXBuffMatModel != NULL) {
		//�o�b�t�@���
		Sky.pD3DXBuffMatModel->Release();
		Sky.pD3DXBuffMatModel = NULL;
	}
	if (Sky.pD3DXMeshModel != NULL) {
		//���b�V�����
		Sky.pD3DXMeshModel->Release();
		Sky.pD3DXMeshModel = NULL;
	}

	DWORD	i;
	// �e�N�X�`���J��
	for (i = 0; i < Sky.nNumMatModel; i++)
	{
		if (Sky.pMeshTex[i] != NULL) {
			Sky.pMeshTex[i]->Release();
			Sky.pMeshTex[i]	= NULL;
		}
	}
	delete[] Sky.pMeshTex;
	Sky.pMeshTex	= NULL;
	delete[] Sky.pMeshMat;
	Sky.pMeshMat	= NULL;

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSky(void)
{
	
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawSky(LPDIRECT3DDEVICE9 pDevice)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATERIAL * 	pD3DXMat;
	D3DMATERIAL9	matDef;

	D3DXMATRIX mtxScale, mtxRot, mtxTrans;

	pDevice->SetFVF(Sky.pD3DXMeshModel->GetFVF());

	////���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&Sky.mtxWorld);	// Identity:�P�ʁ���

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(
		&mtxScale,		//�i�[��
		Sky.scaleModel.x,
		Sky.scaleModel.y,
		Sky.scaleModel.z
		);
	D3DXMatrixMultiply(
		&Sky.mtxWorld,	//�i�[��(A*B)
		&Sky.mtxWorld,	//A
		&mtxScale		//B
		);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(
		&mtxRot,		//�i�[��
		Sky.rotModel.y,	//���[(���E)
		Sky.rotModel.x,	//�s�b�`(�O��)
		Sky.rotModel.z	//���[��(��])
		);
	D3DXMatrixMultiply(
		&Sky.mtxWorld,	//�i�[��(A*B)
		&Sky.mtxWorld,	//A
		&mtxRot			//B
		);

	// �ړ��𔽉f
	D3DXMatrixTranslation(
		&mtxTrans,		//�i�[��
		Sky.posModel.x,	//
		Sky.posModel.y,	//
		Sky.posModel.z	//
		);
	D3DXMatrixMultiply(
		&Sky.mtxWorld,	//�i�[��(A*B)
		&Sky.mtxWorld,	//A
		&mtxTrans		//B
		);

	//���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &Sky.mtxWorld);

	//�}�e���A�����ɑ΂���|�C���^���擾
	pD3DXMat = (D3DXMATERIAL*)Sky.pD3DXBuffMatModel->GetBufferPointer();


	for (int nCntMat = 0; nCntMat < (int)Sky.nNumMatModel; nCntMat ++) {
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, Sky.pMeshTex[nCntMat]);
		//�`��
		Sky.pD3DXMeshModel->DrawSubset(nCntMat);
	}

	//�}�e���A�������ɖ߂�
	pDevice->SetMaterial(&matDef);
}