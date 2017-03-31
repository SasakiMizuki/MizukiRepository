//=============================================================================
//
// モデル処理 [model.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "Sky.h"
#include "shadow.h"
#include "effect.h"
#include "Object.h"

#include <math.h>

//*****************************************************************************
// マクロ定義
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
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
tSkyData Sky;


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitSky(LPDIRECT3DDEVICE9 pDevice)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();

	Sky.pD3DXMeshModel = NULL;
	//Sky.pD3DXBuffMatModel = NULL;
	Sky.nNumMatModel  = 0;

	LPD3DXBUFFER	pMatBuf	= NULL;

	//Xファイル読み込み
	if (FAILED(D3DXLoadMeshFromX(
		FILE_NAME,				//Xファイル名
		D3DXMESH_SYSTEMMEM,		//メッシュ作成のオプション
		pDevice,				//デバイスへのポインタ
		NULL,					//隣接性データを含むバッファへのポインタ
		&Sky.pD3DXBuffMatModel,	//マテリアルデータを含むバッファ
		NULL,					//エフェクトインスタンスへの配列を含むポインタ
		&Sky.nNumMatModel,		//D3DXMATERIAL構造体の数
		&Sky.pD3DXMeshModel		//メッシュのポインタ
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

		//使用しているテクスチャがあれば読み込む
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

	//位置、回転、スケールの初期設定
	Sky.posModel = DEFAULTSKY_POS;
	Sky.rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Sky.scaleModel = D3DXVECTOR3(8.0f, 8.0f, 8.0f);

	// 影の成分
	//Sky.nIdxShadow = CreateShadow(Sky.posModel, 25.0f, 25.0f);

	//pMatBuf->Release();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitSky(void)
{
	if (Sky.pD3DXBuffMatModel != NULL) {
		//バッファ解放
		Sky.pD3DXBuffMatModel->Release();
		Sky.pD3DXBuffMatModel = NULL;
	}
	if (Sky.pD3DXMeshModel != NULL) {
		//メッシュ解放
		Sky.pD3DXMeshModel->Release();
		Sky.pD3DXMeshModel = NULL;
	}

	DWORD	i;
	// テクスチャ開放
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
// 更新処理
//=============================================================================
void UpdateSky(void)
{
	
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawSky(LPDIRECT3DDEVICE9 pDevice)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATERIAL * 	pD3DXMat;
	D3DMATERIAL9	matDef;

	D3DXMATRIX mtxScale, mtxRot, mtxTrans;

	pDevice->SetFVF(Sky.pD3DXMeshModel->GetFVF());

	////ワールドマトリクスの初期化
	D3DXMatrixIdentity(&Sky.mtxWorld);	// Identity:単位○○

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// スケールを反映
	D3DXMatrixScaling(
		&mtxScale,		//格納先
		Sky.scaleModel.x,
		Sky.scaleModel.y,
		Sky.scaleModel.z
		);
	D3DXMatrixMultiply(
		&Sky.mtxWorld,	//格納先(A*B)
		&Sky.mtxWorld,	//A
		&mtxScale		//B
		);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(
		&mtxRot,		//格納先
		Sky.rotModel.y,	//ヨー(左右)
		Sky.rotModel.x,	//ピッチ(前後)
		Sky.rotModel.z	//ロール(回転)
		);
	D3DXMatrixMultiply(
		&Sky.mtxWorld,	//格納先(A*B)
		&Sky.mtxWorld,	//A
		&mtxRot			//B
		);

	// 移動を反映
	D3DXMatrixTranslation(
		&mtxTrans,		//格納先
		Sky.posModel.x,	//
		Sky.posModel.y,	//
		Sky.posModel.z	//
		);
	D3DXMatrixMultiply(
		&Sky.mtxWorld,	//格納先(A*B)
		&Sky.mtxWorld,	//A
		&mtxTrans		//B
		);

	//ワールドマトリクスの設定
	pDevice->SetTransform(D3DTS_WORLD, &Sky.mtxWorld);

	//マテリアル情報に対するポインタを取得
	pD3DXMat = (D3DXMATERIAL*)Sky.pD3DXBuffMatModel->GetBufferPointer();


	for (int nCntMat = 0; nCntMat < (int)Sky.nNumMatModel; nCntMat ++) {
		//マテリアルの設定
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
		//テクスチャの設定
		pDevice->SetTexture(0, Sky.pMeshTex[nCntMat]);
		//描画
		Sky.pD3DXMeshModel->DrawSubset(nCntMat);
	}

	//マテリアルを元に戻す
	pDevice->SetMaterial(&matDef);
}