//=============================================================================
//
// メイン処理 [main.h]
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"

#define DIRECTINPUT_VERSION (0x0800)	// 警告対処用
#include "dinput.h"

#include "input.h"
//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#if 1	// [ここを"0"にした場合、"構成プロパティ" -> "リンカ" -> "入力" -> "追加の依存ファイル"に対象ライブラリを設定する]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "winmm.lib")
#endif

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// ２Ｄポリゴン頂点フォーマット( 頂点座標[2D] / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// ３Ｄポリゴン頂点フォーマット( 頂点座標[3D] / 法線 / 反射光 / テクスチャ座標 )
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE| D3DFVF_TEX1)


#define SCREEN_WIDTH	(800)	// ウインドウの幅
#define SCREEN_HEIGHT	(600)	// ウインドウの高さ

#define	NUM_VERTEX		(4)		// 頂点数
#define	NUM_POLYGON		(2)		// ポリゴン数

#define PI				(3.141592)

#define DEBUG_MODE

#define USE_SOUND

#ifdef USE_SOUND

#include "xaudio2.h"	//vs2012以降だとエラーの可能性あり

#endif
// 上記２Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 vtx;	// 頂点座標
	float rhw;			// テクスチャのパースペクティブコレクト用
	D3DCOLOR diffuse;	// 反射光
	D3DXVECTOR2 tex;	// テクスチャ座標
} VERTEX_2D;

// 上記３Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct{
	D3DXVECTOR3 vtx;		//頂点座標
	D3DXVECTOR3 normal;		//法線ベクトル
	D3DCOLOR	diffuse;	//反射光
	D3DXVECTOR2 tex;		//テクスチャ座標
} VERTEX_3D;

typedef enum {
	STATE_TITLE,
	STATE_GAMEMAIN,
	STATE_ENDING,

	STATE_NUM_MAX
} GAME_STATE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);
void DrawFont(float, int, int);
void SetGameState(GAME_STATE);
#ifdef DEBUG_MODE
int GetCountFPS(void);
GAME_STATE GetGameState();
#endif

#endif