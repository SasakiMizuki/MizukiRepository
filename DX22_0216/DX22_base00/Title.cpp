//#include "Title.h"
//
//void InitTitle() {
//
//}
//void UninitTitle() {
//
//}
//void UpdateTitle() {
//	if (GetKeyboardTrigger(DIK_2))
//		SetGameState(STATE_GAMEMAIN);
//}
//void DrawTitle() {
//
//}
#include "Title.h"
#include "input.h"
#include "sound.h"
#include "Fade.h"
#include "Model.h"

//----- マクロ定義 -----
#define BackGround_TITLE_NAME		"data/TEXTURE/title.jpg"	//背景ファイル名
#define	BackGround_TITLE_POS_X	(0)						//ポリゴンの表示位置
#define BackGround_TITLE_POS_Y	(0)						//ポリゴンの表示位置
#define BackGround_TITLE_SIZE_X	(800)					//ポリゴンのサイズ
#define BackGround_TITLE_SIZE_Y	(600)					//ポリゴンのサイズ

#define TITLE_PATTERN_DIVIDE_X (6) 
#define TITLE_PATTERN_DIVIDE_Y (6)
#define NUM_TITLE_ANIME_PATTERN	 (TITLE_PATTERN_DIVIDE_X * TITLE_PATTERN_DIVIDE_Y)
#define TITLE_PATTERN_SIZE_X   (1.0f / TITLE_PATTERN_DIVIDE_X)
#define TITLE_PATTERN_SIZE_Y   (1.0f / TITLE_PATTERN_DIVIDE_Y)

#define ROGO_TITLE_NAME		"data/TEXTURE/rogo.png"	//背景ファイル名
#define	ROGO_TITLE_POS_X	(0)						//ポリゴンの表示位置
#define ROGO_TITLE_POS_Y	(50)						//ポリゴンの表示位置
#define ROGO_TITLE_SIZE_X	(800)					//ポリゴンのサイズ
#define ROGO_TITLE_SIZE_Y	(180)					//ポリゴンのサイズ

#define TITLEROGO_PATTERN_DIVIDE_X (1) 
#define TITLEROGO_PATTERN_DIVIDE_Y (1)
#define NUM_TITLEROGO_ANIME_PATTERN	 (TITLEROGO_PATTERN_DIVIDE_X * TITLEROGO_PATTERN_DIVIDE_Y)
#define TITLEROGO_PATTERN_SIZE_X   (1.0f / TITLEROGO_PATTERN_DIVIDE_X)
#define TITLEROGO_PATTERN_SIZE_Y   (1.0f / TITLEROGO_PATTERN_DIVIDE_Y)

#define PRESSENTER_TITLE_NAME		"data/TEXTURE/bottom.png"	//背景ファイル名
#define	PRESSENTER_TITLE_POS_X	(190)						//ポリゴンの表示位置
#define PRESSENTER_TITLE_POS_Y	(275)						//ポリゴンの表示位置
#define PRESSENTER_TITLE_SIZE_X	(420)					//ポリゴンのサイズ
#define PRESSENTER_TITLE_SIZE_Y	(50)					//ポリゴンのサイズ

#define TITLEPRESSENTER_PATTERN_DIVIDE_X (1) 
#define TITLEPRESSENTER_PATTERN_DIVIDE_Y (1)
#define NUM_TITLEPRESSENTER_ANIME_PATTERN	 (TITLEPRESSENTER_PATTERN_DIVIDE_X * TITLEPRESSENTER_PATTERN_DIVIDE_Y)
#define TITLEPRESSENTER_PATTERN_SIZE_X   (1.0f / TITLEPRESSENTER_PATTERN_DIVIDE_X)
#define TITLEPRESSENTER_PATTERN_SIZE_Y   (1.0f / TITLEPRESSENTER_PATTERN_DIVIDE_Y)

#define INTERVAL_TITLE_CHANGE_PATTERN (7)


//----- プロトタイプ宣言 -----
void MakeVertexTitle(LPDIRECT3DDEVICE9 pDevice);

//----- グローバル変数 -----
LPDIRECT3DTEXTURE9	g_pTextureTitle[TITLE_NUM_MAX] ={ NULL };	//テクスチャへのポインタ

VERTEX_2D			g_aTITLEVertex[TITLE_NUM_MAX][NUM_VERTEX];		//頂点情報格納ワーク

static tTitle g_tTitle[TITLE_NUM_MAX];
static int g_nFadeVol;

static int g_nPatternAnime;
static int g_nCounterAnime;	//アニメカウンタ(FPS)
static bool bChangeTitle = false;

//int g_nTestPosX = BackGround_POS_X;

//===============================================================
//	ポリゴン初期化
//===============================================================
void InitTitle() {
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点情報の作成
	MakeVertexTitle(pDevice);

	//PlaySound(SOUND_LABEL_BGM001);

	g_nPatternAnime = 0;	////0から数えて5番目(実質6番目)
	g_nFadeVol = 5;

	bChangeTitle = false;
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BackGround_TITLE_NAME, &g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice, ROGO_TITLE_NAME, &g_pTextureTitle[1]);
	D3DXCreateTextureFromFile(pDevice, PRESSENTER_TITLE_NAME, &g_pTextureTitle[2]);

	g_tTitle[TITLE_BG].fTexPosX = BackGround_TITLE_POS_X;
	g_tTitle[TITLE_BG].fTexPosY = BackGround_TITLE_POS_Y;
	g_tTitle[TITLE_BG].nTexSizeX = BackGround_TITLE_SIZE_X;
	g_tTitle[TITLE_BG].nTexSizeY = BackGround_TITLE_SIZE_Y;
	g_tTitle[TITLE_BG].fPosXLeft = 0.0f;
	g_tTitle[TITLE_BG].fPosXRight = g_tTitle[TITLE_BG].fPosXLeft + TITLE_PATTERN_SIZE_X;
	g_tTitle[TITLE_BG].fPosYUp	  = 0.0f;
	g_tTitle[TITLE_BG].fPosYDown = g_tTitle[TITLE_BG].fPosYUp + TITLE_PATTERN_SIZE_Y;
	g_tTitle[TITLE_BG].nFadeAlpha = 255;

	g_tTitle[TITLE_ROGO].fTexPosX   = ROGO_TITLE_POS_X;
	g_tTitle[TITLE_ROGO].fTexPosY   = ROGO_TITLE_POS_Y;
	g_tTitle[TITLE_ROGO].nTexSizeX  = ROGO_TITLE_SIZE_X;
	g_tTitle[TITLE_ROGO].nTexSizeY  = ROGO_TITLE_SIZE_Y;
	g_tTitle[TITLE_ROGO].fPosXLeft  = 0.0f;
	g_tTitle[TITLE_ROGO].fPosXRight = g_tTitle[TITLE_ROGO].fPosXLeft + TITLEROGO_PATTERN_SIZE_X;
	g_tTitle[TITLE_ROGO].fPosYUp	 = 0.0f;
	g_tTitle[TITLE_ROGO].fPosYDown  = g_tTitle[TITLE_ROGO].fPosYUp + TITLEROGO_PATTERN_SIZE_Y;
	g_tTitle[TITLE_ROGO].nFadeAlpha = 255;

	g_tTitle[TITLE_PRESSSTART].fTexPosX   = PRESSENTER_TITLE_POS_X;
	g_tTitle[TITLE_PRESSSTART].fTexPosY   = PRESSENTER_TITLE_POS_Y;
	g_tTitle[TITLE_PRESSSTART].nTexSizeX  = PRESSENTER_TITLE_SIZE_X;
	g_tTitle[TITLE_PRESSSTART].nTexSizeY  = PRESSENTER_TITLE_SIZE_Y;
	g_tTitle[TITLE_PRESSSTART].fPosXLeft  = 0.0f;
	g_tTitle[TITLE_PRESSSTART].fPosXRight = g_tTitle[TITLE_PRESSSTART].fPosXLeft + TITLEPRESSENTER_PATTERN_SIZE_X;
	g_tTitle[TITLE_PRESSSTART].fPosYUp	   = 0.0f;
	g_tTitle[TITLE_PRESSSTART].fPosYDown  = g_tTitle[TITLE_PRESSSTART].fPosYUp + TITLEPRESSENTER_PATTERN_SIZE_Y;
	g_tTitle[TITLE_PRESSSTART].nFadeAlpha = 255;


	//StartFadeIn();
}

//============================================================
//	終了処理
//============================================================
void UninitTitle(void) {
	for (int nCnt = 0; nCnt < TITLE_NUM_MAX; nCnt ++) {
		if (g_pTextureTitle[nCnt] != NULL) {
			//テクスチャの開放
			g_pTextureTitle[nCnt]->Release();
			g_pTextureTitle[nCnt] = NULL;
		}
	}
}

//============================================================
//	更新処理
//============================================================
void UpdateTitle(void) {
	//テクスチャ座標計算
	g_nCounterAnime ++;

	/*if ((g_nCounterAnime % INTERVAL_TITLE_CHANGE_PATTERN) == 0) {
		g_nPatternAnime = (g_nPatternAnime + 1) % NUM_TITLE_ANIME_PATTERN;
	}*/

	g_tTitle[TITLE_PRESSSTART].nFadeAlpha += g_nFadeVol;
	if (g_tTitle[TITLE_PRESSSTART].nFadeAlpha > 255) {
		g_tTitle[TITLE_PRESSSTART].nFadeAlpha = 255;
		g_nFadeVol *= -1;
	}
	if (g_tTitle[TITLE_PRESSSTART].nFadeAlpha < 0) {
		g_tTitle[TITLE_PRESSSTART].nFadeAlpha = 0;
		g_nFadeVol *= -1;
	}

	if (GetKeyboardTrigger(DIK_RETURN)) {
		bChangeTitle = true;
		StartFadeOut();
	}
	if (bChangeTitle && GetFade() == FADE_NONE)
		SetGameState(STATE_GAMEMAIN);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_tTitle[TITLE_BG].fPosXLeft  = (float)(g_nPatternAnime % TITLE_PATTERN_DIVIDE_X) * TITLE_PATTERN_SIZE_X;	//余剰により分割数以上の値にならないよう処理
	g_tTitle[TITLE_BG].fPosXRight = g_tTitle[TITLE_BG].fPosXLeft + TITLE_PATTERN_SIZE_X;
	g_tTitle[TITLE_BG].fPosYUp	   = (float)(g_nPatternAnime / (NUM_TITLE_ANIME_PATTERN / TITLE_PATTERN_DIVIDE_Y)) * TITLE_PATTERN_SIZE_Y;
	g_tTitle[TITLE_BG].fPosYDown  = g_tTitle[TITLE_BG].fPosYUp + TITLE_PATTERN_SIZE_Y;

	MakeVertexTitle(pDevice);

}

//============================================================
//	描画処理
//============================================================
void DrawTitle(void) {
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < TITLE_NUM_MAX; nCnt++) {
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTitle[nCnt]);
		//ポリゴン描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,
			NUM_POLYGON,
			&g_aTITLEVertex[nCnt][0],
			sizeof(VERTEX_2D));
	}
}

//===========================================================
//	頂点の設定
//===========================================================
void MakeVertexTitle(LPDIRECT3DDEVICE9 pDevice) {

	for (int nCnt = 0; nCnt < TITLE_NUM_MAX; nCnt++) {
		//頂点座標	※時計回り注意
		g_aTITLEVertex[nCnt][0].vtx = D3DXVECTOR3(g_tTitle[nCnt].fTexPosX, g_tTitle[nCnt].fTexPosY, 0.0f);	//(X, Y, Z)
		g_aTITLEVertex[nCnt][1].vtx = D3DXVECTOR3(g_tTitle[nCnt].fTexPosX + g_tTitle[nCnt].nTexSizeX, g_tTitle[nCnt].fTexPosY, 0.0f);
		g_aTITLEVertex[nCnt][2].vtx = D3DXVECTOR3(g_tTitle[nCnt].fTexPosX, g_tTitle[nCnt].fTexPosY + g_tTitle[nCnt].nTexSizeY, 0.0f);
		g_aTITLEVertex[nCnt][3].vtx = D3DXVECTOR3(g_tTitle[nCnt].fTexPosX + g_tTitle[nCnt].nTexSizeX, g_tTitle[nCnt].fTexPosY + g_tTitle[nCnt].nTexSizeY, 0.0f);

		//rhw		   
		g_aTITLEVertex[nCnt][0].rhw =
			g_aTITLEVertex[nCnt][1].rhw =
			g_aTITLEVertex[nCnt][2].rhw =
			g_aTITLEVertex[nCnt][3].rhw = 1.0f;	//すべてに1.0fを入れる

												//頂点カラー	  
		g_aTITLEVertex[nCnt][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, g_tTitle[nCnt].nFadeAlpha);
		g_aTITLEVertex[nCnt][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, g_tTitle[nCnt].nFadeAlpha);
		g_aTITLEVertex[nCnt][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, g_tTitle[nCnt].nFadeAlpha);
		g_aTITLEVertex[nCnt][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, g_tTitle[nCnt].nFadeAlpha);

		//テクスチャ座標nCntの設定
		g_aTITLEVertex[nCnt][0].tex = D3DXVECTOR2(g_tTitle[nCnt].fPosXLeft, g_tTitle[nCnt].fPosYUp);
		g_aTITLEVertex[nCnt][1].tex = D3DXVECTOR2(g_tTitle[nCnt].fPosXRight, g_tTitle[nCnt].fPosYUp);
		g_aTITLEVertex[nCnt][2].tex = D3DXVECTOR2(g_tTitle[nCnt].fPosXLeft, g_tTitle[nCnt].fPosYDown);
		g_aTITLEVertex[nCnt][3].tex = D3DXVECTOR2(g_tTitle[nCnt].fPosXRight, g_tTitle[nCnt].fPosYDown);
	}
}