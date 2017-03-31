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

//----- �}�N����` -----
#define BackGround_GAMEOVER_NAME		"data/TEXTURE/Ending.jpg"	//�w�i�t�@�C����
#define	BackGround_GAMEOVER_POS_X	(0)						//�|���S���̕\���ʒu
#define BackGround_GAMEOVER_POS_Y	(0)						//�|���S���̕\���ʒu
#define BackGround_GAMEOVER_SIZE_X	(800)					//�|���S���̃T�C�Y
#define BackGround_GAMEOVER_SIZE_Y	(600)					//�|���S���̃T�C�Y

#define GAMEOVER_PATTERN_DIVIDE_X (1) 
#define GAMEOVER_PATTERN_DIVIDE_Y (1)
#define NUM_GAMEOVER_ANIME_PATTERN	 (GAMEOVER_PATTERN_DIVIDE_X * GAMEOVER_PATTERN_DIVIDE_Y)
#define GAMEOVER_PATTERN_SIZE_X   (1.0f / GAMEOVER_PATTERN_DIVIDE_X)
#define GAMEOVER_PATTERN_SIZE_Y   (1.0f / GAMEOVER_PATTERN_DIVIDE_Y)

#define ROGO_GAMEOVER_NAME		"data/TEXTURE/EndRogo.png"	//�w�i�t�@�C����
#define	ROGO_GAMEOVER_POS_X	(30)						//�|���S���̕\���ʒu
#define ROGO_GAMEOVER_POS_Y	(150)						//�|���S���̕\���ʒu
#define ROGO_GAMEOVER_SIZE_X	(730)					//�|���S���̃T�C�Y
#define ROGO_GAMEOVER_SIZE_Y	(56)					//�|���S���̃T�C�Y

#define PRESSBUTTOM_GAMEOVER_NAME		"data/TEXTURE/EndButtom.png"	//�w�i�t�@�C����
#define	PRESSBUTTOM_GAMEOVER_POS_X	(238)						//�|���S���̕\���ʒu
#define PRESSBUTTOM_GAMEOVER_POS_Y	(350)						//�|���S���̕\���ʒu
#define PRESSBUTTOM_GAMEOVER_SIZE_X	(325)					//�|���S���̃T�C�Y
#define PRESSBUTTOM_GAMEOVER_SIZE_Y	(50)					//�|���S���̃T�C�Y


#define INTERVAL_GAMEOVER_CHANGE_PATTERN (20)
#define FADE_VOLUME						 (7)


//----- �v���g�^�C�v�錾 -----
void MakeVertexGameOver(LPDIRECT3DDEVICE9 pDevice);
void MakeVertexEnding(LPDIRECT3DDEVICE9 pDevice);

//----- �O���[�o���ϐ� -----
LPDIRECT3DTEXTURE9	g_pTextureGameOver[3] ={ NULL };	//�e�N�X�`���ւ̃|�C���^

VERTEX_2D			g_aGAMEOVERVertex[3][NUM_VERTEX];		//���_���i�[���[�N

static float g_fPosXLeft, g_fPosXRight;	//�摜��X���W
static float g_fPosYUp, g_fPosYDown;		//�摜��Y���W
static tEnding g_tEnding[2];

static int g_nFrameCounter;	//�t���[���J�E���^(FPS)
static bool bChangeEnding = false;

//int g_nTestPosX = BackGround_POS_X;

//===============================================================
//	�|���S��������
//===============================================================
void InitEnding() {
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	bChangeEnding = false;
	g_nFrameCounter = 0;
	//���_���̍쐬
	MakeVertexGameOver(pDevice);

	//�e�N�X�`���̓ǂݍ���
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
//	�I������
//============================================================
void UninitEnding(void) {
	for (int nCnt = 0; nCnt < 3; nCnt ++) {
		if (g_pTextureGameOver[nCnt] != NULL) {
			//�e�N�X�`���̊J��
			g_pTextureGameOver[nCnt]->Release();
			g_pTextureGameOver[nCnt] = NULL;
		}
	}
}

//============================================================
//	�X�V����
//============================================================
void UpdateEnding(void) {
	//�e�N�X�`�����W�v�Z
	tPlayerData * tPlayerData = GetPlayerData();
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (tPlayerData->bPlayerMove) {
		g_nFrameCounter ++;

		if (g_nFrameCounter < 2)
			StartFadeIn();
		else if (g_nFrameCounter <= 2)
			SetMessageData(50, 420, 200, "���l�����疳���E�o���邱�Ƃ��ł����B", "���Ƃ͂��̂܂܃C�J�_�𑆂�������Ό��̓��ɋA���͂���");
		else if (g_nFrameCounter == 202)
			SetMessageData(50, 420, 150, "�����M���Ėl�̓C�J�_�𑆂�������...");
		else if (g_nFrameCounter > 420) {
			//SetMessageData(50,420,1,"�����M���Ėl�̓C�J�_�𑆂�������...");
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
//	�`�揈��
//============================================================
void DrawEnding(void) {
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < 3; nCnt ++) {
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureGameOver[nCnt]);
		//�|���S���`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,
			NUM_POLYGON,
			&g_aGAMEOVERVertex[nCnt][0],
			sizeof(VERTEX_2D));
	}
}

//===========================================================
//	���_�̐ݒ�
//===========================================================
void MakeVertexGameOver(LPDIRECT3DDEVICE9 pDevice) {

	//���_���W	�����v��蒍��
	g_aGAMEOVERVertex[0][0].vtx = D3DXVECTOR3(BackGround_GAMEOVER_POS_X, BackGround_GAMEOVER_POS_Y, 0.0f);	//(X, Y, Z)
	g_aGAMEOVERVertex[0][1].vtx = D3DXVECTOR3(BackGround_GAMEOVER_POS_X + BackGround_GAMEOVER_SIZE_X, BackGround_GAMEOVER_POS_Y, 0.0f);
	g_aGAMEOVERVertex[0][2].vtx = D3DXVECTOR3(BackGround_GAMEOVER_POS_X, BackGround_GAMEOVER_POS_Y + BackGround_GAMEOVER_SIZE_Y, 0.0f);
	g_aGAMEOVERVertex[0][3].vtx = D3DXVECTOR3(BackGround_GAMEOVER_POS_X + BackGround_GAMEOVER_SIZE_X, BackGround_GAMEOVER_POS_Y + BackGround_GAMEOVER_SIZE_Y, 0.0f);

	//rhw
	g_aGAMEOVERVertex[0][0].rhw =
		g_aGAMEOVERVertex[0][1].rhw =
		g_aGAMEOVERVertex[0][2].rhw =
		g_aGAMEOVERVertex[0][3].rhw = 1.0f;	//���ׂĂ�1.0f������

											//���_�J���[
	g_aGAMEOVERVertex[0][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_aGAMEOVERVertex[0][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_aGAMEOVERVertex[0][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_aGAMEOVERVertex[0][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	g_aGAMEOVERVertex[0][0].tex = D3DXVECTOR2(g_fPosXLeft, g_fPosYUp);
	g_aGAMEOVERVertex[0][1].tex = D3DXVECTOR2(g_fPosXRight, g_fPosYUp);
	g_aGAMEOVERVertex[0][2].tex = D3DXVECTOR2(g_fPosXLeft, g_fPosYDown);
	g_aGAMEOVERVertex[0][3].tex = D3DXVECTOR2(g_fPosXRight, g_fPosYDown);
}

//===========================================================
//	���_�̐ݒ�
//===========================================================
void MakeVertexEnding(LPDIRECT3DDEVICE9 pDevice) {

	for (int nCnt = 1; nCnt < 3; nCnt++) {
		//���_���W	�����v��蒍��
		g_aGAMEOVERVertex[nCnt][0].vtx = D3DXVECTOR3(g_tEnding[nCnt - 1].fTexPosX, g_tEnding[nCnt - 1].fTexPosY, 0.0f);	//(X, Y, Z)
		g_aGAMEOVERVertex[nCnt][1].vtx = D3DXVECTOR3(g_tEnding[nCnt - 1].fTexPosX + g_tEnding[nCnt - 1].nTexSizeX, g_tEnding[nCnt - 1].fTexPosY, 0.0f);
		g_aGAMEOVERVertex[nCnt][2].vtx = D3DXVECTOR3(g_tEnding[nCnt - 1].fTexPosX, g_tEnding[nCnt - 1].fTexPosY + g_tEnding[nCnt - 1].nTexSizeY, 0.0f);
		g_aGAMEOVERVertex[nCnt][3].vtx = D3DXVECTOR3(g_tEnding[nCnt - 1].fTexPosX + g_tEnding[nCnt - 1].nTexSizeX, g_tEnding[nCnt - 1].fTexPosY + g_tEnding[nCnt - 1].nTexSizeY, 0.0f);

		//rhw		   
		g_aGAMEOVERVertex[nCnt][0].rhw =
			g_aGAMEOVERVertex[nCnt][1].rhw =
			g_aGAMEOVERVertex[nCnt][2].rhw =
			g_aGAMEOVERVertex[nCnt][3].rhw = 1.0f;	//���ׂĂ�1.0f������

													//���_�J���[	  
		g_aGAMEOVERVertex[nCnt][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, g_tEnding[nCnt - 1].nFadeAlpha);
		g_aGAMEOVERVertex[nCnt][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, g_tEnding[nCnt - 1].nFadeAlpha);
		g_aGAMEOVERVertex[nCnt][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, g_tEnding[nCnt - 1].nFadeAlpha);
		g_aGAMEOVERVertex[nCnt][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, g_tEnding[nCnt - 1].nFadeAlpha);

		//�e�N�X�`�����W�̐ݒ�
		g_aGAMEOVERVertex[nCnt][0].tex = D3DXVECTOR2(g_tEnding[nCnt - 1].fPosXLeft, g_tEnding[nCnt - 1].fPosYUp);
		g_aGAMEOVERVertex[nCnt][1].tex = D3DXVECTOR2(g_tEnding[nCnt - 1].fPosXRight, g_tEnding[nCnt - 1].fPosYUp);
		g_aGAMEOVERVertex[nCnt][2].tex = D3DXVECTOR2(g_tEnding[nCnt - 1].fPosXLeft, g_tEnding[nCnt - 1].fPosYDown);
		g_aGAMEOVERVertex[nCnt][3].tex = D3DXVECTOR2(g_tEnding[nCnt - 1].fPosXRight, g_tEnding[nCnt - 1].fPosYDown);
	}
}