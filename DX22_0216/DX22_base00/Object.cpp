#include "Object.h"
#include "Model.h"
#include "shadow.h"
#include "camera.h"

//----- �}�N����` -----
#define OBJECT_TREE_NAME				"data/TEXTURE/tree.png"
#define OBJECT_TREE_SIZE_X				(90)
#define OBJECT_TREE_SIZE_Y				(100)

#define OBJECT_TREE_PATTAERN_DIVIDE_X	(1)
#define OBJECT_TREE_PATTAERN_DIVIDE_Y	(1)
#define OBJECT_NUM_TREE_ANIME_PATTERN	(OBJECT_TREE_PATTAERN_DIVIDE_X * OBJECT_TREE_PATTAERN_DIVIDE_Y)
#define OBJECT_TREE_PATTERN_SIZE_X		(1.0f / OBJECT_TREE_PATTAERN_DIVIDE_X)
#define OBJECT_TREE_PATTERN_SIZE_Y		(1.0f / OBJECT_TREE_PATTAERN_DIVIDE_Y)


#define MAX_OBJECT_NUM					(40)

//----- �\���̐錾 -----
LPDIRECT3DTEXTURE9		g_pTextureObject[OBJECT_NUM_MAX] ={ NULL };	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffObject = NULL;					// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

//----- �O���[�o���錾 -----
//LPDIRECT3DTEXTURE9	g_pTextureObject[OBJECT_NUM_MAX] = {NULL};	//�e�N�X�`���ւ̃|�C���^
object g_tObject[MAX_OBJECT_NUM];
D3DXMATRIX				g_mtxWorldObject;			// ���[���h�}�g���b�N�X

//----- �v���g�^�C�v�錾 -----
HRESULT MakeVertexObject(LPDIRECT3DDEVICE9 pDevice);

//===============================================================
//	����������
//===============================================================
void InitObject(void) {
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, OBJECT_TREE_NAME, &g_pTextureObject[OBJECT_TREE]);


	for (int nCnt = 0; nCnt < MAX_OBJECT_NUM; nCnt ++) {
		g_tObject[nCnt].posBillboard				= D3DXVECTOR3( 0,0,0 );
		g_tObject[nCnt].sclBillboard				= D3DXVECTOR3( 1.0,1.0,1.0 );
		g_tObject[nCnt].vecBillboard				= D3DXVECTOR3( 0,0,0 );
		g_tObject[nCnt].nIdxShadowBillboard			= 0;
		g_tObject[nCnt].bEnableGravity				= false;
		g_tObject[nCnt].bLive						= false;
	}
	//���_���̍쐬
	MakeVertexObject(pDevice);

}

//===============================================================
//	�I������
//===============================================================
void UninitObject() {
	for (int nCnt = 0; nCnt < OBJECT_NUM_MAX; nCnt ++) {
		if(g_pTextureObject[nCnt] != NULL){
			//�e�N�X�`���̊J��
			g_pTextureObject[nCnt]->Release();
			g_pTextureObject[nCnt] = NULL;
		}
	}
}

//===============================================================
//	�X�V����
//===============================================================
void UpdateObject() {

	for (int nCnt = 0; nCnt < MAX_OBJECT_NUM; nCnt ++) {
		if (!g_tObject[nCnt].bLive)
			continue;

		//g_tObject[nCnt].nCounterAnime ++;

		/*if (g_tObject[nCnt].fPosXTex - tPlayerData->nTexSizeX - tPlayerData->fMoveXTex < tPlayerData->fPosXTex &&
			g_tObject[nCnt].fPosXTex + g_tObject[nCnt].nTexSizeX - tPlayerData->fMoveXTex > tPlayerData->fPosXTex &&
			g_tObject[nCnt].fPosYTex - tPlayerData->nTexSizeY - tPlayerData->fMoveYTex < tPlayerData->fPosYTex &&
			g_tObject[nCnt].fPosYTex + g_tObject[nCnt].nTexSizeY - tPlayerData->fMoveYTex > tPlayerData->fPosYTex) {
			//���E�Ɉړ������Ƃ�
			if (tPlayerData->fMoveXTex) {
				tPlayerData->fMoveXTex = 0;
			}
			////���Ɉړ������Ƃ�
			//else if(tPlayerData->fPosXTex < tPlayerData->fOldPosXTex){
			//	tPlayerData->fMoveXTex = 0;
			//}
			//�㉺�Ɉړ������Ƃ�
			if (tPlayerData->fMoveYTex) {
				tPlayerData->fMoveYTex = 0;
			}
			////��Ɉړ������Ƃ�
			//else if(tPlayerData->fPosYTex < tPlayerData->fOldPosYTex){
			//	tPlayerData->fMoveYTex = 0;
			//}
		}*/

	}

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	MakeVertexObject(pDevice);
}

// �I�u�W�F�N�g�ƃv���C���[�̓����蔻��
void HitChecktoObject() {
	static tPlayerData tPlayerDataBefore;
	tPlayerData * tPlayerData = GetPlayerData();

	for (int nCnt = 0; nCnt < MAX_OBJECT_NUM; nCnt ++) {
		if (!g_tObject[nCnt].bLive)
			continue;

		// �v���C���[�Ƃ̂����蔻��(������)
		if (tPlayerData->posModel.x < g_tObject[nCnt].posBillboard.x + (g_tObject[nCnt].sizeBillboard.x / 2.0f) &&
			tPlayerData->posModel.x > g_tObject[nCnt].posBillboard.x - (g_tObject[nCnt].sizeBillboard.x / 2.0f) &&
			tPlayerData->posModel.z < g_tObject[nCnt].posBillboard.z + (g_tObject[nCnt].sizeBillboard.x / 2.0f) &&
			tPlayerData->posModel.z > g_tObject[nCnt].posBillboard.z - (g_tObject[nCnt].sizeBillboard.x / 2.0f)) {
			if (tPlayerData->posModel.x < g_tObject[nCnt].posBillboard.x + (g_tObject[nCnt].sizeBillboard.x / 2.0f) &&
				tPlayerData->posModel.x > g_tObject[nCnt].posBillboard.x - (g_tObject[nCnt].sizeBillboard.x / 2.0f) &&
				(tPlayerDataBefore.posModel.x > g_tObject[nCnt].posBillboard.x + (g_tObject[nCnt].sizeBillboard.x / 2.0f) ||
					tPlayerDataBefore.posModel.x < g_tObject[nCnt].posBillboard.x - (g_tObject[nCnt].sizeBillboard.x / 2.0f)) && 
				tPlayerDataBefore.posModel.z < g_tObject[nCnt].posBillboard.z + (g_tObject[nCnt].sizeBillboard.x / 2.0f) &&
				tPlayerDataBefore.posModel.z > g_tObject[nCnt].posBillboard.z - (g_tObject[nCnt].sizeBillboard.x / 2.0f)) {
				tPlayerData->moveModel.x = 0;
				if (tPlayerData->posModel.x > g_tObject[nCnt].posBillboard.x)
					tPlayerData->posModel.x = g_tObject[nCnt].posBillboard.x + g_tObject[nCnt].sizeBillboard.x / 2.0f;
				if (tPlayerData->posModel.x < g_tObject[nCnt].posBillboard.x)
					tPlayerData->posModel.x = g_tObject[nCnt].posBillboard.x - g_tObject[nCnt].sizeBillboard.x / 2.0f;
			}
			if (tPlayerData->posModel.z < g_tObject[nCnt].posBillboard.z + (g_tObject[nCnt].sizeBillboard.x / 2.0f) &&
				tPlayerData->posModel.z > g_tObject[nCnt].posBillboard.z - (g_tObject[nCnt].sizeBillboard.x / 2.0f) &&
				(tPlayerDataBefore.posModel.z > g_tObject[nCnt].posBillboard.x + (g_tObject[nCnt].sizeBillboard.x / 2.0f) ||
				tPlayerDataBefore.posModel.z < g_tObject[nCnt].posBillboard.x - (g_tObject[nCnt].sizeBillboard.x / 2.0f)) &&
				tPlayerDataBefore.posModel.x < g_tObject[nCnt].posBillboard.z + (g_tObject[nCnt].sizeBillboard.x / 2.0f) &&
				tPlayerDataBefore.posModel.x > g_tObject[nCnt].posBillboard.z - (g_tObject[nCnt].sizeBillboard.x / 2.0f)) {
				tPlayerData->moveModel.z = 0;
				if (tPlayerData->posModel.z > g_tObject[nCnt].posBillboard.z)
					tPlayerData->posModel.z = g_tObject[nCnt].posBillboard.z + g_tObject[nCnt].sizeBillboard.x / 2.0f;
				if (tPlayerData->posModel.z < g_tObject[nCnt].posBillboard.z)
					tPlayerData->posModel.z = g_tObject[nCnt].posBillboard.z - g_tObject[nCnt].sizeBillboard.x / 2.0f;
			}
		}
		//g_tObject[nCnt].nCounterAnime ++;

		/*if (g_tObject[nCnt].fPosXTex - tPlayerData->nTexSizeX - tPlayerData->fMoveXTex < tPlayerData->fPosXTex &&
		g_tObject[nCnt].fPosXTex + g_tObject[nCnt].nTexSizeX - tPlayerData->fMoveXTex > tPlayerData->fPosXTex &&
		g_tObject[nCnt].fPosYTex - tPlayerData->nTexSizeY - tPlayerData->fMoveYTex < tPlayerData->fPosYTex &&
		g_tObject[nCnt].fPosYTex + g_tObject[nCnt].nTexSizeY - tPlayerData->fMoveYTex > tPlayerData->fPosYTex) {
		//���E�Ɉړ������Ƃ�
		if (tPlayerData->fMoveXTex) {
		tPlayerData->fMoveXTex = 0;
		}
		////���Ɉړ������Ƃ�
		//else if(tPlayerData->fPosXTex < tPlayerData->fOldPosXTex){
		//	tPlayerData->fMoveXTex = 0;
		//}
		//�㉺�Ɉړ������Ƃ�
		if (tPlayerData->fMoveYTex) {
		tPlayerData->fMoveYTex = 0;
		}
		////��Ɉړ������Ƃ�
		//else if(tPlayerData->fPosYTex < tPlayerData->fOldPosYTex){
		//	tPlayerData->fMoveYTex = 0;
		//}
		}*/

	}
	tPlayerDataBefore = *tPlayerData;
}
//===============================================================
//	�`�揈��
//===============================================================
void DrawObject() {
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;
	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	
	/*pDevice->SetRenderState(
		D3DRS_BLENDOP,
		D3DBLENDOP_REVSUBTRACT
	);*/
	pDevice->SetRenderState(
		D3DRS_SRCBLEND,
		D3DBLEND_SRCALPHA
	);
	/*pDevice->SetRenderState(
		D3DRS_DESTBLEND,
		D3DBLEND_ONE
	);*/

	// Z��r�Ȃ�
	/*pDevice->SetRenderState(
		D3DRS_ZFUNC,
		D3DCMP_ALWAYS
	);*/
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	//pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);			// ���f�X�e�B�l�[�V�����J���[�̎w��
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);			// Z��r�Ȃ�

	for (int nCnt = 0; nCnt < MAX_OBJECT_NUM; nCnt ++) {
		if (!g_tObject[nCnt].bLive)
			continue;

		D3DXMatrixIdentity(&g_mtxWorldObject);
		mtxView = GetMtxView();
#if 0
		// �t�s������߂�
		D3DXMatrixInverse(
			&g_mtxWorldBillboard,
			NULL,
			&mtxView
		);
		g_mtxWorldBillboard._41 = 0.0f;
		g_mtxWorldBillboard._42 = 0.0f;
		g_mtxWorldBillboard._43 = 0.0f;	// ���s�ړ��������Ȃ���
#else
		// �]�u�s������߂�
		g_mtxWorldObject._11 = mtxView._11;
		g_mtxWorldObject._12 = mtxView._21;
		g_mtxWorldObject._13 = mtxView._31;
		g_mtxWorldObject._21 = mtxView._12;
		g_mtxWorldObject._22 = mtxView._22;
		g_mtxWorldObject._23 = mtxView._32;
		g_mtxWorldObject._31 = mtxView._13;
		g_mtxWorldObject._32 = mtxView._23;
		g_mtxWorldObject._33 = mtxView._33;	
		
#endif
		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScale, g_tObject[nCnt].sclBillboard.x,
										g_tObject[nCnt].sclBillboard.y,
										g_tObject[nCnt].sclBillboard.z);
		D3DXMatrixMultiply(&g_mtxWorldObject,
										&g_mtxWorldObject, &mtxScale);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, g_tObject[nCnt].posBillboard.x,
												g_tObject[nCnt].posBillboard.y,
												g_tObject[nCnt].posBillboard.z);
		D3DXMatrixMultiply(&g_mtxWorldObject,
										&g_mtxWorldObject, &mtxTranslate);

	

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldObject);

		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffObject, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_tObject[nCnt].pTextureObject);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCnt * 4), NUM_POLYGON);


		/*
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, *g_tObject[nCnt].pTextureObject);
		//�|���S���`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,
			NUM_POLYGON,
			&pVtx[0],
			sizeof(VERTEX_2D));
		*/
	}
	// ���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(
		D3DRS_SRCBLEND,
		D3DBLEND_SRCALPHA
	);
	pDevice->SetRenderState(
		D3DRS_DESTBLEND,
		D3DBLEND_INVSRCALPHA
	);	

	// Z��r����
	pDevice->SetRenderState(
		D3DRS_ZFUNC,
		D3DCMP_LESSEQUAL
	);

}

//===============================================================
//	�I�u�W�F�g����
//===============================================================
void SetInfoObject(enum_object eObject, float fPosTexX, float fPosTexY, float fPosTexZ) {
	for (int nCnt = 0; nCnt < MAX_OBJECT_NUM; nCnt ++) {
		if (g_tObject[nCnt].bLive)
			continue;

		g_tObject[nCnt].pTextureObject = g_pTextureObject[eObject];

		// �I�u�W�F�N�g�؂�ւ�(�Ƃƃt�F���X�̓��f�����g�p���邩��)
		switch (eObject) {
		case OBJECT_TREE:
			g_tObject[nCnt].sizeBillboard		= D3DXVECTOR2(OBJECT_TREE_SIZE_X, OBJECT_TREE_SIZE_Y);

			break;
		/*case OBJECT_FENCE:
			g_tObject[nCnt].nTexSizeX			= OBJECT_FENCE_SIZE_X;
			g_tObject[nCnt].nTexSizeY			= OBJECT_FENCE_SIZE_Y;
			g_tObject[nCnt].nPatternDivideX	= OBJECT_FENCE_PATTAERN_DIVIDE_X;
			g_tObject[nCnt].nPatternDivideY	= OBJECT_FENCE_PATTAERN_DIVIDE_Y;

			break;
		case OBJECT_HOUSE:
			g_tObject[nCnt].nTexSizeX			= OBJECT_HOUSE_SIZE_X;
			g_tObject[nCnt].nTexSizeY			= OBJECT_HOUSE_SIZE_Y;
			g_tObject[nCnt].nPatternDivideX	= OBJECT_HOUSE_PATTAERN_DIVIDE_X;
			g_tObject[nCnt].nPatternDivideY	= OBJECT_HOUSE_PATTAERN_DIVIDE_Y;

			break;*/
		default:
			break;

		}
		g_tObject[nCnt].posBillboard		= D3DXVECTOR3(fPosTexX, fPosTexY, fPosTexZ);
		//g_tObject[nCnt].nIdxShadowBillboard = CreateShadow(g_tObject[nCnt].posBillboard, g_tObject[nCnt].sizeBillboard.x, g_tObject[nCnt].sizeBillboard.y);
		//SetColorShadow(g_tObject[nCnt].nIdxShadowBillboard, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		g_tObject[nCnt].bLive = true;

		break;
	}
}

//===========================================================
//	���_�̐ݒ�
//===========================================================
HRESULT MakeVertexObject(LPDIRECT3DDEVICE9 pDevice) {


	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_OBJECT_NUM,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pD3DVtxBuffObject,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))						// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{
		VERTEX_3D * pVtx;
		g_pD3DVtxBuffObject->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCnt = 0; nCnt < MAX_OBJECT_NUM; nCnt ++, pVtx += 4) {
			if (!g_tObject[nCnt].bLive)
				continue;


			pVtx[0].vtx = D3DXVECTOR3(-g_tObject[nCnt].sizeBillboard.x / 2, - g_tObject[nCnt].sizeBillboard.y / 2, 0.0f);	//(X, Y, Z)
			pVtx[1].vtx = D3DXVECTOR3(-g_tObject[nCnt].sizeBillboard.x / 2, g_tObject[nCnt].sizeBillboard.y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(g_tObject[nCnt].sizeBillboard.x / 2, -g_tObject[nCnt].sizeBillboard.y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(g_tObject[nCnt].sizeBillboard.x / 2, g_tObject[nCnt].sizeBillboard.y / 2, 0.0f);

			pVtx[0].normal =
				pVtx[1].normal =
				pVtx[2].normal =
				pVtx[3].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);	//

			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx[0].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);

		}

		g_pD3DVtxBuffObject->Unlock();
	}
	return S_OK;
}

//�I�u�W�F�N�g�폜
void DeleteObject() {
	for (int nCnt = 0; nCnt < MAX_OBJECT_NUM; nCnt ++) {
		if (!g_tObject[nCnt].bLive)
			continue;

		g_tObject[nCnt].pTextureObject	= NULL;
		g_tObject[nCnt].posBillboard	= D3DXVECTOR3(0,0,0);
		g_tObject[nCnt].sizeBillboard	= D3DXVECTOR2(0,0);
		g_tObject[nCnt].bLive			= false;
	}
}

void DeleteObject(int nDeleteNum) {
	g_tObject[nDeleteNum].pTextureObject	= NULL;
	g_tObject[nDeleteNum].posBillboard		= D3DXVECTOR3(0,0,0);
	g_tObject[nDeleteNum].sizeBillboard		= D3DXVECTOR2(0,0);
	g_tObject[nDeleteNum].bLive				= false;
}