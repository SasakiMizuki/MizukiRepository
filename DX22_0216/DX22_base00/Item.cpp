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
// マクロ定義
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
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexItemBg(LPDIRECT3DDEVICE9 pDevice);
void MakeVertexItemIcon(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
tItemModelData g_ItemModel[ITEM_MODEL_NUM_MAX];
tItemIconData g_ItemIcon[ITEM_NUM_MAX];
tItemIconData g_tItem_bg;

bool bEnd;
//=============================================================================
// 初期化処理
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
		//位置、回転、スケールの初期設定
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
			//Xファイル読み込み
			if (FAILED(D3DXLoadMeshFromX(
				FileName.c_str(),				//Xファイル名
				D3DXMESH_SYSTEMMEM,		//メッシュ作成のオプション
				pDevice,				//デバイスへのポインタ
				NULL,					//隣接性データを含むバッファへのポインタ
				&g_ItemModel[nCnt].pD3DXBuffMatModel,	//マテリアルデータを含むバッファ
				NULL,					//エフェクトインスタンスへの配列を含むポインタ
				&g_ItemModel[nCnt].nNumMatModel,		//D3DXMATERIAL構造体の数
				&g_ItemModel[nCnt].pD3DXMeshModel		//メッシュのポインタ
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

			//使用しているテクスチャがあれば読み込む
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
		// 影の成分
		//g_ItemModel[nCnt].nIdxShadow = CreateShadow(g_ItemModel[nCnt].posModel, 25.0f, 25.0f);

		//pMatBuf->Release();
	}

	for (int nCnt = 0; nCnt < ITEM_NUM_MAX; nCnt++) {
		g_ItemIcon[nCnt].bLive = false;
		g_ItemIcon[nCnt].bHave = false;
	}

	// テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, TORCH_ICON_FILE_NAME, &g_ItemIcon[ITEM_TORCH].pTextureItemIcon);
	D3DXCreateTextureFromFile(pDevice, LOG_ICON_FILE_NAME, &g_ItemIcon[ITEM_LOG].pTextureItemIcon);
	D3DXCreateTextureFromFile(pDevice, ROPE_ICON_FILE_NAME, &g_ItemIcon[ITEM_ROPE].pTextureItemIcon);
	D3DXCreateTextureFromFile(pDevice, BOTTLE_ICON_FILE_NAME, &g_ItemIcon[ITEM_BOTTLE].pTextureItemIcon);
	D3DXCreateTextureFromFile(pDevice, CLOTH_ICON_FILE_NAME, &g_ItemIcon[ITEM_CLOTH].pTextureItemIcon);
	D3DXCreateTextureFromFile(pDevice, FOOD_ICON_FILE_NAME, &g_ItemIcon[ITEM_FOOD].pTextureItemIcon);
	D3DXCreateTextureFromFile(pDevice, FLIPPERS_ICON_FILE_NAME, &g_ItemIcon[ITEM_FLIPPERS].pTextureItemIcon);

	// 座標設定
	for (int nCnt = 0; nCnt < ITEM_NUM_MAX; nCnt++) {
		g_ItemIcon[nCnt].fTexPosX  = 32 + nCnt * ICON_INTERVAL;
		g_ItemIcon[nCnt].fTexPosY  = 8.0f;
		g_ItemIcon[nCnt].nTexSizeX  = ICON_SIZEX;
		g_ItemIcon[nCnt].nTexSizeY  = ICON_SIZEY;
	}

	// テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, ITEM_BG_FILE_NAME, &g_tItem_bg.pTextureItemIcon);
	// 座標設定
	g_tItem_bg.fTexPosX = 0.0f;
	g_tItem_bg.fTexPosX = 0.0f;

	MakeVertexItemBg(pDevice);
	MakeVertexItemIcon(pDevice);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitItem(void)
{
	for (int nCnt = 0; nCnt < ITEM_MODEL_NUM_MAX; nCnt++) {
		if (g_ItemModel[nCnt].pD3DXBuffMatModel != NULL) {
			//バッファ解放
			g_ItemModel[nCnt].pD3DXBuffMatModel->Release();
			g_ItemModel[nCnt].pD3DXBuffMatModel = NULL;
		}
		if (g_ItemModel[nCnt].pD3DXMeshModel != NULL) {
			//メッシュ解放
			g_ItemModel[nCnt].pD3DXMeshModel->Release();
			g_ItemModel[nCnt].pD3DXMeshModel = NULL;
		}

		DWORD	i;
		// テクスチャ開放
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
		//テクスチャの開放
		if (g_ItemIcon[nCnt].pTextureItemIcon != NULL) {
			g_ItemIcon[nCnt].pTextureItemIcon->Release();
			g_ItemIcon[nCnt].pTextureItemIcon = NULL;
		}
	}

}

//=============================================================================
// 更新処理
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

	// アイテム獲得
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
			// 影の位置を設定
			//SetPositionShadow(g_ItemModel[nCnt].nIdxShadow, g_ItemModel[nCnt].posModel);
		}
	}

	// クリア判定
	if (GetFieldNumber() == 13 &&
		PlayerData->posModel.x < -7.0f &&
		PlayerData->posModel.x > -105.0f &&
		PlayerData->posModel.z < 70.0f) {
		for (nCnt = 0; g_ItemIcon[nCnt].bHave && nCnt < ITEM_NUM_MAX; nCnt ++);
		if (nCnt == ITEM_NUM_MAX) {
			SetMessageData(50, 420, 70, "これで脱出できそうだ");
			if (GetKeyboardTrigger(DIK_RETURN)) {
				StartFadeOut();
				bEnd = true;
			}
			if (bEnd && GetFade() == FADE_NONE)
				SetGameState(STATE_ENDING);
		} else if (nCnt != ITEM_NUM_MAX) {
			SetMessageData(50, 420, 90, "イカダを直せば脱出できそうだが....");
		}
	}

	//デバッグコマンド
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
// 描画処理
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

		//ワールドマトリクスの初期化
		D3DXMatrixIdentity(&g_ItemModel[nCnt].mtxWorld);	// Identity:単位○○

												//現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// スケールを反映
		D3DXMatrixScaling(
			&mtxScale,		//格納先
			g_ItemModel[nCnt].scaleModel.x,
			g_ItemModel[nCnt].scaleModel.y,
			g_ItemModel[nCnt].scaleModel.z
			);
		D3DXMatrixMultiply(
			&g_ItemModel[nCnt].mtxWorld,	//格納先(A*B)
			&g_ItemModel[nCnt].mtxWorld,	//A
			&mtxScale		//B
			);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(
			&mtxRot,		//格納先
			g_ItemModel[nCnt].rotModel.y,	//ヨー(左右)
			g_ItemModel[nCnt].rotModel.x,	//ピッチ(前後)
			g_ItemModel[nCnt].rotModel.z	//ロール(回転)
			);
		D3DXMatrixMultiply(
			&g_ItemModel[nCnt].mtxWorld,	//格納先(A*B)
			&g_ItemModel[nCnt].mtxWorld,	//A
			&mtxRot			//B
			);

		// 移動を反映
		D3DXMatrixTranslation(
			&mtxTrans,		//格納先
			g_ItemModel[nCnt].posModel.x,	//
			g_ItemModel[nCnt].posModel.y,	//
			g_ItemModel[nCnt].posModel.z	//
			);
		D3DXMatrixMultiply(
			&g_ItemModel[nCnt].mtxWorld,	//格納先(A*B)
			&g_ItemModel[nCnt].mtxWorld,	//A
			&mtxTrans		//B
			);

		//ワールドマトリクスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_ItemModel[nCnt].mtxWorld);

		//マテリアル情報に対するポインタを取得
		pD3DXMat = (D3DXMATERIAL*)g_ItemModel[nCnt].pD3DXBuffMatModel->GetBufferPointer();


		for (int nCntMat = 0; nCntMat < (int)g_ItemModel[nCnt].nNumMatModel; nCntMat ++) {
			//マテリアルの設定
			pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
			//テクスチャの設定
			pDevice->SetTexture(0, g_ItemModel[nCnt].pMeshTex[nCntMat]);
			//描画
			g_ItemModel[nCnt].pD3DXMeshModel->DrawSubset(nCntMat);
		}

		//マテリアルを元に戻す
		pDevice->SetMaterial(&matDef);
	}

	
	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_tItem_bg.pTextureItemIcon);
	//ポリゴン描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,
		NUM_POLYGON,
		&g_tItem_bg.ItemVertex[0],
		sizeof(VERTEX_2D));

	// アイコン
	for (int nCnt = 0; nCnt < ITEM_NUM_MAX; nCnt ++) {
		if (!g_ItemIcon[nCnt].bHave)
			continue;
		//テクスチャの設定
		pDevice->SetTexture(0, g_ItemIcon[nCnt].pTextureItemIcon);
		//ポリゴン描画
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

// アイテムの獲得
void AcquisitionItem(eItem Item) {
	g_ItemIcon[Item].bHave = true;
	PlaySound(SOUND_LABEL_SE_DECIDE);
	if (Item < ITEM_MODEL_NUM_MAX) {
		g_ItemModel[Item].bHave = true;
	}
	switch (Item) {
	case ITEM_TORCH:
		SetMessageData(50, 420, 120, "松明を手に入れました");
		break;
	case ITEM_LOG:
		SetMessageData(50, 420, 120, "丸太を手に入れました");
		break;
	case ITEM_ROPE:
		SetMessageData(50, 420, 120, "ロープを手に入れました");
		break;
	case ITEM_BOTTLE:
		SetMessageData(50, 420, 120, "ビンと水を手に入れました");
		break;
	case ITEM_CLOTH:
		SetMessageData(50, 420, 120, "布を手に入れました");
		break;
	case ITEM_FOOD:
		SetMessageData(50, 420, 120, "食糧を手に入れました");
		break;
	case ITEM_FLIPPERS:
		SetMessageData(50, 420, 120, "足ひれを手に入れました");
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
//	頂点の設定
//===========================================================
void MakeVertexItemBg(LPDIRECT3DDEVICE9 pDevice) {
	g_tItem_bg.ItemVertex[0].vtx = D3DXVECTOR3(g_tItem_bg.fTexPosX, g_tItem_bg.fTexPosY, 0.0f);	//(X, Y, Z)
	g_tItem_bg.ItemVertex[1].vtx = D3DXVECTOR3(g_tItem_bg.fTexPosX + ITEM_BG_SIZE_X, g_tItem_bg.fTexPosY, 0.0f);
	g_tItem_bg.ItemVertex[2].vtx = D3DXVECTOR3(g_tItem_bg.fTexPosX, g_tItem_bg.fTexPosY + ITEM_BG_SIZE_Y, 0.0f);
	g_tItem_bg.ItemVertex[3].vtx = D3DXVECTOR3(g_tItem_bg.fTexPosX + ITEM_BG_SIZE_X, g_tItem_bg.fTexPosY + ITEM_BG_SIZE_Y, 0.0f);

	g_tItem_bg.ItemVertex[0].rhw =
		g_tItem_bg.ItemVertex[1].rhw =
		g_tItem_bg.ItemVertex[2].rhw =
		g_tItem_bg.ItemVertex[3].rhw = 1.0f;	//すべてに1.0fを入れる

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
			g_ItemIcon[nCnt].ItemVertex[3].rhw = 1.0f;	//すべてに1.0fを入れる

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