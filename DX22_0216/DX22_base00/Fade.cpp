#include "Fade.h"
#include "model.h"
#include "sound.h"

//----- �}�N����` -----
#define FADE_TEX_NAME		"data/TEXTURE/fade.png"	//�w�i�t�@�C����
#define	FADE_TEX_POS_X	(0)						//�|���S���̕\���ʒu
#define FADE_TEX_POS_Y	(0)						//�|���S���̕\���ʒu
#define FADE_TEX_SIZE_X	(800)					//�|���S���̃T�C�Y
#define FADE_TEX_SIZE_Y	(600)					//�|���S���̃T�C�Y

#define FADE_TEX_PATTERN_DIVIDE_X (1) 
#define FADE_TEX_PATTERN_DIVIDE_Y (1)
#define NUM_FADE_TEX_ANIME_PATTERN	 (FADE_TEX_PATTERN_DIVIDE_X * FADE_TEX_PATTERN_DIVIDE_Y)
#define FADE_TEX_PATTERN_SIZE_X   (1.0f / FADE_TEX_PATTERN_DIVIDE_X)
#define FADE_TEX_PATTERN_SIZE_Y   (1.0f / FADE_TEX_PATTERN_DIVIDE_Y)

#define FADE_VOLUME (15)


//----- �v���g�^�C�v�錾 -----
void MakeVertexFade(LPDIRECT3DDEVICE9 pDevice);

//----- �O���[�o���ϐ� -----
LPDIRECT3DTEXTURE9	g_pTextureFade = {NULL};	//�e�N�X�`���ւ̃|�C���^

VERTEX_2D			g_aFadeVertex[NUM_VERTEX];		//���_���i�[���[�N

static tFade g_tFade;
static bool g_bFadeChange;

static int g_nPatternAnime;
static int g_nCounterAnime;	//�A�j���J�E���^(FPS)

static eFade g_eFade;

//int g_nTestPosX = BackGround_POS_X;

//===============================================================
//	�|���S��������
//===============================================================
void InitFade(){
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_���̍쐬
	MakeVertexFade(pDevice);

	//PlaySound(SOUND_LABEL_BGM001);

	g_nPatternAnime = 0;	////0���琔����

	g_bFadeChange = false;
	g_eFade = FADE_NONE;
	g_tFade.nFadeAlpha = 0;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, FADE_TEX_NAME, &g_pTextureFade);
	
	g_tFade.fTexPosX  = FADE_TEX_POS_X;
	g_tFade.fTexPosY  = FADE_TEX_POS_Y;
	g_tFade.nTexSizeX = FADE_TEX_SIZE_X;
	g_tFade.nTexSizeY = FADE_TEX_SIZE_Y;
	g_tFade.nFadeAlpha         = 0;
	g_tFade.nFadeVol		   = FADE_VOLUME;



}

//============================================================
//	�I������
//============================================================
void UninitFade(void){
	if(g_pTextureFade != NULL){
		//�e�N�X�`���̊J��
		g_pTextureFade->Release();
		g_pTextureFade = NULL;
	}
}

//============================================================
//	�X�V����
//============================================================
void UpdateFade(void){
//�e�N�X�`�����W�v�Z
	g_nCounterAnime ++;

	// �t�F�[�h�J�n
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
//	�`�揈��
//============================================================
void DrawFade(void){
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureFade);
	//�|���S���`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 
									NUM_POLYGON,
									&g_aFadeVertex[0],
									sizeof(VERTEX_2D));
}

//===========================================================
//	���_�̐ݒ�
//===========================================================
void MakeVertexFade(LPDIRECT3DDEVICE9 pDevice){

	//���_���W	�����v��蒍��
	g_aFadeVertex[0].vtx = D3DXVECTOR3(g_tFade.fTexPosX, g_tFade.fTexPosY, 0.0f);	//(X, Y, Z)
	g_aFadeVertex[1].vtx = D3DXVECTOR3(g_tFade.fTexPosX + g_tFade.nTexSizeX, g_tFade.fTexPosY, 0.0f);
	g_aFadeVertex[2].vtx = D3DXVECTOR3(g_tFade.fTexPosX, g_tFade.fTexPosY + g_tFade.nTexSizeY, 0.0f);
	g_aFadeVertex[3].vtx = D3DXVECTOR3(g_tFade.fTexPosX + g_tFade.nTexSizeX, g_tFade.fTexPosY + g_tFade.nTexSizeY, 0.0f);
				   
	//rhw		   
	g_aFadeVertex[0].rhw = 
	g_aFadeVertex[1].rhw = 
	g_aFadeVertex[2].rhw = 
	g_aFadeVertex[3].rhw = 1.0f;	//���ׂĂ�1.0f������
				   
	//���_�J���[	  
	g_aFadeVertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, g_tFade.nFadeAlpha);
	g_aFadeVertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, g_tFade.nFadeAlpha);
	g_aFadeVertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, g_tFade.nFadeAlpha);
	g_aFadeVertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, g_tFade.nFadeAlpha);
				   
	//�e�N�X�`�����WnCnt�̐ݒ�
	g_aFadeVertex[0].tex = D3DXVECTOR2(0,0);
	g_aFadeVertex[1].tex = D3DXVECTOR2(1,0);
	g_aFadeVertex[2].tex = D3DXVECTOR2(0,1);
	g_aFadeVertex[3].tex = D3DXVECTOR2(1,1);
}

// �t�F�[�h�A�E�g�̏���
void StartFadeOut(){
	if(!g_bFadeChange){
		g_bFadeChange = true;
		g_eFade = FADE_OUT;
		g_tFade.nFadeAlpha = 0;
		g_tFade.nFadeVol = FADE_VOLUME;
		SetPlayerCanMove(false);
	}
}

// �t�F�[�h�C���̏���
void StartFadeIn(){
	if(!g_bFadeChange){
		g_bFadeChange = true;
		g_eFade = FADE_IN;
		g_tFade.nFadeAlpha = 255;
		g_tFade.nFadeVol = -FADE_VOLUME;
		SetPlayerCanMove(false);
	}
}

// ���[�h�̎擾(in or out)
eFade GetFade(){
	return g_eFade;
}