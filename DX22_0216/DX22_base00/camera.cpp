//=============================================================================
//
// カメラ処理 [camera.cpp]
//
//=============================================================================
#include "camera.h"
#include "input.h"
//#include "main.h"
#include "model.h"
#include <math.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
const float CAMERA_MOVE_VOL (3.0f);

const float CAMRA_MOVE_RIMIT (1.0f);
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
D3DXVECTOR3		g_posCameraPoint;	// 視点
D3DXVECTOR3		g_posCameraTarget;	// 注視点
D3DXVECTOR3		g_vecCameraUp;		// 上
D3DXVECTOR3		g_posCameraPointDest;//視点の目標位置
D3DXVECTOR3		g_posCameraTargetDest;//注視点の目標地点
D3DXMATRIX		g_mtxView;			// ビューマトリクス
D3DXMATRIX		g_mtxProjection;	// プロジェクションマトリクス
D3DXVECTOR3		g_rotCamera;		// 角度
float			RadTheta = 270.0f;
float			Radgamma = 30.0f;
float			Raddelta = 0.0f;
float			Radius = 200;

float			g_fLengthCamera;

//=============================================================================
// カメラの初期化処理
//=============================================================================
HRESULT InitCamera(void)
{
	g_posCameraPoint = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
	g_posCameraTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_vecCameraUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	g_rotCamera = D3DXVECTOR3(0, 0, 0);
	g_posCameraPointDest = g_posCameraPoint;
	g_posCameraTargetDest = g_posCameraTarget;

	D3DXVECTOR3 temp = g_posCameraTarget - g_posCameraPoint;
	g_fLengthCamera = D3DXVec3Length(&temp);

	return S_OK;
}

//=============================================================================
// カメラの終了処理
//=============================================================================
void UninitCamera(void)
{
}

//=============================================================================
// カメラの更新処理
//=============================================================================
void UpdateCamera(void)
{
	//移動
	/*if(GetKeyboardPress(DIK_LEFT)){
		RadTheta -= CAMERA_MOVE_VOL;
	}
	if(GetKeyboardPress(DIK_RIGHT)){
		RadTheta += CAMERA_MOVE_VOL;
	}
	if(GetKeyboardPress(DIK_UP)){
		Radgamma -= CAMERA_MOVE_VOL;
		//RadTheta -= CAMERA_MOVE_VOL;
	}
	if(GetKeyboardPress(DIK_DOWN)){
		Radgamma += CAMERA_MOVE_VOL;
		//RadTheta += CAMERA_MOVE_VOL;
	}*/
	if(GetKeyboardPress(DIK_U)){
		Radgamma -= CAMERA_MOVE_VOL;
	}
	if(GetKeyboardPress(DIK_I)){
		Radgamma += CAMERA_MOVE_VOL;
	}
	if(GetKeyboardPress(DIK_9)){
		Radius += CAMERA_MOVE_VOL;
	}
	if(GetKeyboardPress(DIK_U)){
		g_rotCamera.y -= 0.1f;
	}
	if(GetKeyboardPress(DIK_J)){
		g_rotCamera.y += 0.1f;
	}
	if(GetKeyboardPress(DIK_C)){
		g_fLengthCamera -= 10.0f;
		if(g_fLengthCamera < 2)
			g_fLengthCamera = 2;
	}
	if(GetKeyboardPress(DIK_V)){
		g_fLengthCamera += 10.0f;
		if(g_fLengthCamera > 1000)
			g_fLengthCamera = 1000;
	}


	//if(sin(D3DXToRadian(Radgamma)) < 0){
	//	g_vecCameraUp = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	//}else{
	//	g_vecCameraUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//}

	/*g_posCameraPoint = D3DXVECTOR3(cos(D3DXToRadian(RadTheta)) * cos(D3DXToRadian(Radgamma)) * Radius,
									sin(D3DXToRadian(Radgamma)) * Radius, 
									cos(D3DXToRadian(Radgamma)) * sin(D3DXToRadian(RadTheta)) * Radius);*/

	// モデルから一定距離に置く
	D3DXVECTOR3 modelPos = GetModelPos();
	D3DXVECTOR3 modelRot = GetModelRot();

	// パターン3:目標位置を設定
	g_posCameraPointDest = modelPos + D3DXVECTOR3(sin(modelRot.y) * g_fLengthCamera, 0.4f * g_fLengthCamera, cos(modelRot.y) * g_fLengthCamera);
	g_posCameraTargetDest = modelPos;
	
	g_posCameraPoint += (g_posCameraPointDest - g_posCameraPoint) * 0.20f;
	g_posCameraTarget += (g_posCameraTargetDest - g_posCameraTarget) * 0.20f;

	//D3DXVec3Normalize(&g_posCameraPoint, &g_posCameraPoint);
	
}

//=============================================================================
// カメラの設定処理
//=============================================================================
void SetCamera(LPDIRECT3DDEVICE9 pDevice)
{
	// 描画前にカメラをリセットする
	// ビューマトリクスの初期化
	D3DXMatrixIdentity(&g_mtxView);
	
	// ビューマトリクスの作成
	/**************今日のメイン**************/
	D3DXMatrixLookAtLH(
		&g_mtxView,			// 格納用
		&g_posCameraPoint,
		&g_posCameraTarget,
		&g_vecCameraUp);
	/****************************************/
	
	// ビューマトリクスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_mtxView);
	
	// プロジェクションマトリクスの初期化
	D3DXMatrixIdentity(&g_mtxProjection);
	
	// プロジェクションマトリクスの作成
	/**************今日のメイン**************/
	D3DXMatrixPerspectiveFovLH(
		&g_mtxProjection,	// 格納先
		D3DXToRadian(60.0f),// デグリーからラジアン値に変更
		(float)SCREEN_WIDTH / SCREEN_HEIGHT,// アスペクト比
		1.0f,
		2000.0f);
	/****************************************/
	
	// プロジェクションマトリクスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_mtxProjection);


}

//=============================================================================
// カメラの向きを取得
//=============================================================================
D3DXVECTOR3 GetRotCamera(void)
{
	return g_rotCamera;
}

// ビューの取得
D3DXMATRIX GetMtxView(){
	return g_mtxView;
}
