#include "Fade.h"
#include "model.h"
#include "sound.h"

//----- マクロ定義 -----
#define FADE_TEX_NAME		"data/TEXTURE/fade.png"	//背景ファイル名
#define	FADE_TEX_POS_X	(0)						//ポリゴンの表示位置
#define FADE_TEX_POS_Y	(0)						//ポリゴンの表示位置
#define FADE_TEX_SIZE_X	(800)					//ポリゴンのサイズ
#define FADE_TEX_SIZE_Y	(600)					//ポリゴンのサイズ

#define FADE_TEX_PATTERN_DIVIDE_X (1) 
#define FADE_TEX_PATTERN_DIVIDE_Y (1)
#define NUM_FADE_TEX_ANIME_PATTERN	 (FADE_TEX_PATTERN_DIVIDE_X * FADE_TEX_PATTERN_DIVIDE_Y)
#define FADE_TEX_PATTERN_SIZE_X   (1.0f / FADE_TEX_PATTERN_DIVIDE_X)
#define FADE_TEX_PATTERN_SIZE_Y   (1.0f / FADE_TEX_PATTERN_DIVIDE_Y)

#define FADE_VOLUME (15)


//----- プロトタイプ宣言 -----
void MakeVertexFade(LPDIRECT3DDEVICE9 pDevice);

//----- グローバル変数 -----
LPDIRECT3DTEXTURE9	g_pTextureFade = {NULL};	//テクスチャへのポインタ

VERTEX_2D			g_aFadeVertex[NUM_VERTEX];		//頂点情報格納ワーク

static tFade g_tFade;
static bool g_bFadeChange;

static int g_nPatternAnime;
static int g_nCounterAnime;	//アニメカウンタ(FPS)

static eFade g_eFade;

//int g_nTestPosX = BackGround_POS_X;

//===============================================================
//	ポリゴン初期化
//===============================================================
void InitFade(){
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点情報の作成
	MakeVertexFade(pDevice);

	//PlaySound(SOUND_LABEL_BGM001);

	g_nPatternAnime = 0;	////0から数えて

	g_bFadeChange = false;
	g_eFade = FADE_NONE;
	g_tFade.nFadeAlpha = 0;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, FADE_TEX_NAME, &g_pTextureFade);
	
	g_tFade.fTexPosX  = FADE_TEX_POS_X;
	g_tFade.fTexPosY  = FADE_TEX_POS_Y;
	g_tFade.nTexSizeX = FADE_TEX_SIZE_X;
	g_tFade.nTexSizeY = FADE_TEX_SIZE_Y;
	g_tFade.nFadeAlpha         = 0;
	g_tFade.nFadeVol		   = FADE_VOLUME;



}

//============================================================
//	終了処理
//============================================================
void UninitFade(void){
	if(g_pTextureFade != NULL){
		//テクスチャの開放
		g_pTextureFade->Release();
		g_pTextureFade = NULL;
	}
}

//============================================================
//	更新処理
//============================================================
void UpdateFade(void){
//テクスチャ座標計算
	g_nCounterAnime ++;

	// フェード開始
	if(g_bFadeChange){
		g_tFade.nFadeAlpha += g_tFade.nFadeVol;
		if(g_tFade.nFadeAlpha > 255){
			g_tFade.nFadeAlpha = 255;
			g_bFadeChange = false;
			g_eFade = FADE_NONE;
			SetPlayerCanMove(true);
		}
		if(g_tFade.nFadeAlpha < 0){
			g_tFade.nFadeAlpha = 0;
			g_bFadeChange = false;
			g_eFade = FADE_NONE;
			SetPlayerCanMove(true);
		}
	}

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	MakeVertexFade(pDevice);

}

//============================================================
//	描画処理
//============================================================
void DrawFade(void){
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureFade);
	//ポリゴン描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 
									NUM_POLYGON,
									&g_aFadeVertex[0],
									sizeof(VERTEX_2D));
}

//===========================================================
//	頂点の設定
//===========================================================
void MakeVertexFade(LPDIRECT3DDEVICE9 pDevice){

	//頂点座標	※時計回り注意
	g_aFadeVertex[0].vtx = D3DXVECTOR3(g_tFade.fTexPosX, g_tFade.fTexPosY, 0.0f);	//(X, Y, Z)
	g_aFadeVertex[1].vtx = D3DXVECTOR3(g_tFade.fTexPosX + g_tFade.nTexSizeX, g_tFade.fTexPosY, 0.0f);
	g_aFadeVertex[2].vtx = D3DXVECTOR3(g_tFade.fTexPosX, g_tFade.fTexPosY + g_tFade.nTexSizeY, 0.0f);
	g_aFadeVertex[3].vtx = D3DXVECTOR3(g_tFade.fTexPosX + g_tFade.nTexSizeX, g_tFade.fTexPosY + g_tFade.nTexSizeY, 0.0f);
				   
	//rhw		   
	g_aFadeVertex[0].rhw = 
	g_aFadeVertex[1].rhw = 
	g_aFadeVertex[2].rhw = 
	g_aFadeVertex[3].rhw = 1.0f;	//すべてに1.0fを入れる
				   
	//頂点カラー	  
	g_aFadeVertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, g_tFade.nFadeAlpha);
	g_aFadeVertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, g_tFade.nFadeAlpha);
	g_aFadeVertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, g_tFade.nFadeAlpha);
	g_aFadeVertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, g_tFade.nFadeAlpha);
				   
	//テクスチャ座標nCntの設定
	g_aFadeVertex[0].tex = D3DXVECTOR2(0,0);
	g_aFadeVertex[1].tex = D3DXVECTOR2(1,0);
	g_aFadeVertex[2].tex = D3DXVECTOR2(0,1);
	g_aFadeVertex[3].tex = D3DXVECTOR2(1,1);
}

// フェードアウトの準備
void StartFadeOut(){
	if(!g_bFadeChange){
		g_bFadeChange = true;
		g_eFade = FADE_OUT;
		g_tFade.nFadeAlpha = 0;
		g_tFade.nFadeVol = FADE_VOLUME;
		SetPlayerCanMove(false);
	}
}

// フェードインの準備
void StartFadeIn(){
	if(!g_bFadeChange){
		g_bFadeChange = true;
		g_eFade = FADE_IN;
		g_tFade.nFadeAlpha = 255;
		g_tFade.nFadeVol = -FADE_VOLUME;
		SetPlayerCanMove(false);
	}
}

// モードの取得(in or out)
eFade GetFade(){
	return g_eFade;
}