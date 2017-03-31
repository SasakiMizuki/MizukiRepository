//=============================================================================
//
// ���f������ [model.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "model.h"
#include "main.h"
#include "shadow.h"
#include "effect.h"
#include "Object.h"

#include <math.h>

#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FILE_NAME "data/XFILE/tokage.x"
const float MOVE_VOL (3.5);
const float ROTE_VOL (0.05);
const float SCALE_VOL (0.5);
const float JUMP_VOL(2.4f);
const float GRAVITY_VOL(-0.4f);
const D3DXVECTOR3 DEFAULTPLAYER_POS (0.0f,8.0f,0.0f);

//const char FILE_NAME[] = "data/XFILE/tokage.x";

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
tPlayerData Player;


//=============================================================================
// ����������
//=============================================================================
HRESULT InitModel(LPDIRECT3DDEVICE9 pDevice)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	Player.pD3DXMeshModel = NULL;
	//Player.pD3DXBuffMatModel = NULL;
	Player.nNumMatModel  = 0;
	
	//�ʒu�A��]�A�X�P�[���̏����ݒ�
	Player.posModel = DEFAULTPLAYER_POS;
	Player.rotModel = D3DXVECTOR3(0.0f,0.0f,0.0f);
	Player.scaleModel = D3DXVECTOR3(10.0f,10.0f,10.0f);

	Player.bPlayerMove = true;
	
	LPD3DXBUFFER	pMatBuf	= NULL;

	//X�t�@�C���ǂݍ���
	if(FAILED(D3DXLoadMeshFromX(
		FILE_NAME,				//X�t�@�C����
		D3DXMESH_SYSTEMMEM,		//���b�V���쐬�̃I�v�V����
		pDevice,				//�f�o�C�X�ւ̃|�C���^
		NULL,					//�אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
		&Player.pD3DXBuffMatModel,	//�}�e���A���f�[�^���܂ރo�b�t�@
		NULL,					//�G�t�F�N�g�C���X�^���X�ւ̔z����܂ރ|�C���^
		&Player.nNumMatModel,		//D3DXMATERIAL�\���̂̐�
		&Player.pD3DXMeshModel		//���b�V���̃|�C���^
	))){
		return E_FAIL;
	}

	if(!(Player.pD3DXMeshModel->GetFVF() & D3DFVF_NORMAL)){
		ID3DXMesh * pTempMesh = NULL;
		Player.pD3DXMeshModel->CloneMeshFVF(Player.pD3DXMeshModel->GetOptions(),
			Player.pD3DXMeshModel->GetFVF() | D3DFVF_NORMAL,
			pDevice,
			&pTempMesh);
		D3DXComputeNormals(pTempMesh, NULL);
		Player.pD3DXMeshModel->Release();
		Player.pD3DXMeshModel = pTempMesh;
	}
	Player.pMeshMat = new D3DMATERIAL9[Player.nNumMatModel];
	Player.pMeshTex = new LPDIRECT3DTEXTURE9[Player.nNumMatModel];
	D3DXMATERIAL * d3Mat = (D3DXMATERIAL *)Player.pD3DXBuffMatModel->GetBufferPointer();
	for(unsigned int i = 0; i < Player.nNumMatModel; i++){
		Player.pMeshMat[i] = d3Mat[i].MatD3D;
		Player.pMeshMat[i].Ambient = Player.pMeshMat[i].Diffuse;
		Player.pMeshTex[i] = NULL;

		//�g�p���Ă���e�N�X�`��������Γǂݍ���
		if(d3Mat[i].pTextureFilename != NULL &&
			lstrlen(d3Mat[i].pTextureFilename) > 0)
		{
			if(FAILED(D3DXCreateTextureFromFile(
						pDevice,
						d3Mat[i].pTextureFilename,
						&Player.pMeshTex[i])))
						{
							return E_FAIL;
						}
		}
	}

	Player.posModel = DEFAULTPLAYER_POS;
	Player.rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Player.scaleModel = D3DXVECTOR3(10.0f, 10.0f, 10.0f);

	// �e�̐���
	Player.nIdxShadow = CreateShadow( Player.posModel, 25.0f, 25.0f);
	
	//pMatBuf->Release();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitModel(void)
{
	if(Player.pD3DXBuffMatModel != NULL){
		//�o�b�t�@���
		Player.pD3DXBuffMatModel->Release();
		Player.pD3DXBuffMatModel = NULL;
	}
	if(Player.pD3DXMeshModel != NULL){
		//���b�V�����
		Player.pD3DXMeshModel->Release();
		Player.pD3DXMeshModel = NULL;
	}
	
	DWORD	i;
	// �e�N�X�`���J��
	for( i = 0; i < Player.nNumMatModel; i++ )
	{
		if(Player.pMeshTex[i] != NULL){
			Player.pMeshTex[i]->Release();
			Player.pMeshTex[i]	= NULL;
		}
	}
	delete [] Player.pMeshTex;
	Player.pMeshTex	= NULL;
	delete [] Player.pMeshMat;
	Player.pMeshMat	= NULL;
	
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateModel(void)
{
	///////////////////////////////////////
	//if (GetKeyboardTrigger(DIK_3))
	//	SetGameState(STATE_ENDING);
	///////////////////////////////////////
	//���s�ړ�
	/*if(GetKeyboardPress(DIK_RIGHT) && Player.bPlayerMove){
		Player.moveModel.z = -cos(Player.rotModel.y + PI / 2) * MOVE_VOL;
		Player.moveModel.x = -sin(Player.rotModel.y + PI / 2) * MOVE_VOL;
	}
	if(GetKeyboardPress(DIK_LEFT) && Player.bPlayerMove){
		Player.moveModel.z = cos(Player.rotModel.y + PI / 2) * MOVE_VOL;
		Player.moveModel.x = sin(Player.rotModel.y + PI / 2) * MOVE_VOL;
	}*/
	if((GetKeyboardPress(DIK_UP) || GetKeyboardPress(DIK_W)) && Player.bPlayerMove){
		Player.moveModel.z = -cos(Player.rotModel.y) * MOVE_VOL;
		Player.moveModel.x = -sin(Player.rotModel.y) * MOVE_VOL;
		//if (GetKeyboardPress(DIK_RIGHT)) {
		//	Player.moveModel.z = -cos(Player.rotModel.y + PI / 4) * MOVE_VOL;
		//	Player.moveModel.x = -sin(Player.rotModel.y + PI / 4) * MOVE_VOL;
		//}
		//else if (GetKeyboardPress(DIK_LEFT)) {
		//	Player.moveModel.z = cos(Player.rotModel.y + PI / 4 * 3) * MOVE_VOL;
		//	Player.moveModel.x = sin(Player.rotModel.y + PI / 4 * 3) * MOVE_VOL;
		//}
	}
	/*if(GetKeyboardPress(DIK_DOWN) && Player.bPlayerMove){
		Player.moveModel.z = cos(Player.rotModel.y) * MOVE_VOL;
		Player.moveModel.x = sin(Player.rotModel.y) * MOVE_VOL;
		if (GetKeyboardPress(DIK_RIGHT)) {
			Player.moveModel.z = -cos(Player.rotModel.y + PI / 4 * 3) * MOVE_VOL;
			Player.moveModel.x = -sin(Player.rotModel.y + PI / 4 * 3) * MOVE_VOL;
		} else if (GetKeyboardPress(DIK_LEFT)) {
			Player.moveModel.z = cos(Player.rotModel.y + PI / 4) * MOVE_VOL;
			Player.moveModel.x = sin(Player.rotModel.y + PI / 4) * MOVE_VOL;
		}
	}*/
	// �W�����v
	if(GetKeyboardTrigger(DIK_SPACE) && !Player.bPlayerJump){
		Player.bPlayerJump = true;
		PlaySound(SOUND_LABEL_SE_JUMP);
	}

	if (Player.bPlayerJump) {
		Player.moveModel.y = JUMP_VOL * Player.fJumpTime + 1.0f / 2.0f * GRAVITY_VOL * Player.fJumpTime * Player.fJumpTime;
		Player.fJumpTime ++;
	}
	/*
	if(GetKeyboardPress(DIK_I)){
		Player.posModel.y -= MOVE_VOL;
	}*/
	HitChecktoObject();

	// �ړ��ʍ��Z
	Player.posModel += D3DXVECTOR3(Player.moveModel.x, Player.moveModel.y, Player.moveModel.z);

	if (Player.posModel.y < DEFAULTPLAYER_POS.y && Player.bPlayerJump) {
		Player.bPlayerJump = false;
		Player.moveModel.y = 0.0f;
		Player.posModel.y = DEFAULTPLAYER_POS.y;
		Player.fJumpTime = 0;
	}

	Player.moveModel = D3DXVECTOR3(0, 0, 0);

	//��]
	if(GetKeyboardPress(DIK_A) || GetKeyboardPress(DIK_LEFT)){
		Player.rotModel.y -= ROTE_VOL;
	}
	if(GetKeyboardPress(DIK_D) || GetKeyboardPress(DIK_RIGHT)){
		Player.rotModel.y += ROTE_VOL;
	}

	//�g��k��
	/*if(GetKeyboardPress(DIK_Q)){
		Player.scaleModel.x += SCALE_VOL;
	}
	if(GetKeyboardPress(DIK_W)){
		Player.scaleModel.y += SCALE_VOL;
	}
	if(GetKeyboardPress(DIK_E)){
		Player.scaleModel.z += SCALE_VOL;
	}
	if(GetKeyboardPress(DIK_A)){
		Player.scaleModel.x -= SCALE_VOL;
	}
	if(GetKeyboardPress(DIK_S)){
		Player.scaleModel.y -= SCALE_VOL;
	}
	if(GetKeyboardPress(DIK_D)){
		Player.scaleModel.z -= SCALE_VOL;
	}
	*/
	// �e�̈ʒu��ݒ�
	SetPositionShadow(Player.nIdxShadow, Player.posModel);

	// Effect Setting
	SetEffect(Player.posModel, D3DXVECTOR3(0,0,0), D3DXCOLOR(1,1,0,1), 20, 20, 30);
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawModel(LPDIRECT3DDEVICE9 pDevice)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	D3DXMATERIAL * 	pD3DXMat;
	D3DMATERIAL9	matDef;
	
	D3DXMATRIX mtxScale,mtxRot,mtxTrans;
	
	pDevice->SetFVF(Player.pD3DXMeshModel->GetFVF());

	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&Player.mtxWorld);	// Identity:�P�ʁ���

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);
	
	// �X�P�[���𔽉f
	D3DXMatrixScaling(
		&mtxScale,		//�i�[��
		Player.scaleModel.x,
		Player.scaleModel.y,
		Player.scaleModel.z
	);
	D3DXMatrixMultiply(
		&Player.mtxWorld,	//�i�[��(A*B)
		&Player.mtxWorld,	//A
		&mtxScale		//B
	);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(
		&mtxRot,		//�i�[��
		Player.rotModel.y,	//���[(���E)
		Player.rotModel.x,	//�s�b�`(�O��)
		Player.rotModel.z	//���[��(��])
	);
	D3DXMatrixMultiply(
		&Player.mtxWorld,	//�i�[��(A*B)
		&Player.mtxWorld,	//A
		&mtxRot			//B
	);

	// �ړ��𔽉f
	D3DXMatrixTranslation(
		&mtxTrans,		//�i�[��
		Player.posModel.x,	//
		Player.posModel.y,	//
		Player.posModel.z	//
	);
	D3DXMatrixMultiply(
		&Player.mtxWorld,	//�i�[��(A*B)
		&Player.mtxWorld,	//A
		&mtxTrans		//B
	);

	//���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD,&Player.mtxWorld);

	//�}�e���A�����ɑ΂���|�C���^���擾
	pD3DXMat = (D3DXMATERIAL*)Player.pD3DXBuffMatModel->GetBufferPointer();
	

	for(int nCntMat = 0; nCntMat < (int)Player.nNumMatModel; nCntMat ++){
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, Player.pMeshTex[nCntMat]);
		//�`��
		Player.pD3DXMeshModel->DrawSubset(nCntMat);
	}
	
	//�}�e���A�������ɖ߂�
	pDevice->SetMaterial(&matDef);
}

D3DXVECTOR3 GetModelPos(){
	return Player.posModel;
}

D3DXVECTOR3 GetModelRot(){
	return Player.rotModel;
}

tPlayerData * GetPlayerData() {
	return &Player;
}

void SetPlayerCanMove(bool bPlayerMove) {
	Player.bPlayerMove = bPlayerMove;
}