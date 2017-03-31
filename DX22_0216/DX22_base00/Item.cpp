#include "Item.h"
#include "model.h"
#include "shadow.h"
#include "Message.h"
#include "field.h"
#include "Fade.h"
#include<string>

#include <math.h>

#include "sound.h"

using namespace std;
//*****************************************************************************
// �}�N����`
//*****************************************************************************
const string		TORCH_MODEL_FILE_NAME("data/XFILE/torch.x");
const D3DXVECTOR3	TORCH_MODEL_POS(60, 0, 120);
const D3DXVECTOR3	TORCH_MODEL_ROT (10, 10, 10);
const D3DXVECTOR3	TORCH_MODEL_SCALE(10, 10, 10);
const D3DXVECTOR3	TORCH_MODEL_SIZE(80, 80, 80);
const string		LOG_MODEL_FILE_NAME("data/XFILE/log.x");
const D3DXVECTOR3	LOG_MODEL_POS (60, 0, 60);
const D3DXVECTOR3	LOG_MODEL_ROT (10, 10, 10);
const D3DXVECTOR3	LOG_MODEL_SCALE (10, 10, 10);
const D3DXVECTOR3	LOG_MODEL_SIZE(150, 10, 100);
const string		ROPE_MODEL_FILE_NAME("data/XFILE/rope.x");
const D3DXVECTOR3	ROPE_MODEL_POS (-100, 0, -150);
const D3DXVECTOR3	ROPE_MODEL_ROT (10, 10, 10);
const D3DXVECTOR3	ROPE_MODEL_SCALE (10, 10, 10);
const D3DXVECTOR3	ROPE_MODEL_SIZE(100, 10, 100);
const string		BOTTLE_MODEL_FILE_NAME("data/XFILE/bottle.x");
const D3DXVECTOR3	BOTTLE_MODEL_POS (0, 0, -85);
const D3DXVECTOR3	BOTTLE_MODEL_ROT (10, 10, 10);
const D3DXVECTOR3	BOTTLE_MODEL_SCALE (10,10,10);
const D3DXVECTOR3	BOTTLE_MODEL_SIZE(150, 10, 150);

const LPSTR		TORCH_ICON_FILE_NAME("data/TEXTURE/torch_icon.png");
const LPSTR		LOG_ICON_FILE_NAME	("data/TEXTURE/log_icon.png");
const LPSTR		ROPE_ICON_FILE_NAME	("data/TEXTURE/rope_icon.png");
const LPSTR		BOTTLE_ICON_FILE_NAME("data/TEXTURE/bottle_icon.png");
const LPSTR		CLOTH_ICON_FILE_NAME("data/TEXTURE/cloth_icon.png");
const LPSTR		FOOD_ICON_FILE_NAME	("data/TEXTURE/food_icon.png");
const LPSTR		FLIPPERS_ICON_FILE_NAME("data/TEXTURE/flippers_icon.png");

const int ICON_INTERVAL(80);
const int ICON_SIZEX(35);
const int ICON_SIZEY(30);

const LPSTR ITEM_BG_FILE_NAME("data/TEXTURE/item_bg.png");
const int ITEM_BG_SIZE_X(800);
const int ITEM_BG_SIZE_Y(50);

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexItemBg(LPDIRECT3DDEVICE9 pDevice);
void MakeVertexItemIcon(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
tItemModelData g_ItemModel[ITEM_MODEL_NUM_MAX];
tItemIconData g_ItemIcon[ITEM_NUM_MAX];
tItemIconData g_tItem_bg;

bool bEnd;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitItem(LPDIRECT3DDEVICE9 pDevice)
{
	string FileName;
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nCnt = 0; nCnt < ITEM_MODEL_NUM_MAX; nCnt++) {
		g_ItemModel[nCnt].pD3DXMeshModel = NULL;
		//g_ItemModel[nCnt].pD3DXBuffMatModel = NULL;
		g_ItemModel[nCnt].nNumMatModel  = 0;
		bEnd = false;
		//�ʒu�A��]�A�X�P�[���̏����ݒ�
		g_ItemModel[nCnt].posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ItemModel[nCnt].rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ItemModel[nCnt].scaleModel = D3DXVECTOR3(10.0f, 10.0f, 10.0f);

		LPD3DXBUFFER	pMatBuf	= NULL;
		
		switch (nCnt) {
		case ITEM_MODEL_TORCH:
			FileName = TORCH_MODEL_FILE_NAME;
			break;
		case ITEM_MODEL_LOG:
			FileName = LOG_MODEL_FILE_NAME;
			break;
		case ITEM_MODEL_ROPE:
			FileName = ROPE_MODEL_FILE_NAME;
			break;
		case ITEM_MODEL_BOTTLE:
			FileName = BOTTLE_MODEL_FILE_NAME;
			break;
		}
			//X�t�@�C���ǂݍ���
			if (FAILED(D3DXLoadMeshFromX(
				FileName.c_str(),				//X�t�@�C����
				D3DXMESH_SYSTEMMEM,		//���b�V���쐬�̃I�v�V����
				pDevice,				//�f�o�C�X�ւ̃|�C���^
				NULL,					//�אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
				&g_ItemModel[nCnt].pD3DXBuffMatModel,	//�}�e���A���f�[�^���܂ރo�b�t�@
				NULL,					//�G�t�F�N�g�C���X�^���X�ւ̔z����܂ރ|�C���^
				&g_ItemModel[nCnt].nNumMatModel,		//D3DXMATERIAL�\���̂̐�
				&g_ItemModel[nCnt].pD3DXMeshModel		//���b�V���̃|�C���^
				))) {
				//return E_FAIL;
			}
		
		if (!(g_ItemModel[nCnt].pD3DXMeshModel->GetFVF() & D3DFVF_NORMAL)) {
			ID3DXMesh * pTempMesh = NULL;
			g_ItemModel[nCnt].pD3DXMeshModel->CloneMeshFVF(g_ItemModel[nCnt].pD3DXMeshModel->GetOptions(),
				g_ItemModel[nCnt].pD3DXMeshModel->GetFVF() | D3DFVF_NORMAL,
				pDevice,
				&pTempMesh);
			D3DXComputeNormals(pTempMesh, NULL);
			g_ItemModel[nCnt].pD3DXMeshModel->Release();
			g_ItemModel[nCnt].pD3DXMeshModel = pTempMesh;
		}
		g_ItemModel[nCnt].pMeshMat = new D3DMATERIAL9[g_ItemModel[nCnt].nNumMatModel];
		g_ItemModel[nCnt].pMeshTex = new LPDIRECT3DTEXTURE9[g_ItemModel[nCnt].nNumMatModel];
		D3DXMATERIAL * d3Mat = (D3DXMATERIAL *)g_ItemModel[nCnt].pD3DXBuffMatModel->GetBufferPointer();
		for (unsigned int i = 0; i < g_ItemModel[nCnt].nNumMatModel; i++) {
			g_ItemModel[nCnt].pMeshMat[i] = d3Mat[i].MatD3D;
			g_ItemModel[nCnt].pMeshMat[i].Ambient = g_ItemModel[nCnt].pMeshMat[i].Diffuse;
			g_ItemModel[nCnt].pMeshTex[i] = NULL;

			//�g�p���Ă���e�N�X�`��������Γǂݍ���
			if (d3Mat[i].pTextureFilename != NULL &&
				lstrlen(d3Mat[i].pTextureFilename) > 0)
			{
				if (FAILED(D3DXCreateTextureFromFile(
					pDevice,
					d3Mat[i].pTextureFilename,
					&g_ItemModel[nCnt].pMeshTex[i])))
				{
					//return E_FAIL;
				}
			}
		}
		g_ItemModel[nCnt].bHave = false;
		// �e�̐���
		//g_ItemModel[nCnt].nIdxShadow = CreateShadow(g_ItemModel[nCnt].posModel, 25.0f, 25.0f);

		//pMatBuf->Release();
	}

	for (int nCnt = 0; nCnt < ITEM_NUM_MAX; nCnt++) {
		g_ItemIcon[nCnt].bLive = false;
		g_ItemIcon[nCnt].bHave = false;
	}

	// �e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TORCH_ICON_FILE_NAME, &g_ItemIcon[ITEM_TORCH].pTextureItemIcon);
	D3DXCreateTextureFromFile(pDevice, LOG_ICON_FILE_NAME, &g_ItemIcon[ITEM_LOG].pTextureItemIcon);
	D3DXCreateTextureFromFile(pDevice, ROPE_ICON_FILE_NAME, &g_ItemIcon[ITEM_ROPE].pTextureItemIcon);
	D3DXCreateTextureFromFile(pDevice, BOTTLE_ICON_FILE_NAME, &g_ItemIcon[ITEM_BOTTLE].pTextureItemIcon);
	D3DXCreateTextureFromFile(pDevice, CLOTH_ICON_FILE_NAME, &g_ItemIcon[ITEM_CLOTH].pTextureItemIcon);
	D3DXCreateTextureFromFile(pDevice, FOOD_ICON_FILE_NAME, &g_ItemIcon[ITEM_FOOD].pTextureItemIcon);
	D3DXCreateTextureFromFile(pDevice, FLIPPERS_ICON_FILE_NAME, &g_ItemIcon[ITEM_FLIPPERS].pTextureItemIcon);

	// ���W�ݒ�
	for (int nCnt = 0; nCnt < ITEM_NUM_MAX; nCnt++) {
		g_ItemIcon[nCnt].fTexPosX  = 32 + nCnt * ICON_INTERVAL;
		g_ItemIcon[nCnt].fTexPosY  = 8.0f;
		g_ItemIcon[nCnt].nTexSizeX  = ICON_SIZEX;
		g_ItemIcon[nCnt].nTexSizeY  = ICON_SIZEY;
	}

	// �e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, ITEM_BG_FILE_NAME, &g_tItem_bg.pTextureItemIcon);
	// ���W�ݒ�
	g_tItem_bg.fTexPosX = 0.0f;
	g_tItem_bg.fTexPosX = 0.0f;

	MakeVertexItemBg(pDevice);
	MakeVertexItemIcon(pDevice);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitItem(void)
{
	for (int nCnt = 0; nCnt < ITEM_MODEL_NUM_MAX; nCnt++) {
		if (g_ItemModel[nCnt].pD3DXBuffMatModel != NULL) {
			//�o�b�t�@���
			g_ItemModel[nCnt].pD3DXBuffMatModel->Release();
			g_ItemModel[nCnt].pD3DXBuffMatModel = NULL;
		}
		if (g_ItemModel[nCnt].pD3DXMeshModel != NULL) {
			//���b�V�����
			g_ItemModel[nCnt].pD3DXMeshModel->Release();
			g_ItemModel[nCnt].pD3DXMeshModel = NULL;
		}

		DWORD	i;
		// �e�N�X�`���J��
		for (i = 0; i < g_ItemModel[nCnt].nNumMatModel; i++)
		{
			if (g_ItemModel[nCnt].pMeshTex[i] != NULL) {
				g_ItemModel[nCnt].pMeshTex[i]->Release();
				g_ItemModel[nCnt].pMeshTex[i]	= NULL;
			}
		}
		delete[] g_ItemModel[nCnt].pMeshTex;
		g_ItemModel[nCnt].pMeshTex	= NULL;
		delete[] g_ItemModel[nCnt].pMeshMat;
		g_ItemModel[nCnt].pMeshMat	= NULL;
	}

	for (int nCnt = 0; nCnt < ITEM_NUM_MAX; nCnt ++) {
		//�e�N�X�`���̊J��
		if (g_ItemIcon[nCnt].pTextureItemIcon != NULL) {
			g_ItemIcon[nCnt].pTextureItemIcon->Release();
			g_ItemIcon[nCnt].pTextureItemIcon = NULL;
		}
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateItem(void)
{
	/////////////////////////////////////
	if (GetKeyboardTrigger(DIK_3))
		SetGameState(STATE_ENDING);
	/////////////////////////////////////
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	tPlayerData * PlayerData = GetPlayerData();
	int nCnt;

	//MakeVertexItemIcon(pDevice);

	// �A�C�e���l��
	if (GetKeyboardTrigger(DIK_RETURN)) {
		for (int nCnt = 0; nCnt < ITEM_MODEL_NUM_MAX; nCnt++) {
			if (!g_ItemModel[nCnt].bLive)
				continue;
			if (PlayerData->posModel.x < g_ItemModel[nCnt].posModel.x + g_ItemModel[nCnt].sizeModel.x / 2.0f &&
				PlayerData->posModel.x > g_ItemModel[nCnt].posModel.x - g_ItemModel[nCnt].sizeModel.x / 2.0f &&
				PlayerData->posModel.z < g_ItemModel[nCnt].posModel.z + g_ItemModel[nCnt].sizeModel.z / 2.0f &&
				PlayerData->posModel.z > g_ItemModel[nCnt].posModel.z - g_ItemModel[nCnt].sizeModel.z / 2.0f) {
				AcquisitionItem((eItem)nCnt);
			}
			// �e�̈ʒu��ݒ�
			//SetPositionShadow(g_ItemModel[nCnt].nIdxShadow, g_ItemModel[nCnt].posModel);
		}
	}

	// �N���A����
	if (GetFieldNumber() == 13 &&
		PlayerData->posModel.x < -7.0f &&
		PlayerData->posModel.x > -105.0f &&
		PlayerData->posModel.z < 70.0f) {
		for (nCnt = 0; g_ItemIcon[nCnt].bHave && nCnt < ITEM_NUM_MAX; nCnt ++);
		if (nCnt == ITEM_NUM_MAX) {
			SetMessageData(50, 420, 70, "����ŒE�o�ł�������");
			if (GetKeyboardTrigger(DIK_RETURN)) {
				StartFadeOut();
				bEnd = true;
			}
			if (bEnd && GetFade() == FADE_NONE)
				SetGameState(STATE_ENDING);
		} else if (nCnt != ITEM_NUM_MAX) {
			SetMessageData(50, 420, 90, "�C�J�_�𒼂��ΒE�o�ł���������....");
		}
	}

	//�f�o�b�O�R�}���h
	if (GetKeyboardTrigger(DIK_F1)) {
		AcquisitionItem((eItem)0);
	}
	if (GetKeyboardTrigger(DIK_F2)) {
		AcquisitionItem((eItem)1);
	}
	if (GetKeyboardTrigger(DIK_F3)) {
		AcquisitionItem((eItem)2);
	}
	if (GetKeyboardTrigger(DIK_F4)) {
		AcquisitionItem((eItem)3);
	}
	if (GetKeyboardTrigger(DIK_F5)) {
		AcquisitionItem((eItem)4);
	}
	if (GetKeyboardTrigger(DIK_F6)) {
		AcquisitionItem((eItem)5);
	}
	if (GetKeyboardTrigger(DIK_F7)) {
		AcquisitionItem((eItem)6);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawItem(LPDIRECT3DDEVICE9 pDevice)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATERIAL * 	pD3DXMat;
	D3DMATERIAL9	matDef;

	D3DXMATRIX mtxScale, mtxRot, mtxTrans;

	MakeVertexItemBg(pDevice);
	MakeVertexItemIcon(pDevice);

	

	for (int nCnt = 0; nCnt < ITEM_MODEL_NUM_MAX; nCnt++) {
		if (!g_ItemModel[nCnt].bLive || g_ItemModel[nCnt].bHave)
			continue;

		pDevice->SetFVF(g_ItemModel[nCnt].pD3DXMeshModel->GetFVF());

		//���[���h�}�g���N�X�̏�����
		D3DXMatrixIdentity(&g_ItemModel[nCnt].mtxWorld);	// Identity:�P�ʁ���

												//���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �X�P�[���𔽉f
		D3DXMatrixScaling(
			&mtxScale,		//�i�[��
			g_ItemModel[nCnt].scaleModel.x,
			g_ItemModel[nCnt].scaleModel.y,
			g_ItemModel[nCnt].scaleModel.z
			);
		D3DXMatrixMultiply(
			&g_ItemModel[nCnt].mtxWorld,	//�i�[��(A*B)
			&g_ItemModel[nCnt].mtxWorld,	//A
			&mtxScale		//B
			);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(
			&mtxRot,		//�i�[��
			g_ItemModel[nCnt].rotModel.y,	//���[(���E)
			g_ItemModel[nCnt].rotModel.x,	//�s�b�`(�O��)
			g_ItemModel[nCnt].rotModel.z	//���[��(��])
			);
		D3DXMatrixMultiply(
			&g_ItemModel[nCnt].mtxWorld,	//�i�[��(A*B)
			&g_ItemModel[nCnt].mtxWorld,	//A
			&mtxRot			//B
			);

		// �ړ��𔽉f
		D3DXMatrixTranslation(
			&mtxTrans,		//�i�[��
			g_ItemModel[nCnt].posModel.x,	//
			g_ItemModel[nCnt].posModel.y,	//
			g_ItemModel[nCnt].posModel.z	//
			);
		D3DXMatrixMultiply(
			&g_ItemModel[nCnt].mtxWorld,	//�i�[��(A*B)
			&g_ItemModel[nCnt].mtxWorld,	//A
			&mtxTrans		//B
			);

		//���[���h�}�g���N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_ItemModel[nCnt].mtxWorld);

		//�}�e���A�����ɑ΂���|�C���^���擾
		pD3DXMat = (D3DXMATERIAL*)g_ItemModel[nCnt].pD3DXBuffMatModel->GetBufferPointer();


		for (int nCntMat = 0; nCntMat < (int)g_ItemModel[nCnt].nNumMatModel; nCntMat ++) {
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_ItemModel[nCnt].pMeshTex[nCntMat]);
			//�`��
			g_ItemModel[nCnt].pD3DXMeshModel->DrawSubset(nCntMat);
		}

		//�}�e���A�������ɖ߂�
		pDevice->SetMaterial(&matDef);
	}

	
	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_tItem_bg.pTextureItemIcon);
	//�|���S���`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,
		NUM_POLYGON,
		&g_tItem_bg.ItemVertex[0],
		sizeof(VERTEX_2D));

	// �A�C�R��
	for (int nCnt = 0; nCnt < ITEM_NUM_MAX; nCnt ++) {
		if (!g_ItemIcon[nCnt].bHave)
			continue;
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_ItemIcon[nCnt].pTextureItemIcon);
		//�|���S���`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,
			NUM_POLYGON,
			&g_ItemIcon[nCnt].ItemVertex[0],
			sizeof(VERTEX_2D));
	}
}

bool GetItemFlag(eItem ItemNum) {
	return g_ItemIcon[ItemNum].bHave;
}

void SetInfoItem(eItem item, D3DXVECTOR3 itemPos) {
	if (!g_ItemModel[item].bHave) {
		g_ItemModel[item].bLive = true;
		switch (item) {
		case ITEM_TORCH:
			g_ItemModel[item].posModel = TORCH_MODEL_POS;
			g_ItemModel[item].sizeModel = TORCH_MODEL_SIZE;
			break;
		case ITEM_LOG:
			g_ItemModel[item].posModel = LOG_MODEL_POS;
			g_ItemModel[item].sizeModel = LOG_MODEL_SIZE;
			break;
		case ITEM_ROPE:
			g_ItemModel[item].posModel = ROPE_MODEL_POS;
			g_ItemModel[item].sizeModel = ROPE_MODEL_SIZE;
			break;
		case ITEM_BOTTLE:
			g_ItemModel[item].posModel = BOTTLE_MODEL_POS;
			g_ItemModel[item].sizeModel = BOTTLE_MODEL_SIZE;
			break;
		default:
			break;

		}
		g_ItemModel[item].nIdxShadow = CreateShadow(g_ItemModel[item].posModel, 25.0f, 25.0f);
	}
}

void SetInfoItemIcon(int nItem) {
	g_ItemIcon[nItem].bLive = true;
}

// �A�C�e���̊l��
void AcquisitionItem(eItem Item) {
	g_ItemIcon[Item].bHave = true;
	PlaySound(SOUND_LABEL_SE_DECIDE);
	if (Item < ITEM_MODEL_NUM_MAX) {
		g_ItemModel[Item].bHave = true;
	}
	switch (Item) {
	case ITEM_TORCH:
		SetMessageData(50, 420, 120, "��������ɓ���܂���");
		break;
	case ITEM_LOG:
		SetMessageData(50, 420, 120, "�ۑ�����ɓ���܂���");
		break;
	case ITEM_ROPE:
		SetMessageData(50, 420, 120, "���[�v����ɓ���܂���");
		break;
	case ITEM_BOTTLE:
		SetMessageData(50, 420, 120, "�r���Ɛ�����ɓ���܂���");
		break;
	case ITEM_CLOTH:
		SetMessageData(50, 420, 120, "�z����ɓ���܂���");
		break;
	case ITEM_FOOD:
		SetMessageData(50, 420, 120, "�H�Ƃ���ɓ���܂���");
		break;
	case ITEM_FLIPPERS:
		SetMessageData(50, 420, 120, "���Ђ����ɓ���܂���");
		break;

	default:
		break;
	}
	ReleaseShadow(g_ItemModel[Item].nIdxShadow);
}

void ItemSetting(int nMap) {
	switch (nMap) {
	case 0:

		break; 
	case 1:

		break;
	case 2:

		break;
	case 3:
		SetInfoItem(ITEM_BOTTLE, BOTTLE_MODEL_POS);

		break;
	case 4:

		break;
	case 5:
		SetInfoItem(ITEM_LOG, LOG_MODEL_POS);
		SetInfoItem(ITEM_TORCH, TORCH_MODEL_POS);

		break;
	case 6:

		break;
	case 7:

		break;
	case 8:

		break;
	case 9:

		break;
	case 10:

		break;
	case 11:

		break;
	case 12:

		break;
	case 13:

		break;
	case 14:

		break;
	case 15:
		SetInfoItem(ITEM_ROPE, ROPE_MODEL_POS);

		break;

	default:
		break;
	}
}

void DeleteItem() {
	for (int nCnt = 0; nCnt < ITEM_MODEL_NUM_MAX; nCnt++) {
		if (!g_ItemModel[nCnt].bLive)
			continue;
		g_ItemModel[nCnt].bLive	= false;
		ReleaseShadow(g_ItemModel[nCnt].nIdxShadow);
	}
}

void DeleteItem(eItem item) {
	//g_ItemModel[item].
}


//===========================================================
//	���_�̐ݒ�
//===========================================================
void MakeVertexItemBg(LPDIRECT3DDEVICE9 pDevice) {
	g_tItem_bg.ItemVertex[0].vtx = D3DXVECTOR3(g_tItem_bg.fTexPosX, g_tItem_bg.fTexPosY, 0.0f);	//(X, Y, Z)
	g_tItem_bg.ItemVertex[1].vtx = D3DXVECTOR3(g_tItem_bg.fTexPosX + ITEM_BG_SIZE_X, g_tItem_bg.fTexPosY, 0.0f);
	g_tItem_bg.ItemVertex[2].vtx = D3DXVECTOR3(g_tItem_bg.fTexPosX, g_tItem_bg.fTexPosY + ITEM_BG_SIZE_Y, 0.0f);
	g_tItem_bg.ItemVertex[3].vtx = D3DXVECTOR3(g_tItem_bg.fTexPosX + ITEM_BG_SIZE_X, g_tItem_bg.fTexPosY + ITEM_BG_SIZE_Y, 0.0f);

	g_tItem_bg.ItemVertex[0].rhw =
		g_tItem_bg.ItemVertex[1].rhw =
		g_tItem_bg.ItemVertex[2].rhw =
		g_tItem_bg.ItemVertex[3].rhw = 1.0f;	//���ׂĂ�1.0f������

	g_tItem_bg.ItemVertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_tItem_bg.ItemVertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_tItem_bg.ItemVertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_tItem_bg.ItemVertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	g_tItem_bg.ItemVertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_tItem_bg.ItemVertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_tItem_bg.ItemVertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_tItem_bg.ItemVertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

void MakeVertexItemIcon(LPDIRECT3DDEVICE9 pDevice) {

	for (int nCnt = 0; nCnt < ITEM_NUM_MAX; nCnt ++) {
		if (!g_ItemIcon[nCnt].bHave)
			continue;
		g_ItemIcon[nCnt].ItemVertex[0].vtx = D3DXVECTOR3(g_ItemIcon[nCnt].fTexPosX, g_ItemIcon[nCnt].fTexPosY, 0.0f);	//(X, Y, Z)
		g_ItemIcon[nCnt].ItemVertex[1].vtx = D3DXVECTOR3(g_ItemIcon[nCnt].fTexPosX + g_ItemIcon[nCnt].nTexSizeX, g_ItemIcon[nCnt].fTexPosY, 0.0f);
		g_ItemIcon[nCnt].ItemVertex[2].vtx = D3DXVECTOR3(g_ItemIcon[nCnt].fTexPosX, g_ItemIcon[nCnt].fTexPosY + g_ItemIcon[nCnt].nTexSizeY, 0.0f);
		g_ItemIcon[nCnt].ItemVertex[3].vtx = D3DXVECTOR3(g_ItemIcon[nCnt].fTexPosX + g_ItemIcon[nCnt].nTexSizeX, g_ItemIcon[nCnt].fTexPosY + g_ItemIcon[nCnt].nTexSizeY, 0.0f);

		g_ItemIcon[nCnt].ItemVertex[0].rhw =
			g_ItemIcon[nCnt].ItemVertex[1].rhw =
			g_ItemIcon[nCnt].ItemVertex[2].rhw =
			g_ItemIcon[nCnt].ItemVertex[3].rhw = 1.0f;	//���ׂĂ�1.0f������

		g_ItemIcon[nCnt].ItemVertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ItemIcon[nCnt].ItemVertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ItemIcon[nCnt].ItemVertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ItemIcon[nCnt].ItemVertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		g_ItemIcon[nCnt].ItemVertex[0].tex = D3DXVECTOR2(0.0f,0.0f);
		g_ItemIcon[nCnt].ItemVertex[1].tex = D3DXVECTOR2(1.0f,0.0f);
		g_ItemIcon[nCnt].ItemVertex[2].tex = D3DXVECTOR2(0.0f,1.0f);
		g_ItemIcon[nCnt].ItemVertex[3].tex = D3DXVECTOR2(1.0f,1.0f);
	}
}