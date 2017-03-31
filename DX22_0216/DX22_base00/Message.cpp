//===== インクルード宣言 =====
#include "Message.h"

//===== マクロ定義 =====
#define MESSAGE_BG_NAME		"data/TEXTURE/MesTest.png"	//背景ファイル名
#define	MESSAGE_BG_POS_X	(10)						//ポリゴンの表示位置
#define MESSAGE_BG_POS_Y	(410)						//ポリゴンの表示位置
#define MESSAGE_BG_SIZE_X	(780)					//ポリゴンのサイズ
#define MESSAGE_BG_SIZE_Y	(180)					//ポリゴンのサイズ

#define MESSAGE_BG_PATTERN_DIVIDE_X (1) 
#define MESSAGE_BG_PATTERN_DIVIDE_Y (1)
#define NUM_MESSAGE_BG_ANIME_PATTERN	 (MESSAGE_BG_PATTERN_DIVIDE_X * MESSAGE_BG_PATTERN_DIVIDE_Y)
#define MESSAGE_BG_PATTERN_SIZE_X   (1.0f / MESSAGE_BG_PATTERN_DIVIDE_X)
#define MESSAGE_BG_PATTERN_SIZE_Y   (1.0f / MESSAGE_BG_PATTERN_DIVIDE_Y)

#define MESSAGE_LIVE_TIME (60)

//===== 構造体宣言 =====

//===== 列挙対宣言 =====

//===== グローバル変数 =====
LPD3DXFONT g_pD3DXMesFont = NULL;	//フォント
int g_nMesFlameCnt;
int g_nPosX,g_nPosY;
bool g_bMesFlag;
char g_szStr[256];

LPDIRECT3DTEXTURE9	g_pMessageBackGround[1] = {NULL};	//テクスチャへのポインタ

VERTEX_2D			g_aMesBGVertex[4];		//頂点情報格納ワーク


//===== プロトタイプ宣言 =====
void MakeVertexMessage(LPDIRECT3DDEVICE9 pDevice);


//===================================================
void InitMessage(void){
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点情報の作成
	MakeVertexMessage(pDevice);

	D3DXCreateFont(pDevice,
					30, 0,		//フォントの高さと幅。幅は自動的に決まる
					 0, 0,
					FALSE,		//イタリックフォント(斜体)
					SHIFTJIS_CHARSET,
					OUT_DEFAULT_PRECIS,
					DEFAULT_QUALITY,
					DEFAULT_PITCH,
					"Terminal",
					&g_pD3DXMesFont);
		//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, MESSAGE_BG_NAME, &g_pMessageBackGround[0]);
}

void UninitMessage(void){
	if(g_pD3DXMesFont != NULL){
		g_pD3DXMesFont->Release();	//フォント開放
		g_pD3DXMesFont = NULL;		//安全化
	}
}

void UpdateMessage(void){
	if(g_bMesFlag)
	{
		g_nMesFlameCnt --;

		if(g_nMesFlameCnt <= 0)
			g_bMesFlag = false;
	}
}

void DrawMessage(void){
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	if(g_bMesFlag){
		//頂点フォーマット設定
		pDevice->SetFVF(FVF_VERTEX_2D);
	
		//テクスチャの設定
		pDevice->SetTexture(0, g_pMessageBackGround[0]);
		//ポリゴン描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 
								 NUM_POLYGON,
								 &g_aMesBGVertex[0],
								 sizeof(VERTEX_2D));
		RECT g_rect = {g_nPosX, g_nPosY, SCREEN_WIDTH, SCREEN_HEIGHT};
		g_pD3DXMesFont->DrawText(NULL,&g_szStr[0], -1, &g_rect, DT_LEFT, D3DCOLOR_XRGB(255,255,255));
	}
}


void SetMessageData(int nPosX,int nPosY,int nMesLiveTime,char szMes1[256] = 0){
	g_nPosX = nPosX;
	g_nPosY = nPosY;
	g_nMesFlameCnt = nMesLiveTime;
	g_bMesFlag = true;
	wsprintf(&g_szStr[0], "%s", &szMes1[0]);
}
void SetMessageData(int nPosX,int nPosY,int nMesLiveTime,char szMes1[256] = 0,char szMes2[256] = 0){
	g_nPosX = nPosX;
	g_nPosY = nPosY;
	g_nMesFlameCnt = nMesLiveTime;
	g_bMesFlag = true;
	wsprintf(&g_szStr[0], "%s", &szMes1[0]);
	wsprintf(&g_szStr[0], "%s\n%s", &szMes1[0],&szMes2[0]);
}
void SetMessageData(int nPosX,int nPosY,int nMesLiveTime,char szMes1[256] = 0,char szMes2[256] = 0, char szMes3[256] = 0){
	g_nPosX = nPosX;
	g_nPosY = nPosY;
	g_nMesFlameCnt = nMesLiveTime;
	g_bMesFlag = true;
	wsprintf(&g_szStr[0], "%s", &szMes1[0]);
	wsprintf(&g_szStr[0], "%s\n%s", &szMes1[0],&szMes2[0]);
	wsprintf(&g_szStr[0], "%s\n%s\n%s", &szMes1[0],&szMes2[0],&szMes3[0]);
}

//===========================================================
//	頂点の設定
//===========================================================
void MakeVertexMessage(LPDIRECT3DDEVICE9 pDevice){

	//頂点座標	※時計回り注意
	g_aMesBGVertex[0].vtx = D3DXVECTOR3(MESSAGE_BG_POS_X, MESSAGE_BG_POS_Y, 0.0f);	//(X, Y, Z)
	g_aMesBGVertex[1].vtx = D3DXVECTOR3(MESSAGE_BG_POS_X + MESSAGE_BG_SIZE_X, MESSAGE_BG_POS_Y, 0.0f);
	g_aMesBGVertex[2].vtx = D3DXVECTOR3(MESSAGE_BG_POS_X, MESSAGE_BG_POS_Y + MESSAGE_BG_SIZE_Y, 0.0f);
	g_aMesBGVertex[3].vtx = D3DXVECTOR3(MESSAGE_BG_POS_X + MESSAGE_BG_SIZE_X, MESSAGE_BG_POS_Y + MESSAGE_BG_SIZE_Y, 0.0f);

	//rhw
	g_aMesBGVertex[0].rhw = 
	g_aMesBGVertex[1].rhw = 
	g_aMesBGVertex[2].rhw = 
	g_aMesBGVertex[3].rhw = 1.0f;	//すべてに1.0fを入れる
	
	//頂点カラー
	g_aMesBGVertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_aMesBGVertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_aMesBGVertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_aMesBGVertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	g_aMesBGVertex[0].tex = D3DXVECTOR2(0, 0);
	g_aMesBGVertex[1].tex = D3DXVECTOR2(1, 0);
	g_aMesBGVertex[2].tex = D3DXVECTOR2(0, 1);
	g_aMesBGVertex[3].tex = D3DXVECTOR2(1, 1);
}