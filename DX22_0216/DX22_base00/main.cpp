//=============================================================================
//
// メイン処理 [main.cpp]
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
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"DX22_Winter"				// ウインドウのクラス名
#define WINDOW_NAME		"EscapeIsland3D"		// ウインドウのキャプション名

//*****************************************************************************
// プロトタイプ宣言
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
// グローバル変数:
//*****************************************************************************
LPDIRECT3D9			g_pD3D = NULL;			// Direct3Dオブジェクト
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// デバイスオブジェクト(描画に必要)
GAME_STATE			g_eGameState = STATE_TITLE;
#ifdef DEBUG_MODE
//LPD3DXFONT			g_pD3DXFont = NULL;		// フォントへのポインタ
int					g_nCountFPS;			// FPSカウンタ
#endif

//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

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
	
	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
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

	// 初期化処理(ウィンドウを作成してから行う)
	if(FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	//フレームカウント初期化
	timeBeginPeriod(1);				// 分解能を設定
	dwExecLastTime = 
	dwFPSLastTime = timeGetTime();
	dwCurrentTime =
	dwFrameCount = 0;

	// ウインドウの表示(初期化処理の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// メッセージループ
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();
#ifdef DEBUG_MODE
			if((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5秒ごとに実行
			{
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}
#endif

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// 更新処理
				Update();

				// 描画処理
				Draw();

				dwFrameCount++;
			}
		}
	}
	
	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 終了処理
	Uninit();

	timeEndPeriod(1);				// 分解能を戻す

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
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
// 初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
    D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
    if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ワークをゼロクリア
	d3dpp.BackBufferCount			= 1;						// バックバッファの数
	d3dpp.BackBufferWidth			= SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight			= SCREEN_HEIGHT;			// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat			= d3ddm.Format;				// バックバッファフォーマットはディスプレイモードに合わせて使う
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	// 映像信号に同期してフリップする
	d3dpp.Windowed					= bWindow;					// ウィンドウモード
	d3dpp.EnableAutoDepthStencil	= TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;				// デプスバッファとして16bitを使う

	if(bWindow)
	{// ウィンドウモード
		d3dpp.FullScreen_RefreshRateInHz = 0;								// リフレッシュレート
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;	// インターバル
	}
	else
	{// フルスクリーンモード
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// リフレッシュレート
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル
	}

	// デバイスオブジェクトの生成
	// [デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
									D3DDEVTYPE_HAL, 
									hWnd, 
									D3DCREATE_HARDWARE_VERTEXPROCESSING, 
									&d3dpp, &g_pD3DDevice)))
	{
		// 上記の設定が失敗したら
		// [デバイス作成制御]<描画>をハードウェアで行い、<頂点処理>はCPUで行なう
		if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
										D3DDEVTYPE_HAL, 
										hWnd, 
										D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
										&d3dpp, &g_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// [デバイス作成制御]<描画>と<頂点処理>をCPUで行なう
			if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
											D3DDEVTYPE_REF,
											hWnd, 
											D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
											&d3dpp, &g_pD3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	// プロジェクショントランスフォーム（射影変換）
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(45), (float)SCREEN_WIDTH/SCREEN_HEIGHT, 1.0f, 3000.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	// ビュートランスフォーム（視点座標変換）
	/*D3DXVECTOR3 vecEyePt(   -80.0f, 40.0f, -80.0f);	// カメラ（視点）位置
	D3DXVECTOR3 vecLookatPt(30.0f, 0.0f,  0.0f);	// 注視位置
	D3DXVECTOR3 vecUpVec(   0.0f, 1.0f,  0.0f);	// 上方位置
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH( &matView, &vecEyePt, &vecLookatPt, &vecUpVec );
	g_pD3DDevice->SetTransform( D3DTS_VIEW, &matView );*/

	// レンダーステートパラメータの設定
    g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面をカリング
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

	// サンプラーステートパラメータの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

	// テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理を設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数

#ifdef DEBUG_MODE
	// 情報表示用フォントを設定
//	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
//					OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pD3DXFont);
	Debug.InitDebug();
#endif

	// 入力関連の初期化
	InitInput(hInstance, hWnd);

	InitSound(hWnd);
	PlaySound(SOUND_LABEL_BGM_WAVE);

	InitTitle();
	InitEnding();

	//フェード
	InitFade();
	// カメラ関連の初期化
	InitCamera();
	// ライト関連の初期化
	InitLight(g_pD3DDevice);

	// 影
	InitShadow(g_pD3DDevice);
	// モデル
	InitModel(g_pD3DDevice);
	// 空
	InitSky(g_pD3DDevice);
	// ビルボード
	InitBillboard(g_pD3DDevice);
	// オブジェクト
	InitObject();
	// アイテム
	InitItem(g_pD3DDevice);
	// 3Dのオブジェクト
	Init3DObject(g_pD3DDevice);
	// 地面の初期化処理
	InitField(g_pD3DDevice, 4, 4, 125.0f, 125.0f);
	// 爆発(使わないつもりだった)
	InitExplosion(g_pD3DDevice);
	// エフェクト(これも)
	InitEffect(g_pD3DDevice);
	// メッセージ
	InitMessage();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
#ifdef DEBUG_MODE
	Debug.UninitDebug();
#endif
	if(g_pD3DDevice != NULL)
	{// デバイスオブジェクトの開放
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if(g_pD3D != NULL)
	{// Direct3Dオブジェクトの開放
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	//入力関連の終了処理
	UninitInput();
	UninitFade();

	// 音
	UninitSound();

	// 終了処理
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
// 更新処理
//=============================================================================
void Update(void)
{
#ifdef DEBUG_MODE
	Debug.UpdateDebug();
#endif
	// 入力関連の更新
	UpdateInput();
	UpdateFade();

	switch (g_eGameState) {
	case STATE_TITLE:
		UpdateTitle();

		break;
	case STATE_GAMEMAIN:
		// ライト
		UpdateLight(g_pD3DDevice);

		// カメラ
		UpdateCamera();
		SetCamera(g_pD3DDevice);
		// ビルボード
		UpdateBillboard();

		// 地面の更新処理
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
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファ＆Ｚバッファのクリア
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(128, 128, 255, 0), 1.0f, 0);

	// 描画の開始
	if(SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (g_eGameState) {
		case STATE_TITLE:
			DrawTitle();

			break;
		case STATE_GAMEMAIN:
			SetCamera(g_pD3DDevice);
			// 地面の描画処理
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
		// FPS表示
		Debug.DrawDebug();
#endif

		// 描画の終了
		g_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

#ifdef DEBUG_MODE
//=============================================================================
// FPS表示
//=============================================================================
//void DrawFPS(void)
//{
//	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
//	char str[256];
//
//	wsprintf(str, "FPS:%d\n", g_nCountFPS);
//
//	// テキスト描画
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
	
		// 影
		InitShadow(g_pD3DDevice);
		// モデル
		InitModel(g_pD3DDevice);
		// 空
		InitSky(g_pD3DDevice);
		// ビルボード
		InitBillboard(g_pD3DDevice);
		// オブジェクト
		InitObject();
		// アイテム
		InitItem(g_pD3DDevice);
		// 3Dのオブジェクト
		Init3DObject(g_pD3DDevice);
		// 地面の初期化処理
		InitField(g_pD3DDevice, 4, 4, 125.0f, 125.0f);
		// 爆発(使わないつもりだった)
		InitExplosion(g_pD3DDevice);
		// メッセージ
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
//	// テキスト描画
//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
//}