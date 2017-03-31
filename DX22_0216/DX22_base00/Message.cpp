//===== �C���N���[�h�錾 =====
#include "Message.h"

//===== �}�N����` =====
#define MESSAGE_BG_NAME		"data/TEXTURE/MesTest.png"	//�w�i�t�@�C����
#define	MESSAGE_BG_POS_X	(10)						//�|���S���̕\���ʒu
#define MESSAGE_BG_POS_Y	(410)						//�|���S���̕\���ʒu
#define MESSAGE_BG_SIZE_X	(780)					//�|���S���̃T�C�Y
#define MESSAGE_BG_SIZE_Y	(180)					//�|���S���̃T�C�Y

#define MESSAGE_BG_PATTERN_DIVIDE_X (1) 
#define MESSAGE_BG_PATTERN_DIVIDE_Y (1)
#define NUM_MESSAGE_BG_ANIME_PATTERN	 (MESSAGE_BG_PATTERN_DIVIDE_X * MESSAGE_BG_PATTERN_DIVIDE_Y)
#define MESSAGE_BG_PATTERN_SIZE_X   (1.0f / MESSAGE_BG_PATTERN_DIVIDE_X)
#define MESSAGE_BG_PATTERN_SIZE_Y   (1.0f / MESSAGE_BG_PATTERN_DIVIDE_Y)

#define MESSAGE_LIVE_TIME (60)

//===== �\���̐錾 =====

//===== �񋓑ΐ錾 =====

//===== �O���[�o���ϐ� =====
LPD3DXFONT g_pD3DXMesFont = NULL;	//�t�H���g
int g_nMesFlameCnt;
int g_nPosX,g_nPosY;
bool g_bMesFlag;
char g_szStr[256];

LPDIRECT3DTEXTURE9	g_pMessageBackGround[1] = {NULL};	//�e�N�X�`���ւ̃|�C���^

VERTEX_2D			g_aMesBGVertex[4];		//���_���i�[���[�N


//===== �v���g�^�C�v�錾 =====
void MakeVertexMessage(LPDIRECT3DDEVICE9 pDevice);


//===================================================
void InitMessage(void){
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_���̍쐬
	MakeVertexMessage(pDevice);

	D3DXCreateFont(pDevice,
					30, 0,		//�t�H���g�̍����ƕ��B���͎����I�Ɍ��܂�
					 0, 0,
					FALSE,		//�C�^���b�N�t�H���g(�Α�)
					SHIFTJIS_CHARSET,
					OUT_DEFAULT_PRECIS,
					DEFAULT_QUALITY,
					DEFAULT_PITCH,
					"Terminal",
					&g_pD3DXMesFont);
		//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MESSAGE_BG_NAME, &g_pMessageBackGround[0]);
}

void UninitMessage(void){
	if(g_pD3DXMesFont != NULL){
		g_pD3DXMesFont->Release();	//�t�H���g�J��
		g_pD3DXMesFont = NULL;		//���S��
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
		//���_�t�H�[�}�b�g�ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);
	
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pMessageBackGround[0]);
		//�|���S���`��
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
//	���_�̐ݒ�
//===========================================================
void MakeVertexMessage(LPDIRECT3DDEVICE9 pDevice){

	//���_���W	�����v��蒍��
	g_aMesBGVertex[0].vtx = D3DXVECTOR3(MESSAGE_BG_POS_X, MESSAGE_BG_POS_Y, 0.0f);	//(X, Y, Z)
	g_aMesBGVertex[1].vtx = D3DXVECTOR3(MESSAGE_BG_POS_X + MESSAGE_BG_SIZE_X, MESSAGE_BG_POS_Y, 0.0f);
	g_aMesBGVertex[2].vtx = D3DXVECTOR3(MESSAGE_BG_POS_X, MESSAGE_BG_POS_Y + MESSAGE_BG_SIZE_Y, 0.0f);
	g_aMesBGVertex[3].vtx = D3DXVECTOR3(MESSAGE_BG_POS_X + MESSAGE_BG_SIZE_X, MESSAGE_BG_POS_Y + MESSAGE_BG_SIZE_Y, 0.0f);

	//rhw
	g_aMesBGVertex[0].rhw = 
	g_aMesBGVertex[1].rhw = 
	g_aMesBGVertex[2].rhw = 
	g_aMesBGVertex[3].rhw = 1.0f;	//���ׂĂ�1.0f������
	
	//���_�J���[
	g_aMesBGVertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_aMesBGVertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_aMesBGVertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_aMesBGVertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	g_aMesBGVertex[0].tex = D3DXVECTOR2(0, 0);
	g_aMesBGVertex[1].tex = D3DXVECTOR2(1, 0);
	g_aMesBGVertex[2].tex = D3DXVECTOR2(0, 1);
	g_aMesBGVertex[3].tex = D3DXVECTOR2(1, 1);
}