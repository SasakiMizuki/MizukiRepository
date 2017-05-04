//=======================================================================================
//
//	  ゲームシーン クラス
//
//=======================================================================================
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "define.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "Input.h"

#include "Debug.h"

// 全オブジェクト初期化
void CGameScene::InitObj()
{
	auto Iterator = m_mObj.begin();
	for (; Iterator != m_mObj.end(); ++Iterator) {
		if (Iterator->second == NULL) {
			continue;
		}
		Iterator->second->Init();
	}

	//m_pParticle->PostInit();
}

// 全オブジェクト破棄
void CGameScene::FinObj()
{
	auto Iterator = m_mObj.begin();
	for (; Iterator != m_mObj.end(); ++Iterator) {
		if (Iterator->second == NULL) {
			continue;
		}
		Iterator->second->Fin();
		delete Iterator->second;
	}
}

// 全オブジェクト更新
void CGameScene::UpdateObj()
{
	auto Iterator = m_mObj.begin();
	for (; Iterator != m_mObj.end(); ++Iterator) {
		if (Iterator->second == NULL) {
			continue;
		}
		Iterator->second->Update();
	}
	Iterator = m_mObj.begin();
	for (; Iterator != m_mObj.end(); ++Iterator) {
		if (Iterator->second == NULL) {
			continue;
		}
		Iterator->second->PostUpdate();
	}

	//m_pCamera->PostUpdate();	// カメラ更新
	//m_pSword->PostUpdate();	// カメラ更新
}

// 全オブジェクト描画
//void CGameScene::DrawObj()
//{
//	//m_pCamera->PreDraw();		// カメラ反映
//
//	// 不透明部分描画
//	auto Iterator = m_mObj.begin();
//	for (; Iterator != m_mObj.end(); ++Iterator) {
//		if (Iterator->second == NULL) {
//			continue;
//		}
//		if (Iterator->second->GetDamage() && (m_dwTick & 8)) {
//			continue;
//		}
//		Iterator->second->PreDraw();
//	}
//
//	Iterator = m_mObj.begin();
//	for (; Iterator != m_mObj.end(); ++Iterator) {
//		if (Iterator->second == NULL) {
//			continue;
//		}
//		if (Iterator->second->GetDamage() && (m_dwTick & 8)) {
//			continue;
//		}
//		Iterator->second->Draw(&m_shader);
//	}
//
//	// 半透明部分描画
//	LPDIRECT3DDEVICE9 pD = CGraphics::GetDevice();
//	pD->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
//	pD->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//	pD->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
//	pD->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
//	Iterator = m_mObj.begin();
//	for (; Iterator != m_mObj.end(); ++Iterator) {
//		if (Iterator->second == NULL) {
//			continue;
//		}
//		if (Iterator->second->GetDamage() && (m_dwTick & 8)) {
//			continue;
//		}
//		Iterator->second->DrawAlpha();
//	}
//	pD->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
//	pD->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
//}

//---------------------------------------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------------------------------------
CGameScene::CGameScene()
{
	m_szDebug[0] = _T('\0');

	//m_pPlayer = new CPlayer(this);
	new CFade(this);
	new CJintai(this, D3DXVECTOR3(-300.0f, 0.0f, -300.0f));
	new CEnemy(this);
	new CSword(this);
	new CSky(this);
	new CCamera(this);
	new CLand(this);
	new CPlayerHP(this);
	new CTreeManager(this);
}

//---------------------------------------------------------------------------------------
// デストラクタ
//---------------------------------------------------------------------------------------
CGameScene::~CGameScene()
{
	m_mObj.clear();
}

//---------------------------------------------------------------------------------------
// シーン生成
//---------------------------------------------------------------------------------------
CGameScene* CGameScene::Create(CGraphics* pGraph)
{
	m_pScene = new CGameScene();
	if (m_pScene) {
		if (!m_pScene->Initialize(pGraph)) {
			SAFE_DELETE(m_pScene);
		}
	}
	m_pGraph = pGraph;
	return m_pScene;
}

//---------------------------------------------------------------------------------------
// デバイス、リソース初期化
//---------------------------------------------------------------------------------------
bool CGameScene::Initialize(CGraphics* pGraph)
{
	m_pGraph = pGraph;
	m_target.Init();
	CJintai::LoadMesh();
	//-------- ゲーム用オブジェクトの初期化
	InitObj();

	m_shader.Load(_T("../data/shader/Toon.fx"));
	return true;
}

//---------------------------------------------------------------------------------------
// デバイス、リソース解放
//---------------------------------------------------------------------------------------
void CGameScene::Finalize()
{
	//-------- ゲーム用オブジェクトの後始末
	//SAFE_DELETE(m_pScene);
	m_shader.Release();
	FinObj();
}

//---------------------------------------------------------------------------------------
// シーン解放
//---------------------------------------------------------------------------------------
void CGameScene::Release()
{
	Finalize();
	delete this;
}

//---------------------------------------------------------------------------------------
// ゲーム描画処理（メインループからコールされる）
//---------------------------------------------------------------------------------------
void CGameScene::Render()
{
	if (m_pGraph->Begin()) {	// 描画開始

		Draw();					// 描画処理

		m_pGraph->End();		// 描画終了
	}
	m_pGraph->SwapBuffer();		// バックバッファ入替
}

////---------------------------------------------------------------------------------------
//// ゲームメイン処理（メインループからコールされる）
////---------------------------------------------------------------------------------------
//void CGameScene::Update()
//{
//	++m_dwTick;
//
//	// 入力更新
//	CInput::Update();
//
//
//	//----- ここにゲーム本体処理
//		UpdateObj();
//
//		/*if (CInput::GetKeyPress(DIK_F1)) {
//			m_pPlayer->ChangeHP(-1000);
//		}
//		if (CInput::GetKeyPress(DIK_F2)) {
//			m_pEnemy->ChangeHP(-1000);
//		}
//
//		if (!m_bSceneChange && (m_pPlayer->GetHP() <= 0.0f || m_pEnemy->GetHP() <= 0.0f)){
//			m_bSceneChange = true;
//			m_pFade->Start(FADEOUT);
//		}
//		if (m_bSceneChange && !m_pFade->GetDoingFade() && m_pEnemy->GetHP() <= 0.0f) {
//			CSceneManager::Instance()->ChangeScene(Scene_End);
//		} else if (m_bSceneChange && !m_pFade->GetDoingFade() && m_pPlayer->GetHP() <= 0.0f){
//			CSceneManager::Instance()->ChangeScene(Scene_GameOver);	
//		}*/
//}
//
////---------------------------------------------------------------------------------------
//// 描画処理（CGraphics::Render() からコールされる）
////---------------------------------------------------------------------------------------
//void CGameScene::Draw()
//{
//	m_szDebug[0] = _T('\0');	// デバッグ文字列初期化
//
//	// FPS を画面に描画するための文字列を作成
//	TCHAR	str[256];
//	_stprintf(str, _T("FPS = %d\n"), m_FPS);
//	lstrcat(m_szDebug, str);
//
//	//----- ここに描画処理
//	DrawObj();
//
//	// デバッグ文字列描画
//	m_pGraph->DrawText(0, 0, m_szDebug);
//}

//=======================================================================================
//	End of File
//=======================================================================================