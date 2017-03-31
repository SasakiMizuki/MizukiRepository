//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"
//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM_BIRD = 0,		// 鳥
	SOUND_LABEL_BGM_WAVE,			// 波
	SOUND_LABEL_BGM002,			// BGM2
	SOUND_LABEL_SE_DECIDE,		// 決定音
	SOUND_LABEL_SE_CANCEL,		// キャンセル音
	SOUND_LABEL_SE_SELECT,		// 選択音
	SOUND_LABEL_SE_SHOT,		// 弾発射音
	SOUND_LABEL_SE_LASER,		// レーザー発射音
	SOUND_LABEL_SE_LOCKON,		// ロックオン音
	SOUND_LABEL_SE_HIT,			// ヒット音
	SOUND_LABEL_SE_GUARD,		// ガード音
	SOUND_LABEL_SE_EXPLOSION,	// 爆発音
	SOUND_LABEL_SE_JUMP,		// ジャンプ音
	
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
