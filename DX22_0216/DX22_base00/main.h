//=============================================================================
//
// ���C������ [main.h]
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"

#define DIRECTINPUT_VERSION (0x0800)	// �x���Ώ��p
#include "dinput.h"

#include "input.h"
//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#if 1	// [������"0"�ɂ����ꍇ�A"�\���v���p�e�B" -> "�����J" -> "����" -> "�ǉ��̈ˑ��t�@�C��"�ɑΏۃ��C�u������ݒ肷��]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "winmm.lib")
#endif

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �Q�c�|���S�����_�t�H�[�}�b�g( ���_���W[2D] / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// �R�c�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / �@�� / ���ˌ� / �e�N�X�`�����W )
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE| D3DFVF_TEX1)


#define SCREEN_WIDTH	(800)	// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(600)	// �E�C���h�E�̍���

#define	NUM_VERTEX		(4)		// ���_��
#define	NUM_POLYGON		(2)		// �|���S����

#define PI				(3.141592)

#define DEBUG_MODE

#define USE_SOUND

#ifdef USE_SOUND

#include "xaudio2.h"	//vs2012�ȍ~���ƃG���[�̉\������

#endif
// ��L�Q�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 vtx;	// ���_���W
	float rhw;			// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR diffuse;	// ���ˌ�
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_2D;

// ��L�R�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct{
	D3DXVECTOR3 vtx;		//���_���W
	D3DXVECTOR3 normal;		//�@���x�N�g��
	D3DCOLOR	diffuse;	//���ˌ�
	D3DXVECTOR2 tex;		//�e�N�X�`�����W
} VERTEX_3D;

typedef enum {
	STATE_TITLE,
	STATE_GAMEMAIN,
	STATE_ENDING,

	STATE_NUM_MAX
} GAME_STATE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);
void DrawFont(float, int, int);
void SetGameState(GAME_STATE);
#ifdef DEBUG_MODE
int GetCountFPS(void);
GAME_STATE GetGameState();
#endif

#endif