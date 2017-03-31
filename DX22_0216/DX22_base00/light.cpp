//=============================================================================
//
// ライト処理 [light.cpp]
//
//=============================================================================
#include "light.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
D3DLIGHT9 g_light;
D3DLIGHT9 g_light2;

float vol = 0.0f;
float Redvol = 0.003f;
float Greenvol = 0.002f;
float Bluevol = 0.005f;

//=============================================================================
// ライトの初期化処理
//=============================================================================
HRESULT InitLight(LPDIRECT3DDEVICE9 pDevice)
{
	/*// ライトを有効にする
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	// アンビエントライト（環境光）を設定する
	g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
	// スペキュラ（鏡面反射）を有効にする
	g_pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

	// ライトをあてる（白色で鏡面反射ありに設定）
	D3DXVECTOR3 vecDirection(0, -1, -1);			// 光の向きを決める
	D3DLIGHT9 light = {D3DLIGHT_DIRECTIONAL};	// ライトオブジェクト
	light.Diffuse.r  = 1.0f;
	light.Diffuse.g  = 1.0f;
	light.Diffuse.b  = 1.0f;
	light.Specular.r = 0.0f;
	light.Specular.g = 0.0f;
	light.Specular.b = 0.0f;
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDirection);
	g_pD3DDevice->SetLight(0, &light);
	g_pD3DDevice->LightEnable(0, TRUE);			// ライト０を有効*/
	
	// ライトの情報クリア
	ZeroMemory(&g_light, sizeof(D3DLIGHT9));
	// ライトのタイプの設定
	g_light.Type = D3DLIGHT_DIRECTIONAL; // 平行光源
	// 方向
	D3DXVECTOR3 vecDir;
	vecDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_light.Direction, &vecDir);	// 3次元ベクトルの正規化
	// ディフューズ(拡散反射光)
	g_light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	// アンビエント(環境光)
	g_light.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
		
	//g_light.Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	// ライトの情報クリア
	ZeroMemory(&g_light2, sizeof(D3DLIGHT9));
	// ライトのタイプの設定
	g_light2.Type = D3DLIGHT_DIRECTIONAL; // タイプ
	// 方向
	D3DXVECTOR3 vecDir2;
	vecDir2 = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_light2.Direction, &vecDir2);	// 3次元ベクトルの正規化
	
	//g_light2.Direction.y = -1.0f;

	// ディフューズ(拡散反射光)
	g_light2.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	// アンビエント(環境光)
	//g_light2.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

	g_light2.Specular = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

	//g_light2.Position = D3DXVECTOR3(-1.0f, 40.0f, -15.0f);

	//g_light2.Falloff = 1.0f;
	//g_light2.Theta = D3DXToRadian(100.0f);
	//g_light2.Phi = D3DXToRadian(300.0f);
	//g_light2.Range = 1200.0f;
	//
	//g_light2.Attenuation0 = 1.0f;
	

	// ライトをレンダリングパイプラインに設定
	pDevice->SetLight(0, &g_light);
	pDevice->SetLight(1, &g_light2);
	// ライトの設定
	pDevice->LightEnable(0, TRUE);	//(ライトの番号, OnOff)
	pDevice->LightEnable(1, TRUE);	

	// レンダーステートの設定
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	return S_OK;
}

//=============================================================================
// ライトの終了処理
//=============================================================================
void UninitLight(void)
{
	
}

//=============================================================================
// ライトの更新処理
//=============================================================================
void UpdateLight(LPDIRECT3DDEVICE9 pDevice)
{

	D3DXVECTOR3 vecDir;
	static float LightX;
	
	static float Red = 0.0f;
	static float Green = 0.0f;
	static float Blue = 0.0f;
	static float Alpha = 1.0f;

	LightX += vol;
	Red		+= Redvol;
	Green	+= Greenvol;
	Blue	+= Bluevol;

	/*if(LightX > 1.0f){
		LightX = 1.0f;
		vol *= -1;
	}else if(LightX < -1.0){
		LightX = -1.0f;
		vol *= -1;
	}	
	if(Red > 1.0f){
		Red = 1.0f;
		Redvol *= -1;
	}else if(Red < -1.0){
		Red = -1.0f;
		Redvol *= -1;
	}	
	if(Green > 1.0f){
		Green = 1.0f;
		Greenvol *= -1;
	}else if(Green < -1.0){
		Green = -1.0f;
		Greenvol *= -1;
	}	
	if(Blue > 1.0f){
		Blue = 1.0f;
		Bluevol *= -1;
	}else if(Blue < -1.0){
		Blue = -1.0f;
		Bluevol *= -1;
	}

	vecDir = D3DXVECTOR3(LightX, -1.0f, 0.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_light.Direction, &vecDir);	// 3次元ベクトルの正規化
	
	g_light.Diffuse = D3DXCOLOR(Red, Blue, Green, Alpha);
	// ライトをレンダリングパイプラインに設定
	pDevice->SetLight(0, &g_light);
	// ライトの設定
	//pDevice->LightEnable(0, TRUE);	//(ライトの番号, OnOff)
	// レンダーステートの設定
	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);*/
}

