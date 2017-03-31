#include "3DObject.h"
#include "model.h"
#include "shadow.h"
#include "Message.h"
#include "Item.h"
#include<string>

#include <math.h>

using namespace std;
//*****************************************************************************
// マクロ定義
//*****************************************************************************
const string		HOUSE_MODEL_FILE_NAME("data/XFILE/house.x");
const D3DXVECTOR3	HOUSE_MODEL_POS(20, 0, 20);
const D3DXVECTOR3	HOUSE_MODEL_ROT(10, 10, 10);
const D3DXVECTOR3	HOUSE_MODEL_SCALE(10, 10, 10);
const string		PALM_MODEL_FILE_NAME("data/XFILE/yasi.x");
const D3DXVECTOR3	PALM_MODEL_POS(60, 0, 60);
const D3DXVECTOR3	PALM_MODEL_ROT(10, 10, 10);
const D3DXVECTOR3	PALM_MODEL_SCALE(10, 10, 10);
const string		FENCE_MODEL_FILE_NAME("data/XFILE/fence.x");
const D3DXVECTOR3	FENCE_MODEL_POS(50, 0, 50);
const D3DXVECTOR3	FENCE_MODEL_ROT(10, 10, 10);
const D3DXVECTOR3	FENCE_MODEL_SCALE(10, 10, 10);
const string		RAFT_MODEL_FILE_NAME("data/XFILE/raft.x");
const D3DXVECTOR3	RAFT_MODEL_POS(50, 0, 50);
const D3DXVECTOR3	RAFT_MODEL_ROT(0, 90, 0);
const D3DXVECTOR3	RAFT_MODEL_SCALE(40, 40, 40);
const string		TREASURE_MODEL_FILE_NAME("data/XFILE/treasure.x");
const D3DXVECTOR3	TREASURE_MODEL_POS(50, 0, 50);
const D3DXVECTOR3	TREASURE_MODEL_ROT(10, 10, 10);
const D3DXVECTOR3	TREASURE_MODEL_SCALE(10, 10, 10);

const int MAX_NUM_3DOBJECT(20);

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
tObjectModelData g_ObjectModel[MAX_NUM_3DOBJECT];
tObjectModelData g_ObjectModelInfo[OBJECT_MODEL_NUM_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init3DObject(LPDIRECT3DDEVICE9 pDevice)
{
	string FileName;
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nCnt = 0; nCnt < OBJECT_MODEL_NUM_MAX; nCnt++) {
		g_ObjectModelInfo[nCnt].pD3DXMeshModel = NULL;
		//g_ObjectModel[nCnt].pD3DXBuffMatModel = NULL;
		g_ObjectModelInfo[nCnt].nNumMatModel  = 0;

		//位置、回転、スケールの初期設定
		g_ObjectModelInfo[nCnt].posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ObjectModelInfo[nCnt].rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ObjectModelInfo[nCnt].scaleModel = D3DXVECTOR3(10.0f, 10.0f, 10.0f);

		LPD3DXBUFFER	pMatBuf	= NULL;

		switch (nCnt) {
		case OBJECT_MODEL_HOUSE:
			FileName = HOUSE_MODEL_FILE_NAME;
			break;
		case OBJECT_MODEL_PALM:
			FileName = PALM_MODEL_FILE_NAME;
			break;
		case OBJECT_MODEL_FENCE:
			FileName = FENCE_MODEL_FILE_NAME;
			break;
		case OBJECT_MODEL_RAFT:
			FileName = RAFT_MODEL_FILE_NAME;
			break;
		case OBJECT_MODEL_TREASURE:
			//FileName = TREASURE_MODEL_FILE_NAME;
			break;

		default:
			break;
		}
		//Xファイル読み込み
		if (FAILED(D3DXLoadMeshFromX(
			FileName.c_str(),				//Xファイル名
			D3DXMESH_SYSTEMMEM,		//メッシュ作成のオプション
			pDevice,				//デバイスへのポインタ
			NULL,					//隣接性データを含むバッファへのポインタ
			&g_ObjectModelInfo[nCnt].pD3DXBuffMatModel,	//マテリアルデータを含むバッファ
			NULL,					//エフェクトインスタンスへの配列を含むポインタ
			&g_ObjectModelInfo[nCnt].nNumMatModel,		//D3DXMATERIAL構造体の数
			&g_ObjectModelInfo[nCnt].pD3DXMeshModel		//メッシュのポインタ
			))) {
			//return E_FAIL;
		}

		if (!(g_ObjectModelInfo[nCnt].pD3DXMeshModel->GetFVF() & D3DFVF_NORMAL)) {
			ID3DXMesh * pTempMesh = NULL;
			g_ObjectModelInfo[nCnt].pD3DXMeshModel->CloneMeshFVF(g_ObjectModelInfo[nCnt].pD3DXMeshModel->GetOptions(),
				g_ObjectModelInfo[nCnt].pD3DXMeshModel->GetFVF() | D3DFVF_NORMAL,
				pDevice,
				&pTempMesh);
			D3DXComputeNormals(pTempMesh, NULL);
			g_ObjectModelInfo[nCnt].pD3DXMeshModel->Release();
			g_ObjectModelInfo[nCnt].pD3DXMeshModel = pTempMesh;
		}
		g_ObjectModelInfo[nCnt].pMeshMat = new D3DMATERIAL9[g_ObjectModelInfo[nCnt].nNumMatModel];
		g_ObjectModelInfo[nCnt].pMeshTex = new LPDIRECT3DTEXTURE9[g_ObjectModelInfo[nCnt].nNumMatModel];
		D3DXMATERIAL * d3Mat = (D3DXMATERIAL *)g_ObjectModelInfo[nCnt].pD3DXBuffMatModel->GetBufferPointer();
		for (unsigned int i = 0; i < g_ObjectModelInfo[nCnt].nNumMatModel; i++) {
			g_ObjectModelInfo[nCnt].pMeshMat[i] = d3Mat[i].MatD3D;
			g_ObjectModelInfo[nCnt].pMeshMat[i].Ambient = g_ObjectModelInfo[nCnt].pMeshMat[i].Diffuse;
			g_ObjectModelInfo[nCnt].pMeshTex[i] = NULL;

			//使用しているテクスチャがあれば読み込む
			if (d3Mat[i].pTextureFilename != NULL &&
				lstrlen(d3Mat[i].pTextureFilename) > 0)
			{
				if (FAILED(D3DXCreateTextureFromFile(
					pDevice,
					d3Mat[i].pTextureFilename,
					&g_ObjectModelInfo[nCnt].pMeshTex[i])))
				{
					//return E_FAIL;
				}
			}
		}

		// 影の成分
		//g_ObjectModel[nCnt].nIdxShadow = CreateShadow(g_ObjectModel[nCnt].posModel, 25.0f, 25.0f);

		//pMatBuf->Release();
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit3DObject(void)
{
	for (int nCnt = 0; nCnt < OBJECT_MODEL_NUM_MAX; nCnt++) {
		if (g_ObjectModelInfo[nCnt].pD3DXBuffMatModel != NULL) {
			//バッファ解放
			g_ObjectModelInfo[nCnt].pD3DXBuffMatModel->Release();
			g_ObjectModelInfo[nCnt].pD3DXBuffMatModel = NULL;
		}
		if (g_ObjectModelInfo[nCnt].pD3DXMeshModel != NULL) {
			//メッシュ解放
			g_ObjectModelInfo[nCnt].pD3DXMeshModel->Release();
			g_ObjectModelInfo[nCnt].pD3DXMeshModel = NULL;
		}

		DWORD	i;
		// テクスチャ開放
		for (i = 0; i < g_ObjectModelInfo[nCnt].nNumMatModel; i++)
		{
			if (g_ObjectModelInfo[nCnt].pMeshTex[i] != NULL) {
				g_ObjectModelInfo[nCnt].pMeshTex[i]->Release();
				g_ObjectModelInfo[nCnt].pMeshTex[i]	= NULL;
			}
		}
		delete[] g_ObjectModelInfo[nCnt].pMeshTex;
		g_ObjectModelInfo[nCnt].pMeshTex	= NULL;
		delete[] g_ObjectModelInfo[nCnt].pMeshMat;
		g_ObjectModelInfo[nCnt].pMeshMat	= NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void Update3DObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	/////////////////////////////////////
	if (GetKeyboardTrigger(DIK_3))
		SetGameState(STATE_ENDING);
	/////////////////////////////////////

	for (int nCnt = 0; nCnt < OBJECT_MODEL_NUM_MAX; nCnt++) {
		// 影の位置を設定
		//SetPositionShadow(g_ObjectModel[nCnt].nIdxShadow, g_ObjectModel[nCnt].posModel);
	}

	
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw3DObject(LPDIRECT3DDEVICE9 pDevice)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATERIAL * 	pD3DXMat;
	D3DMATERIAL9	matDef;

	D3DXMATRIX mtxScale, mtxRot, mtxTrans;

	
	for (int nCnt = 0; nCnt < MAX_NUM_3DOBJECT; nCnt++) {
		if (!g_ObjectModel[nCnt].bLive)
			continue;

		pDevice->SetFVF(g_ObjectModel[nCnt].pD3DXMeshModel->GetFVF());

		//ワールドマトリクスの初期化
		D3DXMatrixIdentity(&g_ObjectModel[nCnt].mtxWorld);	// Identity:単位○○

															//現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// スケールを反映
		D3DXMatrixScaling(
			&mtxScale,		//格納先
			g_ObjectModel[nCnt].scaleModel.x,
			g_ObjectModel[nCnt].scaleModel.y,
			g_ObjectModel[nCnt].scaleModel.z
			);
		D3DXMatrixMultiply(
			&g_ObjectModel[nCnt].mtxWorld,	//格納先(A*B)
			&g_ObjectModel[nCnt].mtxWorld,	//A
			&mtxScale		//B
			);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(
			&mtxRot,		//格納先
			g_ObjectModel[nCnt].rotModel.y,	//ヨー(左右)
			g_ObjectModel[nCnt].rotModel.x,	//ピッチ(前後)
			g_ObjectModel[nCnt].rotModel.z	//ロール(回転)
			);
		D3DXMatrixMultiply(
			&g_ObjectModel[nCnt].mtxWorld,	//格納先(A*B)
			&g_ObjectModel[nCnt].mtxWorld,	//A
			&mtxRot			//B
			);

		// 移動を反映
		D3DXMatrixTranslation(
			&mtxTrans,		//格納先
			g_ObjectModel[nCnt].posModel.x,	//
			g_ObjectModel[nCnt].posModel.y,	//
			g_ObjectModel[nCnt].posModel.z	//
			);
		D3DXMatrixMultiply(
			&g_ObjectModel[nCnt].mtxWorld,	//格納先(A*B)
			&g_ObjectModel[nCnt].mtxWorld,	//A
			&mtxTrans		//B
			);

		//ワールドマトリクスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_ObjectModel[nCnt].mtxWorld);

		//マテリアル情報に対するポインタを取得
		pD3DXMat = (D3DXMATERIAL*)g_ObjectModel[nCnt].pD3DXBuffMatModel->GetBufferPointer();


		for (int nCntMat = 0; nCntMat < (int)g_ObjectModel[nCnt].nNumMatModel; nCntMat ++) {
			//マテリアルの設定
			pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
			//テクスチャの設定
			pDevice->SetTexture(0, g_ObjectModel[nCnt].pMeshTex[nCntMat]);
			//描画
			g_ObjectModel[nCnt].pD3DXMeshModel->DrawSubset(nCntMat);
		}

		//マテリアルを元に戻す
		pDevice->SetMaterial(&matDef);
	}

	
}

void SetInfo3DObject(eObjectModel object, D3DXVECTOR3 posModel, D3DXVECTOR3 rotModel, D3DXVECTOR3 sclModel) {
	for (int nCnt = 0; nCnt < MAX_NUM_3DOBJECT;nCnt++) {
		if (g_ObjectModel[nCnt].bLive)
			continue;
		switch (object) {
		case OBJECT_MODEL_HOUSE:
			g_ObjectModel[nCnt].pD3DTextureModel	= g_ObjectModelInfo[OBJECT_MODEL_HOUSE].pD3DTextureModel;
			g_ObjectModel[nCnt].pD3DXBuffMatModel	= g_ObjectModelInfo[OBJECT_MODEL_HOUSE].pD3DXBuffMatModel;
			g_ObjectModel[nCnt].pD3DXMeshModel		= g_ObjectModelInfo[OBJECT_MODEL_HOUSE].pD3DXMeshModel;
			g_ObjectModel[nCnt].pMeshMat			= g_ObjectModelInfo[OBJECT_MODEL_HOUSE].pMeshMat;
			g_ObjectModel[nCnt].pMeshTex			= g_ObjectModelInfo[OBJECT_MODEL_HOUSE].pMeshTex;
			g_ObjectModel[nCnt].nNumMatModel		= g_ObjectModelInfo[OBJECT_MODEL_HOUSE].nNumMatModel;
			break;
		case OBJECT_MODEL_PALM:
			g_ObjectModel[nCnt].pD3DTextureModel	= g_ObjectModelInfo[OBJECT_MODEL_PALM].pD3DTextureModel;
			g_ObjectModel[nCnt].pD3DXBuffMatModel	= g_ObjectModelInfo[OBJECT_MODEL_PALM].pD3DXBuffMatModel;
			g_ObjectModel[nCnt].pD3DXMeshModel		= g_ObjectModelInfo[OBJECT_MODEL_PALM].pD3DXMeshModel;
			g_ObjectModel[nCnt].pMeshMat			= g_ObjectModelInfo[OBJECT_MODEL_PALM].pMeshMat;
			g_ObjectModel[nCnt].pMeshTex			= g_ObjectModelInfo[OBJECT_MODEL_PALM].pMeshTex;
			g_ObjectModel[nCnt].nNumMatModel		= g_ObjectModelInfo[OBJECT_MODEL_PALM].nNumMatModel;
			break;
		case OBJECT_MODEL_FENCE:
			g_ObjectModel[nCnt].pD3DTextureModel	= g_ObjectModelInfo[OBJECT_MODEL_FENCE].pD3DTextureModel;
			g_ObjectModel[nCnt].pD3DXBuffMatModel	= g_ObjectModelInfo[OBJECT_MODEL_FENCE].pD3DXBuffMatModel;
			g_ObjectModel[nCnt].pD3DXMeshModel		= g_ObjectModelInfo[OBJECT_MODEL_FENCE].pD3DXMeshModel;
			g_ObjectModel[nCnt].pMeshMat			= g_ObjectModelInfo[OBJECT_MODEL_FENCE].pMeshMat;
			g_ObjectModel[nCnt].pMeshTex			= g_ObjectModelInfo[OBJECT_MODEL_FENCE].pMeshTex;
			g_ObjectModel[nCnt].nNumMatModel		= g_ObjectModelInfo[OBJECT_MODEL_FENCE].nNumMatModel;
			break;
		case OBJECT_MODEL_RAFT:
			g_ObjectModel[nCnt].pD3DTextureModel	= g_ObjectModelInfo[OBJECT_MODEL_RAFT].pD3DTextureModel;
			g_ObjectModel[nCnt].pD3DXBuffMatModel	= g_ObjectModelInfo[OBJECT_MODEL_RAFT].pD3DXBuffMatModel;
			g_ObjectModel[nCnt].pD3DXMeshModel		= g_ObjectModelInfo[OBJECT_MODEL_RAFT].pD3DXMeshModel;
			g_ObjectModel[nCnt].pMeshMat			= g_ObjectModelInfo[OBJECT_MODEL_RAFT].pMeshMat;
			g_ObjectModel[nCnt].pMeshTex			= g_ObjectModelInfo[OBJECT_MODEL_RAFT].pMeshTex;
			g_ObjectModel[nCnt].nNumMatModel		= g_ObjectModelInfo[OBJECT_MODEL_RAFT].nNumMatModel;
			break;
		case OBJECT_MODEL_TREASURE:
			g_ObjectModel[nCnt].pD3DTextureModel	= g_ObjectModelInfo[OBJECT_MODEL_TREASURE].pD3DTextureModel;
			g_ObjectModel[nCnt].pD3DXBuffMatModel	= g_ObjectModelInfo[OBJECT_MODEL_TREASURE].pD3DXBuffMatModel;
			g_ObjectModel[nCnt].pD3DXMeshModel		= g_ObjectModelInfo[OBJECT_MODEL_TREASURE].pD3DXMeshModel;
			g_ObjectModel[nCnt].pMeshMat			= g_ObjectModelInfo[OBJECT_MODEL_TREASURE].pMeshMat;
			g_ObjectModel[nCnt].pMeshTex			= g_ObjectModelInfo[OBJECT_MODEL_TREASURE].pMeshTex;
			g_ObjectModel[nCnt].nNumMatModel		= g_ObjectModelInfo[OBJECT_MODEL_TREASURE].nNumMatModel;
			break;
		default:
			break;

		}
		g_ObjectModel[nCnt].bLive = true;
		g_ObjectModel[nCnt].posModel = posModel;
		g_ObjectModel[nCnt].rotModel = rotModel;
		g_ObjectModel[nCnt].scaleModel = sclModel;
		g_ObjectModel[nCnt].nIdxShadow = CreateShadow(g_ObjectModel[nCnt].posModel, 25.0f, 25.0f);
		break;
	}
}

void Setting3DObject(int nMap) {
	switch (nMap) {
	case 0:

		break;
	case 1:

		break;
	case 2:
		SetInfo3DObject(OBJECT_MODEL_HOUSE, D3DXVECTOR3(-150.0f, 0.0f, 105.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 20.0f));
		break;
	case 3:
		SetInfo3DObject(OBJECT_MODEL_FENCE, D3DXVECTOR3(-250.0f, 0.0f, -85.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f));
		SetInfo3DObject(OBJECT_MODEL_FENCE, D3DXVECTOR3(-230.0f, 0.0f, -85.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f));
		SetInfo3DObject(OBJECT_MODEL_FENCE, D3DXVECTOR3(-210.0f, 0.0f, -85.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f));
		SetInfo3DObject(OBJECT_MODEL_FENCE, D3DXVECTOR3(-190.0f, 0.0f, -85.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f));
		SetInfo3DObject(OBJECT_MODEL_FENCE, D3DXVECTOR3(-170.0f, 0.0f, -85.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f));
		SetInfo3DObject(OBJECT_MODEL_FENCE, D3DXVECTOR3(-150.0f, 0.0f, -85.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f));
		SetInfo3DObject(OBJECT_MODEL_FENCE, D3DXVECTOR3(-130.0f, 0.0f, -85.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f));
		SetInfo3DObject(OBJECT_MODEL_FENCE, D3DXVECTOR3(-110.0f, 0.0f, -85.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f));
		SetInfo3DObject(OBJECT_MODEL_FENCE, D3DXVECTOR3(110.0f, 0.0f, -85.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f));
		SetInfo3DObject(OBJECT_MODEL_FENCE, D3DXVECTOR3(130.0f, 0.0f, -85.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f));
		SetInfo3DObject(OBJECT_MODEL_FENCE, D3DXVECTOR3(150.0f, 0.0f, -85.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f));
		SetInfo3DObject(OBJECT_MODEL_FENCE, D3DXVECTOR3(170.0f, 0.0f, -85.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f));
		SetInfo3DObject(OBJECT_MODEL_FENCE, D3DXVECTOR3(190.0f, 0.0f, -85.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f));
		SetInfo3DObject(OBJECT_MODEL_FENCE, D3DXVECTOR3(210.0f, 0.0f, -85.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f));
		SetInfo3DObject(OBJECT_MODEL_FENCE, D3DXVECTOR3(230.0f, 0.0f, -85.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f));
		SetInfo3DObject(OBJECT_MODEL_FENCE, D3DXVECTOR3(250.0f, 0.0f, -85.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f));

		break;
	case 4:

		break;
	case 5:
		//SetInfo3DObject(ITEM_LOG, LOG_MODEL_POS);
		//SetInfo3DObject(ITEM_TORCH, TORCH_MODEL_POS);

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
		SetInfo3DObject(OBJECT_MODEL_RAFT, D3DXVECTOR3(-45.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 90.0f, 0.0f), D3DXVECTOR3(40.0f, 40.0f, 40.0f));

		break;
	case 14:
		SetInfo3DObject(OBJECT_MODEL_PALM, D3DXVECTOR3(70.0f, 0.0f, -160.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f));

		break;
	case 15:

		break;

	default:
		break;
	}
}

void Delete3DObject() {
	for (int nCnt = 0; nCnt < MAX_NUM_3DOBJECT; nCnt++) {
		if (!g_ObjectModel[nCnt].bLive)
			continue;
		g_ObjectModel[nCnt].bLive	= false;
		g_ObjectModel[nCnt].posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ObjectModel[nCnt].rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ObjectModel[nCnt].scaleModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ReleaseShadow(g_ObjectModel[nCnt].nIdxShadow);
	}
}
