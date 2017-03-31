//#include "Ending.h"
//
//void InitEnding() {
//
//}
//
//void UninitEnding() {
//
//}
//
//void UpdateEnding() {
//	if (GetKeyboardTrigger(DIK_1))
//		SetGameState(STATE_TITLE);
//}
//
//void DrawEnding() {
//
//}

#include "Ending.h"
#include "input.h"
#include "Model.h"
#include "Fade.h"
#include "Message.h"

//----- マクロ定義 -----
#define BackGround_GAMEOVER_NAME		"data/TEXTURE/Ending.jpg"	//背景ファイル名
#define	BackGround_GAMEOVER_POS_X	(0)						//ポリゴンの表示位置
#define BackGround_GAMEOVER_POS_Y	(0)						//ポリゴンの表示位置
#define BackGround_GAMEOVER_SIZE_X	(800)					//ポリゴンのサイズ
#define BackGround_GAMEOVER_SIZE_Y	(600)					//ポリゴンのサイズ

#define GAMEOVER_PATTERN_DIVIDE_X (1) 
#define GAMEOVER_PATTERN_DIVIDE_Y (1)
#define NUM_GAMEOVER_ANIME_PATTERN	 (GAMEOVER_PATTERN_DIVIDE_X * GAMEOVER_PATTERN_DIVIDE_Y)
#define GAMEOVER_PATTERN_SIZE_X   (1.0f / GAMEOVER_PATTERN_DIVIDE_X)
#define GAMEOVER_PATTERN_SIZE_Y   (1.0f / GAMEOVER_PATTERN_DIVIDE_Y)

#define ROGO_GAMEOVER_NAME		"data/TEXTURE/EndRogo.png"	//背景ファイル名
#define	ROGO_GAMEOVER_POS_X	(30)						//ポリゴンの表示位置
#define ROGO_GAMEOVER_POS_Y	(150)						//ポリゴンの表示位置
#define ROGO_GAMEOVER_SIZE_X	(730)					//ポリゴンのサイズ
#define ROGO_GAMEOVER_SIZE_Y	(56)					//ポリゴンのサイズ

#define PRESSBUTTOM_GAMEOVER_NAME		"data/TEXTURE/EndButtom.png"	//背景ファイル名
#define	PRESSBUTTOM_GAMEOVER_POS_X	(238)						//ポリゴンの表示位置
#define PRESSBUTTOM_GAMEOVER_POS_Y	(350)						//ポリゴンの表示位置
#define PRESSBUTTOM_GAMEOVER_SIZE_X	(325)					//ポリゴンのサイズ
#define PRESSBUTTOM_GAMEOVER_SIZE_Y	(50)					//ポリゴンのサイズ


#define INTERVAL_GAMEOVER_CHANGE_PATTERN (20)
#define FADE_VOLUME						 (7)


//----- プロトタイプ宣言 -----
void MakeVertexGameOver(LPDIRECT3DDEVICE9 pDevice);
void MakeVertexEnding(LPDIRECT3DDEVICE9 pDevice);

//----- グローバル変数 -----
LPDIRECT3DTEXTURE9	g_pTextureGameOver[3] ={ NULL };	//テクスチャへのポインタ

VERTEX_2D			g_aGAMEOVERVertex[3][NUM_VERTEX];		//頂点情報格納ワーク

static float g_fPosXLeft, g_fPosXRight;	//画像のX座標
static float g_fPosYUp, g_fPosYDown;		//画像のY座標
static tEnding g_tEnding[2];

static int g_nFrameCounter;	//フレームカウンタ(FPS)
static bool bChangeEnding = false;

//int g_nTestPosX = BackGround_POS_X;

//===============================================================
//	ポリゴン初期化
//===============================================================
void InitEnding() {
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	bChangeEnding = false;
	g_nFrameCounter = 0;
	//頂点情報の作成
	MakeVertexGameOver(pDevice);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BackGround_GAMEOVER_NAME, &g_pTextureGameOver[0]);
	D3DXCreateTextureFromFile(pDevice, ROGO_GAMEOVER_NAME, &g_pTextureGameOver[1]);
	D3DXCreateTextureFromFile(pDevice, PRESSBUTTOM_GAMEOVER_NAME, &g_pTextureGameOver[2]);
	g_fPosXLeft = 0.0f;
	g_fPosXRight = 1.0f;
	g_fPosYUp = 0.0f;
	g_fPosYDown = 1.0f;


	g_tEnding[0].fTexPosX			= ROGO_GAMEOVER_POS_X;
	g_tEnding[0].fTexPosY			= ROGO_GAMEOVER_POS_Y;
	g_tEnding[0].fPosXLeft			= 0;
	g_tEnding[0].fPosXRight			= 1.0;
	g_tEnding[0].fPosYUp			= 0;
	g_tEnding[0].fPosYDown			= 1.0;
	g_tEnding[0].nTexSizeX			= ROGO_GAMEOVER_SIZE_X;
	g_tEnding[0].nTexSizeY			= ROGO_GAMEOVER_SIZE_Y;
	g_tEnding[0].nFadeAlpha			= 0;
	g_tEnding[0].nFadeVol			= FADE_VOLUME;


	g_tEnding[1].fTexPosX			= PRESSBUTTOM_GAMEOVER_POS_X;
	g_tEnding[1].fTexPosY			= PRESSBUTTOM_GAMEOVER_POS_Y;
	g_tEnding[1].fPosXLeft			= 0;
	g_tEnding[1].fPosXRight			= 1.0;
	g_tEnding[1].fPosYUp			= 0;
	g_tEnding[1].fPosYDown			= 1.0;
	g_tEnding[1].nTexSizeX			= PRESSBUTTOM_GAMEOVER_SIZE_X;
	g_tEnding[1].nTexSizeY			= PRESSBUTTOM_GAMEOVER_SIZE_Y;
	g_tEnding[1].nFadeAlpha			= 0;
	g_tEnding[1].nFadeVol			= FADE_VOLUME;
}

//============================================================
//	終了処理
//============================================================
void UninitEnding(void) {
	for (int nCnt = 0; nCnt < 3; nCnt ++) {
		if (g_pTextureGameOver[nCnt] != NULL) {
			//テクスチャの開放
			g_pTextureGameOver[nCnt]->Release();
			g_pTextureGameOver[nCnt] = NULL;
		}
	}
}

//============================================================
//	更新処理
//============================================================
void UpdateEnding(void) {
	//テクスチャ座標計算
	tPlayerData * tPlayerData = GetPlayerData();
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (tPlayerData->bPlayerMove) {
		g_nFrameCounter ++;

		if (g_nFrameCounter < 2)
			StartFadeIn();
		else if (g_nFrameCounter <= 2)
			SetMessageData(50, 420, 200, "無人島から無事脱出することができた。", "あとはこのままイカダを漕ぎ続ければ元の島に帰れるはずだ");
		else if (g_nFrameCounter == 202)
			SetMessageData(50, 420, 150, "そう信じて僕はイカダを漕ぎ続けた...");
		else if (g_nFrameCounter > 420) {
			//SetMessageData(50,420,1,"そう信じて僕はイカダを漕ぎ続けた...");
			g_tEnding[0].nFadeAlpha += g_tEnding[0].nFadeVol;
			if (g_tEnding[0].nFadeAlpha > 255)
				g_tEnding[0].nFadeAlpha = 255;

			g_tEnding[1].nFadeAlpha += g_tEnding[1].nFadeVol;
			if (g_tEnding[1].nFadeAlpha > 255) {
				g_tEnding[1].nFadeAlpha = 255;
				g_tEnding[1].nFadeVol *= -1;
			}
			if (g_tEnding[1].nFadeAlpha < 0) {
				g_tEnding[1].nFadeAlpha = 0;
				g_tEnding[1].nFadeVol *= -1;
			}
			if (GetKeyboardTrigger(DIK_T)) {
				bChangeEnding = true;
				StartFadeOut();
			}
			if (bChangeEnding && GetFade() == FADE_NONE)
				SetGameState(STATE_TITLE);

		}
	}

	MakeVertexGameOver(pDevice);
	MakeVertexEnding(pDevice);

}

//============================================================
//	描画処理
//============================================================
void DrawEnding(void) {
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < 3; nCnt ++) {
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureGameOver[nCnt]);
		//ポリゴン描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,
			NUM_POLYGON,
			&g_aGAMEOVERVertex[nCnt][0],
			sizeof(VERTEX_2D));
	}
}

//===========================================================
//	頂点の設定
//===========================================================
void MakeVertexGameOver(LPDIRECT3DDEVICE9 pDevice) {

	//頂点座標	※時計回り注意
	g_aGAMEOVERVertex[0][0].vtx = D3DXVECTOR3(BackGround_GAMEOVER_POS_X, BackGround_GAMEOVER_POS_Y, 0.0f);	//(X, Y, Z)
	g_aGAMEOVERVertex[0][1].vtx = D3DXVECTOR3(BackGround_GAMEOVER_POS_X + BackGround_GAMEOVER_SIZE_X, BackGround_GAMEOVER_POS_Y, 0.0f);
	g_aGAMEOVERVertex[0][2].vtx = D3DXVECTOR3(BackGround_GAMEOVER_POS_X, BackGround_GAMEOVER_POS_Y + BackGround_GAMEOVER_SIZE_Y, 0.0f);
	g_aGAMEOVERVertex[0][3].vtx = D3DXVECTOR3(BackGround_GAMEOVER_POS_X + BackGround_GAMEOVER_SIZE_X, BackGround_GAMEOVER_POS_Y + BackGround_GAMEOVER_SIZE_Y, 0.0f);

	//rhw
	g_aGAMEOVERVertex[0][0].rhw =
		g_aGAMEOVERVertex[0][1].rhw =
		g_aGAMEOVERVertex[0][2].rhw =
		g_aGAMEOVERVertex[0][3].rhw = 1.0f;	//すべてに1.0fを入れる

											//頂点カラー
	g_aGAMEOVERVertex[0][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_aGAMEOVERVertex[0][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_aGAMEOVERVertex[0][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_aGAMEOVERVertex[0][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	g_aGAMEOVERVertex[0][0].tex = D3DXVECTOR2(g_fPosXLeft, g_fPosYUp);
	g_aGAMEOVERVertex[0][1].tex = D3DXVECTOR2(g_fPosXRight, g_fPosYUp);
	g_aGAMEOVERVertex[0][2].tex = D3DXVECTOR2(g_fPosXLeft, g_fPosYDown);
	g_aGAMEOVERVertex[0][3].tex = D3DXVECTOR2(g_fPosXRight, g_fPosYDown);
}

//===========================================================
//	頂点の設定
//===========================================================
void MakeVertexEnding(LPDIRECT3DDEVICE9 pDevice) {

	for (int nCnt = 1; nCnt < 3; nCnt++) {
		//頂点座標	※時計回り注意
		g_aGAMEOVERVertex[nCnt][0].vtx = D3DXVECTOR3(g_tEnding[nCnt - 1].fTexPosX, g_tEnding[nCnt - 1].fTexPosY, 0.0f);	//(X, Y, Z)
		g_aGAMEOVERVertex[nCnt][1].vtx = D3DXVECTOR3(g_tEnding[nCnt - 1].fTexPosX + g_tEnding[nCnt - 1].nTexSizeX, g_tEnding[nCnt - 1].fTexPosY, 0.0f);
		g_aGAMEOVERVertex[nCnt][2].vtx = D3DXVECTOR3(g_tEnding[nCnt - 1].fTexPosX, g_tEnding[nCnt - 1].fTexPosY + g_tEnding[nCnt - 1].nTexSizeY, 0.0f);
		g_aGAMEOVERVertex[nCnt][3].vtx = D3DXVECTOR3(g_tEnding[nCnt - 1].fTexPosX + g_tEnding[nCnt - 1].nTexSizeX, g_tEnding[nCnt - 1].fTexPosY + g_tEnding[nCnt - 1].nTexSizeY, 0.0f);

		//rhw		   
		g_aGAMEOVERVertex[nCnt][0].rhw =
			g_aGAMEOVERVertex[nCnt][1].rhw =
			g_aGAMEOVERVertex[nCnt][2].rhw =
			g_aGAMEOVERVertex[nCnt][3].rhw = 1.0f;	//すべてに1.0fを入れる

													//頂点カラー	  
		g_aGAMEOVERVertex[nCnt][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, g_tEnding[nCnt - 1].nFadeAlpha);
		g_aGAMEOVERVertex[nCnt][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, g_tEnding[nCnt - 1].nFadeAlpha);
		g_aGAMEOVERVertex[nCnt][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, g_tEnding[nCnt - 1].nFadeAlpha);
		g_aGAMEOVERVertex[nCnt][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, g_tEnding[nCnt - 1].nFadeAlpha);

		//テクスチャ座標の設定
		g_aGAMEOVERVertex[nCnt][0].tex = D3DXVECTOR2(g_tEnding[nCnt - 1].fPosXLeft, g_tEnding[nCnt - 1].fPosYUp);
		g_aGAMEOVERVertex[nCnt][1].tex = D3DXVECTOR2(g_tEnding[nCnt - 1].fPosXRight, g_tEnding[nCnt - 1].fPosYUp);
		g_aGAMEOVERVertex[nCnt][2].tex = D3DXVECTOR2(g_tEnding[nCnt - 1].fPosXLeft, g_tEnding[nCnt - 1].fPosYDown);
		g_aGAMEOVERVertex[nCnt][3].tex = D3DXVECTOR2(g_tEnding[nCnt - 1].fPosXRight, g_tEnding[nCnt - 1].fPosYDown);
	}
}