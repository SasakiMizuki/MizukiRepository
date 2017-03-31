//=============================================================================
//
// モデル処理 [model.cpp]
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
// マクロ定義
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
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
tPlayerData Player;


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitModel(LPDIRECT3DDEVICE9 pDevice)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	Player.pD3DXMeshModel = NULL;
	//Player.pD3DXBuffMatModel = NULL;
	Player.nNumMatModel  = 0;
	
	//位置、回転、スケールの初期設定
	Player.posModel = DEFAULTPLAYER_POS;
	Player.rotModel = D3DXVECTOR3(0.0f,0.0f,0.0f);
	Player.scaleModel = D3DXVECTOR3(10.0f,10.0f,10.0f);

	Player.bPlayerMove = true;
	
	LPD3DXBUFFER	pMatBuf	= NULL;

	//Xファイル読み込み
	if(FAILED(D3DXLoadMeshFromX(
		FILE_NAME,				//Xファイル名
		D3DXMESH_SYSTEMMEM,		//メッシュ作成のオプション
		pDevice,				//デバイスへのポインタ
		NULL,					//隣接性データを含むバッファへのポインタ
		&Player.pD3DXBuffMatModel,	//マテリアルデータを含むバッファ
		NULL,					//エフェクトインスタンスへの配列を含むポインタ
		&Player.nNumMatModel,		//D3DXMATERIAL構造体の数
		&Player.pD3DXMeshModel		//メッシュのポインタ
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

		//使用しているテクスチャがあれば読み込む
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

	// 影の成分
	Player.nIdxShadow = CreateShadow( Player.posModel, 25.0f, 25.0f);
	
	//pMatBuf->Release();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitModel(void)
{
	if(Player.pD3DXBuffMatModel != NULL){
		//バッファ解放
		Player.pD3DXBuffMatModel->Release();
		Player.pD3DXBuffMatModel = NULL;
	}
	if(Player.pD3DXMeshModel != NULL){
		//メッシュ解放
		Player.pD3DXMeshModel->Release();
		Player.pD3DXMeshModel = NULL;
	}
	
	DWORD	i;
	// テクスチャ開放
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
// 更新処理
//=============================================================================
void UpdateModel(void)
{
	///////////////////////////////////////
	//if (GetKeyboardTrigger(DIK_3))
	//	SetGameState(STATE_ENDING);
	///////////////////////////////////////
	//平行移動
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
	// ジャンプ
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

	// 移動量合算
	Player.posModel += D3DXVECTOR3(Player.moveModel.x, Player.moveModel.y, Player.moveModel.z);

	if (Player.posModel.y < DEFAULTPLAYER_POS.y && Player.bPlayerJump) {
		Player.bPlayerJump = false;
		Player.moveModel.y = 0.0f;
		Player.posModel.y = DEFAULTPLAYER_POS.y;
		Player.fJumpTime = 0;
	}

	Player.moveModel = D3DXVECTOR3(0, 0, 0);

	//回転
	if(GetKeyboardPress(DIK_A) || GetKeyboardPress(DIK_LEFT)){
		Player.rotModel.y -= ROTE_VOL;
	}
	if(GetKeyboardPress(DIK_D) || GetKeyboardPress(DIK_RIGHT)){
		Player.rotModel.y += ROTE_VOL;
	}

	//拡大縮小
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
	// 影の位置を設定
	SetPositionShadow(Player.nIdxShadow, Player.posModel);

	// Effect Setting
	SetEffect(Player.posModel, D3DXVECTOR3(0,0,0), D3DXCOLOR(1,1,0,1), 20, 20, 30);
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawModel(LPDIRECT3DDEVICE9 pDevice)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	D3DXMATERIAL * 	pD3DXMat;
	D3DMATERIAL9	matDef;
	
	D3DXMATRIX mtxScale,mtxRot,mtxTrans;
	
	pDevice->SetFVF(Player.pD3DXMeshModel->GetFVF());

	//ワールドマトリクスの初期化
	D3DXMatrixIdentity(&Player.mtxWorld);	// Identity:単位○○

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);
	
	// スケールを反映
	D3DXMatrixScaling(
		&mtxScale,		//格納先
		Player.scaleModel.x,
		Player.scaleModel.y,
		Player.scaleModel.z
	);
	D3DXMatrixMultiply(
		&Player.mtxWorld,	//格納先(A*B)
		&Player.mtxWorld,	//A
		&mtxScale		//B
	);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(
		&mtxRot,		//格納先
		Player.rotModel.y,	//ヨー(左右)
		Player.rotModel.x,	//ピッチ(前後)
		Player.rotModel.z	//ロール(回転)
	);
	D3DXMatrixMultiply(
		&Player.mtxWorld,	//格納先(A*B)
		&Player.mtxWorld,	//A
		&mtxRot			//B
	);

	// 移動を反映
	D3DXMatrixTranslation(
		&mtxTrans,		//格納先
		Player.posModel.x,	//
		Player.posModel.y,	//
		Player.posModel.z	//
	);
	D3DXMatrixMultiply(
		&Player.mtxWorld,	//格納先(A*B)
		&Player.mtxWorld,	//A
		&mtxTrans		//B
	);

	//ワールドマトリクスの設定
	pDevice->SetTransform(D3DTS_WORLD,&Player.mtxWorld);

	//マテリアル情報に対するポインタを取得
	pD3DXMat = (D3DXMATERIAL*)Player.pD3DXBuffMatModel->GetBufferPointer();
	

	for(int nCntMat = 0; nCntMat < (int)Player.nNumMatModel; nCntMat ++){
		//マテリアルの設定
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
		//テクスチャの設定
		pDevice->SetTexture(0, Player.pMeshTex[nCntMat]);
		//描画
		Player.pD3DXMeshModel->DrawSubset(nCntMat);
	}
	
	//マテリアルを元に戻す
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