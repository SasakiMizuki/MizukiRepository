//=============================================================================
//
// �n�ʏ��� [field.cpp]
//
//=============================================================================
#include "field.h"
#include "input.h"
#include "model.h"
#include "Fade.h"
#include "Object.h"
#include "Item.h"
#include "3DObject.h"
#include "Message.h"
#include "explosion.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_FIELD_GRASS	"data/TEXTURE/BGTEST.png"						// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_FIELD_BEACH	"data/TEXTURE/beach.jpg"						// �ǂݍ��ރe�N�X�`���t�@�C����

#define	FIELD_SIZE_X	(5.0f)										// 1�l�p�`������̒n�ʂ̃T�C�Y(X����)
#define	FIELD_SIZE_Z	(5.0f)										// 1�l�p�`������̒n�ʂ̃T�C�Y(Z����)

const int FIELD_DIVIDE_X(4);
const int FIELD_DIVIDE_Z(4); 
const float FLOAT_FIELD_DIVIDE_Z(4);
const float FLOAT_FIELD_DIVIDE_X(4);

#define FILED_TYPE	(0)

const float LIMIT_FIELD = 250;
const int FIRST(13);

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice,
	int nNumBlockX, int nNumBlockZ,
	float fSizeBlockX, float fSizeBlockZ);
void SetVerTexField();

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
FIELD g_tField;
static SOUND_LABEL g_eMusic;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitField( LPDIRECT3DDEVICE9 pDevice,
	int nNumBlockX, int nNumBlockZ,
	float fSizeBlockX, float fSizeBlockZ)
{

	// �e�N�X�`���̓ǂݍ���
	if (&g_tField.pD3DTextureField[FIELD_GRASS] != NULL) {
		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			TEXTURE_FIELD_GRASS,			// �t�@�C���̖��O
			&g_tField.pD3DTextureField[FIELD_GRASS]);	// �ǂݍ��ރ������[	
	}
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FIELD_BEACH,			// �t�@�C���̖��O
		&g_tField.pD3DTextureField[FIELD_BEACH]);	// �ǂݍ��ރ������[
	g_tField.FieldType = FIELD_GRASS;
	g_tField.nFieldNumber = FIRST;

	SetObjectinField();
	// ���_���̍쐬
	MakeVertexField(pDevice, nNumBlockX, nNumBlockZ, fSizeBlockX, fSizeBlockZ);

	g_eMusic = SOUND_LABEL_BGM_WAVE;

	StartFadeIn();
	ItemSetting(g_tField.nFieldNumber);
	SetObjectinField();
	Setting3DObject(g_tField.nFieldNumber);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitField(void)
{
	for (int a = 0; a < MAX_FIELD_TYPE; a ++) {
		if (g_tField.pD3DTextureField != NULL)
		{// �e�N�X�`���̊J��
			g_tField.pD3DTextureField[a]->Release();
			g_tField.pD3DTextureField[a] = NULL;
		}
	}

	if(g_tField.pD3DVtxBuffField != NULL){
		//���_�o�b�t�@�̉��
		g_tField.pD3DVtxBuffField->Release();
		g_tField.pD3DVtxBuffField = NULL;
	}
	
	if(g_tField.pD3DIdxBuffField){
		// �C���f�b�N�X�o�b�t�@�̉��
		g_tField.pD3DIdxBuffField->Release();
		g_tField.pD3DIdxBuffField = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateField(void)
{
	static bool bFade = false;
	static bool bMove = false;
	tPlayerData * PlayerData = GetPlayerData();
	D3DXVECTOR3 exPOS = D3DXVECTOR3(PlayerData->posModel.x,PlayerData->posModel.y + 30,PlayerData->posModel.z);


	// ���ֈړ�
	if (PlayerData->posModel.x > LIMIT_FIELD && ((g_tField.nFieldNumber % 4) != 3)) {
		PlayerData->posModel.x = LIMIT_FIELD;
		StartFadeOut();
		DeleteObject();
		Delete3DObject();
		DeleteItem();
		bFade = true;
	} else if(PlayerData->posModel.x > LIMIT_FIELD && ((g_tField.nFieldNumber % 4) == 3)){
		PlayerData->posModel.x = LIMIT_FIELD;
	}
	if (bFade && PlayerData->bPlayerMove && PlayerData->posModel.x == LIMIT_FIELD) {
		PlayerData->posModel.x = -LIMIT_FIELD;
		bFade = false;
		g_tField.nFieldNumber ++;
		ItemSetting(g_tField.nFieldNumber);
		SetVerTexField();
		SetObjectinField(); 
		Setting3DObject(g_tField.nFieldNumber);
		StartFadeIn();
		if (g_tField.nFieldNumber <= 11 && g_eMusic == SOUND_LABEL_BGM_WAVE) {
			StopSound();
			g_eMusic = SOUND_LABEL_BGM_BIRD;
			PlaySound(SOUND_LABEL_BGM_BIRD);
		}
		if (g_tField.nFieldNumber > 11 && g_eMusic == SOUND_LABEL_BGM_BIRD) {
			StopSound();
			g_eMusic = SOUND_LABEL_BGM_WAVE;
			PlaySound(SOUND_LABEL_BGM_WAVE);
		}
	}
	// ���ֈړ�
	if (PlayerData->posModel.x < -LIMIT_FIELD && (g_tField.nFieldNumber % 4)) {
		PlayerData->posModel.x = -LIMIT_FIELD;
		StartFadeOut();
		DeleteObject();
		Delete3DObject();
		DeleteItem();
		bFade = true;
	} else if (PlayerData->posModel.x < -LIMIT_FIELD && !(g_tField.nFieldNumber % 4)) {
		PlayerData->posModel.x = -LIMIT_FIELD;
	}
	if (bFade && PlayerData->bPlayerMove && PlayerData->posModel.x == -LIMIT_FIELD) {
		PlayerData->posModel.x = LIMIT_FIELD;
		bFade = false;
		g_tField.nFieldNumber --;
		ItemSetting(g_tField.nFieldNumber);
		SetVerTexField();
		SetObjectinField();
		Setting3DObject(g_tField.nFieldNumber);
		StartFadeIn();
		if (g_tField.nFieldNumber <= 11 && g_eMusic == SOUND_LABEL_BGM_WAVE) {
			StopSound();
			g_eMusic = SOUND_LABEL_BGM_BIRD;
			PlaySound(SOUND_LABEL_BGM_BIRD);
		}
		if (g_tField.nFieldNumber > 11 && g_eMusic == SOUND_LABEL_BGM_BIRD) {
			StopSound();
			g_eMusic = SOUND_LABEL_BGM_WAVE;
			PlaySound(SOUND_LABEL_BGM_WAVE);
		}
	}	
	// �k�ֈړ�
	if (PlayerData->posModel.z > LIMIT_FIELD && (g_tField.nFieldNumber >= 4)) {
		PlayerData->posModel.z = LIMIT_FIELD;
		StartFadeOut();
		DeleteObject();
		Delete3DObject();
		DeleteItem();
		bFade = true;
	} else if (PlayerData->posModel.z > LIMIT_FIELD && (g_tField.nFieldNumber < 4)) {
 		PlayerData->posModel.z = LIMIT_FIELD;
	}
	if (bFade && PlayerData->bPlayerMove && PlayerData->posModel.z == LIMIT_FIELD) {
		PlayerData->posModel.z = -LIMIT_FIELD;
		bFade = false;
		g_tField.nFieldNumber -= 4;
		ItemSetting(g_tField.nFieldNumber);
		SetVerTexField();
		SetObjectinField();
		Setting3DObject(g_tField.nFieldNumber);
		StartFadeIn();
		if (g_tField.nFieldNumber <= 11 && g_eMusic == SOUND_LABEL_BGM_WAVE) {
			StopSound();
			g_eMusic = SOUND_LABEL_BGM_BIRD;
			PlaySound(SOUND_LABEL_BGM_BIRD);
		}
		if (g_tField.nFieldNumber > 11 && g_eMusic == SOUND_LABEL_BGM_BIRD) {
			StopSound();
			g_eMusic = SOUND_LABEL_BGM_WAVE;
			PlaySound(SOUND_LABEL_BGM_WAVE);
		}
	}
	// ��ֈړ�
	if (PlayerData->posModel.z < -LIMIT_FIELD && (g_tField.nFieldNumber < 12)) {
		PlayerData->posModel.z = -LIMIT_FIELD;
		SetPlayerCanMove(false);
		StartFadeOut();
		DeleteObject();
		Delete3DObject();
		DeleteItem();
		bFade = true;
	}else if(PlayerData->posModel.z < -LIMIT_FIELD && (g_tField.nFieldNumber >= 12)){
		PlayerData->posModel.z = -LIMIT_FIELD;
	}
	if (bFade && PlayerData->bPlayerMove && PlayerData->posModel.z == -LIMIT_FIELD) {
		PlayerData->posModel.z = LIMIT_FIELD;
		bFade = false;
		g_tField.nFieldNumber += 4;
		ItemSetting(g_tField.nFieldNumber);
		SetVerTexField();
		SetObjectinField();
		Setting3DObject(g_tField.nFieldNumber);
		StartFadeIn();
		if (g_tField.nFieldNumber <= 11 && g_eMusic == SOUND_LABEL_BGM_WAVE) {
			StopSound();
			g_eMusic = SOUND_LABEL_BGM_BIRD;
			PlaySound(SOUND_LABEL_BGM_BIRD);
		}
		if (g_tField.nFieldNumber > 11 && g_eMusic == SOUND_LABEL_BGM_BIRD) {
			StopSound();
			g_eMusic = SOUND_LABEL_BGM_WAVE;
			PlaySound(SOUND_LABEL_BGM_WAVE);
		}
	}

	// �ړ������A�A�C�e���l��
	switch (g_tField.nFieldNumber) {
	case 0:

		break;
	case 1:

		break;
	case 2:
		if (GetKeyboardTrigger(DIK_RETURN) &&
			PlayerData->posModel.x > -190.0 &&
			PlayerData->posModel.x < -100.0 &&
			PlayerData->posModel.z < 140.0 &&
			PlayerData->posModel.z > 70.0 ) {
			StartFadeOut();
			SetMessageData(50, 420, 90, "�ڂ�ڂ�̉Ƃ�����", "�������邩������Ȃ�");
			bFade = true;
		}
		   if (bFade && PlayerData->bPlayerMove) {
			   if (GetItemFlag(ITEM_CLOTH)) {
				   if (GetItemFlag(ITEM_FLIPPERS)) {
				   } else {
					   AcquisitionItem((eItem)ITEM_FLIPPERS);
				   }
			   } else {
				   AcquisitionItem((eItem)ITEM_CLOTH);
			   }
			   bFade = false;
			   StartFadeIn();
		   }

		break;
	case 3:
		if (PlayerData->posModel.z > -85.0f)
			PlayerData->posModel.z = -85.0f;
		break;
	case 4:

		break;
	case 5:

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
		if (PlayerData->posModel.z < -10.0f) {
			PlayerData->posModel.z = -10.0f;
			SetMessageData(50, 420, 150, "���������͍s�������ɂȂ�");

		}

		break;
	case 13:
		if (PlayerData->posModel.x <= 0.0f &&
			PlayerData->posModel.z <= -10.0f) {
			PlayerData->posModel.z = -10.0f;
			SetMessageData(50, 420, 150, "���������͍s�������ɂȂ�");
		}
		else if (PlayerData->posModel.x > 0.0f &&
			PlayerData->posModel.z < 125.0f) {
			PlayerData->posModel.z = 125.0f;
			SetMessageData(50, 420, 150, "���������͍s�������ɂȂ�");
		}

		break;
	case 14:
		if (PlayerData->posModel.z >= -40.0f &&
			PlayerData->posModel.z <= 125.0f) {
			if(PlayerData->posModel.z < 125.0f)
				SetExplosion(exPOS, 10, 10);
			PlayerData->posModel.z = 125.0f;
			if (!GetItemFlag(ITEM_FLIPPERS))
				SetMessageData(50, 420, 150, "���������͍s�������ɂȂ�", "�������ɂ킽���i�����邩������Ȃ�");
			else {
				SetMessageData(50, 420, 150, "���������͍s�������ɂȂ�", "���Ђ��t����Ήj��������");
				if (GetKeyboardTrigger(DIK_RETURN)) {
					PlayerData->posModel.x = 120.0f;
					PlayerData->posModel.z = -70.0f;
					SetMessageData(50, 420, 150, "�������݂֓n����");
				}
			}
		}
		if (PlayerData->posModel.z >= -50.0f &&
			PlayerData->posModel.z <= 115.0f) {
			if(PlayerData->posModel.z > -50.0f)
				SetExplosion(exPOS, 10, 10);
			PlayerData->posModel.z = -50.0f;
			if (!GetItemFlag(ITEM_FLIPPERS))
				SetMessageData(50, 420, 150, "���������͍s�������ɂȂ�", "�������ɂ킽���i�����邩������Ȃ�");
			else{
				SetMessageData(50, 420, 150, "���������͍s�������ɂȂ�", "���Ђ��t����Ήj��������");
				if (GetKeyboardTrigger(DIK_RETURN)) {
					PlayerData->posModel.x = 120.0f;
					PlayerData->posModel.z = 140.0f;
					SetMessageData(50, 420, 150, "�������݂֓n����");
				}
			}
		}
		if (PlayerData->posModel.z <= -50.0f &&
			PlayerData->posModel.x <= -30.0f) {
			if(PlayerData->posModel.x < -30.0f)
				SetExplosion(exPOS, 10, 10);
			PlayerData->posModel.x = -30.0f;
			if (!GetItemFlag(ITEM_FLIPPERS))
				SetMessageData(50, 420, 150, "���������͍s�������ɂȂ�", "�������ɂ킽���i�����邩������Ȃ�");
			else {
				SetMessageData(50, 420, 150, "���������͍s�������ɂȂ�", "���Ђ��t����Ήj��������");
				if (GetKeyboardTrigger(DIK_RETURN)) {
					PlayerData->posModel.x = 120.0f;
					PlayerData->posModel.z = -70.0f;
					SetMessageData(50, 420, 150, "�������݂֓n����");
				}
			}
		}if (PlayerData->posModel.x <= 80.0f &&
			PlayerData->posModel.x >= 50.0f &&
			PlayerData->posModel.y >= 40.0f &&
			PlayerData->posModel.z <= -140.0f &&
			PlayerData->posModel.z >= -180.0f) {
			AcquisitionItem(ITEM_FOOD);
		}
		break;
	case 15:
		if (PlayerData->posModel.z >= -40.0f &&
			PlayerData->posModel.z <= 125.0f) {
			if(PlayerData->posModel.z < 125.0f)
				SetExplosion(exPOS, 10, 10);
			PlayerData->posModel.z = 125.0f;
			if (!GetItemFlag(ITEM_FLIPPERS))
				SetMessageData(50, 420, 150, "���������͍s�������ɂȂ�", "�������ɂ킽���i�����邩������Ȃ�");
			else {
				SetMessageData(50, 420, 150, "���������͍s�������ɂȂ�", "���Ђ��t����Ήj��������");
				if (GetKeyboardTrigger(DIK_RETURN)) {
					PlayerData->posModel.x = -100.0f;
					PlayerData->posModel.z = -70.0f;
					SetMessageData(50, 420, 150, "�������݂֓n����");
				}
			}
		}
		if (PlayerData->posModel.z >= -50.0f &&
			PlayerData->posModel.z <= 115.0f) {
			if(PlayerData->posModel.z > -50.0f)
				SetExplosion(exPOS, 10, 10);
			PlayerData->posModel.z = -50.0f;
			if (!GetItemFlag(ITEM_FLIPPERS))
				SetMessageData(50, 420, 150, "���������͍s�������ɂȂ�", "�������ɂ킽���i�����邩������Ȃ�");
			else {
				SetMessageData(50, 420, 150, "���������͍s�������ɂȂ�", "���Ђ��t����Ήj��������");
				if (GetKeyboardTrigger(DIK_RETURN)) {
					PlayerData->posModel.x = -100.0f;
					PlayerData->posModel.z = 140.0f;
					SetMessageData(50, 420, 150, "�������݂֓n����");
				}
			}
		}
		if (PlayerData->posModel.z <= -50.0f &&
			PlayerData->posModel.x >= 90.0f) {
			if(PlayerData->posModel.x > 90.0f)
				SetExplosion(exPOS, 10, 10);
			PlayerData->posModel.x = 90.0f;
			if (!GetItemFlag(ITEM_FLIPPERS))
				SetMessageData(50, 420, 150, "���������͍s�������ɂȂ�", "�������ɂ킽���i�����邩������Ȃ�");
			else {
				SetMessageData(50, 420, 150, "���������͍s�������ɂȂ�", "���Ђ��t����Ήj��������");
				PlayerData->posModel.x = -100.0f;
				PlayerData->posModel.z = 140.0f;
				SetMessageData(50, 420, 150, "�������݂֓n����");
			}
		}
		break;

	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawField( LPDIRECT3DDEVICE9 pDevice )
{
	D3DXMatrixIdentity(&g_tField.mtxField);	// Identity:�P�ʁ���
		
	//���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD,&g_tField.mtxField);

	//���_�o�b�t�@�f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, 
		g_tField.pD3DVtxBuffField, 
		0, 
		sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetIndices(g_tField.pD3DIdxBuffField);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	
	static bool a;

	if(a/*���l�Ƒ����؂�ւ�*/) 
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_tField.pD3DTextureField[FIELD_BEACH]);
	//�e�N�X�`���̐ݒ�
	else
		pDevice->SetTexture(0, g_tField.pD3DTextureField[FIELD_GRASS]);
	//�e�N�X�`���̍폜(�|���S���̐F���o�������Ƃ��Ȃ�)
	//pDevice->SetTexture(0, NULL);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,	// 
		0,						// ���_�o�b�t�@�̃x�[�X�ʒu
		0,						// ���_�o�b�t�@�̎g�p�J�n�ʒu
		g_tField.nNumVertexField,
		0,						// �C���f�b�N�X�o�b�t�@�̊J�n�ʒu
		g_tField.nNumPolygonField
	);
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ)
{
	// ���_��(�k�ރ|���S���p���l������)
	//g_tField.nNumVertexField = (nNumBlockX + 1) * nNumBlockZ * 2 + (nNumBlockZ - 1) * 2;
	g_tField.nNumVertexField = nNumBlockZ * 2 * ((nNumBlockX + 1) + 1) - 2;
	// �|���S����(�k�ރ|���S���p���l������)
	//g_tField.nNumPolygonField = nNumBlockX * nNumBlockZ * 2 + (nNumBlockZ - 1) * 4;
	g_tField.nNumPolygonField = nNumBlockZ * 2 * (nNumBlockX + 2) - 4;
	
	// ���_���̐ݒ�
	g_tField.nNumVertexField = (nNumBlockX + 1) * (nNumBlockZ + 1);	// �C���f�b�N�X���̐ݒ�(�k�ރ|���S�����l������)
	g_tField.nNumVertexIndex = nNumBlockZ * 2 * ((nNumBlockX + 1) + 1) - 2;

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if( FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * g_tField.nNumVertexField,	//���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,				//���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_3D,					//�g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				//���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_tField.pD3DVtxBuffField,			//���_�o�b�t�@�C���^�t�F�[�X�ւ̃|�C���^
		NULL))){
			return E_FAIL;
	}
	if(FAILED(pDevice->CreateIndexBuffer(
		sizeof(WORD) * g_tField.nNumVertexIndex,	// �C���f�b�N�X�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g)
		D3DUSAGE_WRITEONLY,					// �g�p�@
		D3DFMT_INDEX16,						// �t�H�[�}�b�g
		D3DPOOL_MANAGED,					// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_tField.pD3DIdxBuffField,
		NULL))){
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D * pVtx;

#if FILED_TYPE == 1	//1���̎l�p�`�|���S���ɒ���t����e�N�X�`���̃T�C�Y
		const float fSizeTexX = 1.0f / nNumBlockX;
		const float fSizeTexZ = 1.0f / nNumBlockZ;
#elif FILED_TYPE == 2
		const float fSizeTexX = 1.0f;
		const float fSizeTexZ = 1.0f;
#else
		const float fSizeTexX = ((1.0f / nNumBlockX) / nNumBlockX);
		const float fSizeTexZ = ((1.0f / nNumBlockZ) / nNumBlockZ);
#endif


		//���_�f�[�^�͈̔͂����b�N�����_�o�b�t�@�ւ̃|�C���^���擾
		g_tField.pD3DVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		/*for(int nCntZ = 0; nCntZ < nNumBlockZ; nCntZ ++){
			if(nCntZ > 0){
				// �k�ރ|���S���̂��߂̃_�u���ݒ�
				// ���_���W
				pVtx[0].vtx = D3DXVECTOR3(-(nNumBlockX / 2.0f) * fSizeBlockX, 0.0f, nNumBlockZ / 2.0f * fSizeBlockZ - (nCntZ + 1) * fSizeBlockZ);

				// �@���x�N�g���̐ݒ�
				pVtx[0].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				// ���ˌ��̐ݒ�
				pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				// �e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, fSizeTexZ * (nCntZ + 1));
	
				pVtx ++;	// ����
	
			}
			for(int nCntX = 0; nCntX <= nNumBlockX; nCntX ++, pVtx += 2){
				float posX;
				float posZ;

				posX = (nCntX - nNumBlockX / 2) * fSizeBlockX;
				posZ = (-(nCntZ + 1) + nNumBlockZ / 2) * fSizeBlockZ;
				// ���_���W�̐ݒ�
				pVtx[0].vtx = D3DXVECTOR3(posX, 0.0f, posZ);
				pVtx[1].vtx = D3DXVECTOR3(posX, 0.0f, posZ + fSizeBlockZ);

				// �@���x�N�g���̐ݒ�
				pVtx[0].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				pVtx[1].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				// ���ˌ��̐ݒ�
				pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				// �e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(fSizeTexX * nCntX, fSizeTexZ * (nCntZ + 1));
				pVtx[1].tex = D3DXVECTOR2(fSizeTexX * nCntX, fSizeTexZ * nCntZ);
			}
			if(nCntZ < nNumBlockZ - 1){
				// �k�ރ|���S���̂��߂̃_�u���ݒ�
				// ���_���̃R�s�[
				*pVtx = *(pVtx - 1);
				pVtx ++;	// ����
			}

		}*/
		float posX;
		float posZ;

		for(int nCntZ = 0; nCntZ < nNumBlockZ + 1; nCntZ ++){
			for(int nCntX = 0; nCntX < nNumBlockX + 1; nCntX ++){
			posX = (nCntX - nNumBlockX / 2) * fSizeBlockX;
			posZ = (-(nCntZ + 1) + nNumBlockZ / 2) * fSizeBlockZ + fSizeBlockZ;
			pVtx[nCntZ * (nNumBlockX + 1) + nCntX].vtx = D3DXVECTOR3(posX, 0.0f, posZ);
			// �@��
			pVtx[nCntZ * (nNumBlockX + 1) + nCntX].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			// ���ˌ�
			pVtx[nCntZ * (nNumBlockX + 1) + nCntX].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			// �e�N�X�`�����W
			pVtx[nCntZ * (nNumBlockX + 1) + nCntX].tex = D3DXVECTOR2(fSizeTexX * (nCntX + g_tField.nFieldNumber % FIELD_DIVIDE_X * FIELD_DIVIDE_X),
																	 fSizeTexZ * ((nCntZ) + g_tField.nFieldNumber / FIELD_DIVIDE_Z * FIELD_DIVIDE_Z));
			}
		}

		//���_�f�[�^���A�����b�N����
		g_tField.pD3DVtxBuffField->Unlock();

	}
	// �C���f�b�N�X�o�b�t�@�̒��g�𖄂߂�
	WORD* pIdx;
	
	// �C���f�b�N�X�f�[�^�͈̔͂����b�N�����_�o�b�t�@�ւ̃|�C���^���擾
	g_tField.pD3DIdxBuffField->Lock(0, 0, (void**)&pIdx, 0);
	int nCntIdx = 0;
	for(int nCntZ = 0; nCntZ < nNumBlockZ; nCntZ ++){
		if(nCntZ > 0){
			// �k�ރ|���S���̂��߂̃_�u���ݒ�
			pIdx[nCntIdx] = (nCntZ + 1) * (nNumBlockX + 1);
			nCntIdx ++;
		}
		for(int nCntX = 0; nCntX < nNumBlockX + 1; nCntX ++){
			pIdx[nCntIdx] = (nCntZ + 1) * (nNumBlockX + 1) + nCntX;
			nCntIdx ++;
			pIdx[nCntIdx] = nCntZ * (nNumBlockX + 1) + nCntX;
			nCntIdx ++;
		}
		if(nCntZ < nNumBlockZ - 1){
			// �k�ރ|���S���̂��߂̃_�u���ݒ�
			pIdx[nCntIdx] = nCntZ * (nNumBlockX + 1) + nNumBlockX;
			nCntIdx ++;
		}
	}

	g_tField.pD3DIdxBuffField->Unlock();

	return S_OK;
}

int GetFieldNumber() {
	return g_tField.nFieldNumber;
}

void SetVerTexField() {
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D * pVtx;

#if FILED_TYPE == 1	//1���̎l�p�`�|���S���ɒ���t����e�N�X�`���̃T�C�Y
		const float fSizeTexX = 1.0f / nNumBlockX;
		const float fSizeTexZ = 1.0f / nNumBlockZ;
#elif FILED_TYPE == 2
		const float fSizeTexX = 1.0f;
		const float fSizeTexZ = 1.0f;
#else
		const float fSizeTexX = ((1.0f / FLOAT_FIELD_DIVIDE_X) / FLOAT_FIELD_DIVIDE_X);
		const float fSizeTexZ = ((1.0f / FLOAT_FIELD_DIVIDE_Z) / FLOAT_FIELD_DIVIDE_Z);
#endif


		//���_�f�[�^�͈̔͂����b�N�����_�o�b�t�@�ւ̃|�C���^���擾
		g_tField.pD3DVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntZ = 0; nCntZ < FIELD_DIVIDE_Z + 1; nCntZ ++) {
			for (int nCntX = 0; nCntX < FIELD_DIVIDE_X + 1; nCntX ++) {
				pVtx[nCntZ * (FIELD_DIVIDE_X + 1) + nCntX].tex = D3DXVECTOR2(fSizeTexX * (nCntX + g_tField.nFieldNumber % FIELD_DIVIDE_X * FIELD_DIVIDE_X),
																		fSizeTexZ * ((nCntZ)+ g_tField.nFieldNumber / FIELD_DIVIDE_Z * FIELD_DIVIDE_Z));
			}
		}
		g_tField.pD3DVtxBuffField->Unlock();
	}
}

// �r���{�[�h�I�u�W�F�N�g�ݒu(���݂͖؂̂�)
void SetObjectinField() {
	// �}�b�v�ԍ����Ƃ�
	switch (g_tField.nFieldNumber) {
	case 0:

		break;
	case 1:

		break;
	case 2:

		break;
	case 3:

		break;
	case 4:
		SetInfoObject(OBJECT_TREE, 80.0f, 45.0f, 30.0f);
		SetInfoObject(OBJECT_TREE, 160.0f, 45.0f, 30.0f);
		SetInfoObject(OBJECT_TREE, 240.0f, 45.0f, 30.0f);
		SetInfoObject(OBJECT_TREE, 0.0f, 45.0f, 30.0f);
		SetInfoObject(OBJECT_TREE, 0.0f, 45.0f, -50.0f);
		SetInfoObject(OBJECT_TREE, 0.0f, 45.0f, -130.0f);
		SetInfoObject(OBJECT_TREE, 0.0f, 45.0f, -210.0f);

		break;
	case 5:
		SetInfoObject(OBJECT_TREE, 0.0f, 45.0f, -210.0f);
		SetInfoObject(OBJECT_TREE, 0.0f, 45.0f, -130.0f);
		SetInfoObject(OBJECT_TREE, 0.0f, 45.0f, -50.0f);

		break;
	case 6:

		break;
	case 7:

		break;
	case 8:
		SetInfoObject(OBJECT_TREE, 0.0f, 45.0f, 210.0f);
		SetInfoObject(OBJECT_TREE, 0.0f, 45.0f, 130.0f);

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
		SetInfoObject(OBJECT_TREE, 250.0f, 45.0f, 100.0f);
		SetInfoObject(OBJECT_TREE, 250.0f, 45.0f, 200.0f);

		break;

	}
}