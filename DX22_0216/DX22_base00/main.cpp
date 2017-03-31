//=============================================================================
//
// ���C������ [main.cpp]
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "field.h"
#include "model.h"
#include "light.h"
#include "camera.h"
#include "shadow.h"
#include "billboard.h"
#include "explosion.h"
#include "effect.h"
#include "Fade.h"
#include "Title.h"
#include "Ending.h"
#include "Object.h"
#include "Sky.h"
#include "Item.h"
#include "Message.h"
#include "3DObject.h"
#include "sound.h"

#include "Debug.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		"DX22_Winter"				// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"EscapeIsland3D"		// �E�C���h�E�̃L���v�V������

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
#ifdef DEBUG_MODE
CDebug Debug;
#endif

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
LPDIRECT3D9			g_pD3D = NULL;			// Direct3D�I�u�W�F�N�g
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// �f�o�C�X�I�u�W�F�N�g(�`��ɕK�v)
GAME_STATE			g_eGameState = STATE_TITLE;
#ifdef DEBUG_MODE
//LPD3DXFONT			g_pD3DXFont = NULL;		// �t�H���g�ւ̃|�C���^
int					g_nCountFPS;			// FPS�J�E���^
#endif

//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	HWND hWnd;
	MSG msg;
	
	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
	hWnd = CreateWindowEx(0,
						CLASS_NAME,
						WINDOW_NAME,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,
						SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
						NULL,
						NULL,
						hInstance,
						NULL);

	// ����������(�E�B���h�E���쐬���Ă���s��)
	if(FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	//�t���[���J�E���g������
	timeBeginPeriod(1);				// ����\��ݒ�
	dwExecLastTime = 
	dwFPSLastTime = timeGetTime();
	dwCurrentTime =
	dwFrameCount = 0;

	// �E�C���h�E�̕\��(�����������̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// ���b�Z�[�W���[�v
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();
#ifdef DEBUG_MODE
			if((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5�b���ƂɎ��s
			{
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}
#endif

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// �X�V����
				Update();

				// �`�揈��
				Draw();

				dwFrameCount++;
			}
		}
	}
	
	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �I������
	Uninit();

	timeEndPeriod(1);				// ����\��߂�

	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
    D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
    if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ���[�N���[���N���A
	d3dpp.BackBufferCount			= 1;						// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth			= SCREEN_WIDTH;				// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight			= SCREEN_HEIGHT;			// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat			= d3ddm.Format;				// �o�b�N�o�b�t�@�t�H�[�}�b�g�̓f�B�X�v���C���[�h�ɍ��킹�Ďg��
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	// �f���M���ɓ������ăt���b�v����
	d3dpp.Windowed					= bWindow;					// �E�B���h�E���[�h
	d3dpp.EnableAutoDepthStencil	= TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;				// �f�v�X�o�b�t�@�Ƃ���16bit���g��

	if(bWindow)
	{// �E�B���h�E���[�h
		d3dpp.FullScreen_RefreshRateInHz = 0;								// ���t���b�V�����[�g
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;	// �C���^�[�o��
	}
	else
	{// �t���X�N���[�����[�h
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// ���t���b�V�����[�g
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��
	}

	// �f�o�C�X�I�u�W�F�N�g�̐���
	// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
									D3DDEVTYPE_HAL, 
									hWnd, 
									D3DCREATE_HARDWARE_VERTEXPROCESSING, 
									&d3dpp, &g_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// [�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs�Ȃ�
		if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
										D3DDEVTYPE_HAL, 
										hWnd, 
										D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
										&d3dpp, &g_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// [�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs�Ȃ�
			if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
											D3DDEVTYPE_REF,
											hWnd, 
											D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
											&d3dpp, &g_pD3DDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}

	// �v���W�F�N�V�����g�����X�t�H�[���i�ˉe�ϊ��j
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(45), (float)SCREEN_WIDTH/SCREEN_HEIGHT, 1.0f, 3000.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	// �r���[�g�����X�t�H�[���i���_���W�ϊ��j
	/*D3DXVECTOR3 vecEyePt(   -80.0f, 40.0f, -80.0f);	// �J�����i���_�j�ʒu
	D3DXVECTOR3 vecLookatPt(30.0f, 0.0f,  0.0f);	// �����ʒu
	D3DXVECTOR3 vecUpVec(   0.0f, 1.0f,  0.0f);	// ����ʒu
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH( &matView, &vecEyePt, &vecLookatPt, &vecUpVec );
	g_pD3DDevice->SetTransform( D3DTS_VIEW, &matView );*/

	// �����_�[�X�e�[�g�p�����[�^�̐ݒ�
    g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

	// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O������ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����

#ifdef DEBUG_MODE
	// ���\���p�t�H���g��ݒ�
//	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
//					OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pD3DXFont);
	Debug.InitDebug();
#endif

	// ���͊֘A�̏�����
	InitInput(hInstance, hWnd);

	InitSound(hWnd);
	PlaySound(SOUND_LABEL_BGM_WAVE);

	InitTitle();
	InitEnding();

	//�t�F�[�h
	InitFade();
	// �J�����֘A�̏�����
	InitCamera();
	// ���C�g�֘A�̏�����
	InitLight(g_pD3DDevice);

	// �e
	InitShadow(g_pD3DDevice);
	// ���f��
	InitModel(g_pD3DDevice);
	// ��
	InitSky(g_pD3DDevice);
	// �r���{�[�h
	InitBillboard(g_pD3DDevice);
	// �I�u�W�F�N�g
	InitObject();
	// �A�C�e��
	InitItem(g_pD3DDevice);
	// 3D�̃I�u�W�F�N�g
	Init3DObject(g_pD3DDevice);
	// �n�ʂ̏���������
	InitField(g_pD3DDevice, 4, 4, 125.0f, 125.0f);
	// ����(�g��Ȃ����肾����)
	InitExplosion(g_pD3DDevice);
	// �G�t�F�N�g(�����)
	InitEffect(g_pD3DDevice);
	// ���b�Z�[�W
	InitMessage();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
#ifdef DEBUG_MODE
	Debug.UninitDebug();
#endif
	if(g_pD3DDevice != NULL)
	{// �f�o�C�X�I�u�W�F�N�g�̊J��
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if(g_pD3D != NULL)
	{// Direct3D�I�u�W�F�N�g�̊J��
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	//���͊֘A�̏I������
	UninitInput();
	UninitFade();

	// ��
	UninitSound();

	// �I������
	UninitTitle();
	UninitEnding();
	UninitField();
	UninitModel();
	UninitShadow();
	UninitBillboard();
	UninitExplosion();
	UninitEffect();
	UninitObject();
	Uninit3DObject();
	UninitSky();
	UninitItem();
	UninitMessage();

	UninitLight();
	UninitCamera();
}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
#ifdef DEBUG_MODE
	Debug.UpdateDebug();
#endif
	// ���͊֘A�̍X�V
	UpdateInput();
	UpdateFade();

	switch (g_eGameState) {
	case STATE_TITLE:
		UpdateTitle();

		break;
	case STATE_GAMEMAIN:
		// ���C�g
		UpdateLight(g_pD3DDevice);

		// �J����
		UpdateCamera();
		SetCamera(g_pD3DDevice);
		// �r���{�[�h
		UpdateBillboard();

		// �n�ʂ̍X�V����
		UpdateField();
		UpdateModel();
		UpdateShadow();
		UpdateExplosion();
		UpdateEffect();
		UpdateObject(); 
		Update3DObject();
		UpdateItem();
		UpdateSky();
		UpdateMessage();

		break;
	case STATE_ENDING:
		UpdateEnding();
		UpdateMessage();

		break;
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(128, 128, 255, 0), 1.0f, 0);

	// �`��̊J�n
	if(SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (g_eGameState) {
		case STATE_TITLE:
			DrawTitle();

			break;
		case STATE_GAMEMAIN:
			SetCamera(g_pD3DDevice);
			// �n�ʂ̕`�揈��
			DrawSky(g_pD3DDevice);
			DrawField(g_pD3DDevice);
			DrawShadow(g_pD3DDevice);
			DrawModel(g_pD3DDevice);
			Draw3DObject(g_pD3DDevice);
			DrawExplosion(g_pD3DDevice);
			//DrawEffect(g_pD3DDevice);
			DrawObject();
			DrawBillboard(g_pD3DDevice);
			DrawItem(g_pD3DDevice);
			DrawMessage();
			break;
		case STATE_ENDING:
			DrawEnding();
			DrawMessage();

			break;

		}
		DrawFade();
#ifdef DEBUG_MODE
		// FPS�\��
		Debug.DrawDebug();
#endif

		// �`��̏I��
		g_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

#ifdef DEBUG_MODE
//=============================================================================
// FPS�\��
//=============================================================================
//void DrawFPS(void)
//{
//	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
//	char str[256];
//
//	wsprintf(str, "FPS:%d\n", g_nCountFPS);
//
//	// �e�L�X�g�`��
//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
//}

int GetCountFPS(){
	return g_nCountFPS;
}
#endif

LPDIRECT3DDEVICE9 GetDevice(){
	return g_pD3DDevice;
}

void SetGameState(GAME_STATE eGameState) {
	g_eGameState = eGameState;

	if (eGameState == STATE_TITLE) {
		StopSound();
		PlaySound(SOUND_LABEL_BGM_WAVE);
		InitFade();
		InitTitle();
	}

	if (eGameState == STATE_GAMEMAIN) {
		//StopSound();
		InitFade();
	
		// �e
		InitShadow(g_pD3DDevice);
		// ���f��
		InitModel(g_pD3DDevice);
		// ��
		InitSky(g_pD3DDevice);
		// �r���{�[�h
		InitBillboard(g_pD3DDevice);
		// �I�u�W�F�N�g
		InitObject();
		// �A�C�e��
		InitItem(g_pD3DDevice);
		// 3D�̃I�u�W�F�N�g
		Init3DObject(g_pD3DDevice);
		// �n�ʂ̏���������
		InitField(g_pD3DDevice, 4, 4, 125.0f, 125.0f);
		// ����(�g��Ȃ����肾����)
		InitExplosion(g_pD3DDevice);
		// ���b�Z�[�W
		InitMessage();
	}

	if (eGameState == STATE_ENDING) {
		StopSound();
		PlaySound(SOUND_LABEL_BGM_WAVE);
		//InitFade();
		InitEnding();
	}
}

#ifdef DEBUG_MODE
GAME_STATE GetGameState() {
	return g_eGameState;
}
#endif

//void DrawFont(float Font, int posX, int posY)
//{
//	RECT rect = {posX, posY, SCREEN_WIDTH, SCREEN_HEIGHT};
//	char str[256];
//
//	wsprintf(str, "%d\n", Font);
//
//	// �e�L�X�g�`��
//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
//}