#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "define.h"
#include "DescriptionScene.h"
#include "SceneManager.h"
#include "Input.h"


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
#include "TitleScene.h"
#include "Input.h"

// 全オブジェクト初期化
void CDescriptionScene::InitObj() {
	CObjectBase* pObj = m_pObj;
	for (; pObj; pObj = pObj->GetNext()) {
		pObj->Init();
	}
}

// 全オブジェクト破棄
void CDescriptionScene::FinObj() {
	CObjectBase* pObj = m_pObj;
	CObjectBase* pNext;
	for (; pObj; pObj = pNext) {
		pNext = pObj->GetNext();
		pObj->Fin();
	}
}

// 全オブジェクト更新
void CDescriptionScene::UpdateObj() {
	CObjectBase* pObj = m_pObj;
	CObjectBase* pNext;
	for (; pObj; pObj = pNext) {
		pNext = pObj->GetNext();
		pObj->Update();
	}

	m_pCamera->PostUpdate();	// カメラ更新
}

// 全オブジェクト描画
void CDescriptionScene::DrawObj() {
	m_pCamera->PreDraw();		// カメラ反映

								// 不透明部分描画
	CObjectBase* pObj = m_pObj;
	for (; pObj; pObj = pObj->GetNext()) {
		if (pObj->GetDamage() && (m_dwTick & 8)) {
			continue;
		}
		pObj->Draw();
	}

	// 半透明部分描画
	LPDIRECT3DDEVICE9 pD = CGraphics::GetDevice();
	pD->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pD->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pObj = m_pObj;
	for (; pObj; pObj = pObj->GetNext()) {
		if (pObj->GetDamage() && (m_dwTick & 8)) {
			continue;
		}
		pObj->DrawAlpha();
	}
	pD->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pD->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

//---------------------------------------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------------------------------------
CDescriptionScene::CDescriptionScene() {
	m_szDebug[0] = _T('\0');

	m_pCamera = new CCamera(this);
	m_pFade = new CFade(this);
	m_pButton = new CFadeButton(this);
	m_pDescriptionSceneBG = new CDescriptionSceneBG(this);
}

//---------------------------------------------------------------------------------------
// デストラクタ
//---------------------------------------------------------------------------------------
CDescriptionScene::~CDescriptionScene() {
	delete m_pDescriptionSceneBG;
	delete m_pCamera;
	delete m_pButton;
	delete m_pFade;
}

//---------------------------------------------------------------------------------------
// シーン生成
//---------------------------------------------------------------------------------------
CDescriptionScene* CDescriptionScene::Create(CGraphics* pGraph) {
	m_pScene = new CDescriptionScene();
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
bool CDescriptionScene::Initialize(CGraphics* pGraph) {

	//-------- ゲーム用オブジェクトの初期化
	InitObj();

	return true;
}

//---------------------------------------------------------------------------------------
// デバイス、リソース解放
//---------------------------------------------------------------------------------------
void CDescriptionScene::Finalize() {
	//-------- ゲーム用オブジェクトの後始末
	if (m_pScene) {
		delete m_pScene;
		m_pScene = NULL;
	}
	FinObj();
}

//---------------------------------------------------------------------------------------
// シーン解放
//---------------------------------------------------------------------------------------
void CDescriptionScene::Release() {
	Finalize();
	delete this;
}

//---------------------------------------------------------------------------------------
// ゲーム描画処理（メインループからコールされる）
//---------------------------------------------------------------------------------------
void CDescriptionScene::Render() {
	if (m_pGraph->Begin()) {	// 描画開始

		Draw();					// 描画処理

		m_pGraph->End();		// 描画終了
	}
	m_pGraph->SwapBuffer();		// バックバッファ入替
}

//---------------------------------------------------------------------------------------
// ゲームメイン処理（メインループからコールされる）
//---------------------------------------------------------------------------------------
void CDescriptionScene::Update() {
	++m_dwTick;

	// 入力更新
	CInput::Update();

	//----- ここにゲーム本体処理
	UpdateObj();
	if (CInput::GetKeyTrigger(DIK_U)) {
		m_pFade->Start(FADEOUT);
		m_bSceneChange = true;
	}

	if (m_bSceneChange && (!m_pFade->GetDoingFade()))
		CSceneManager::Instance()->ChangeScene(Scene_Game);
}

//---------------------------------------------------------------------------------------
// 描画処理（CGraphics::Render() からコールされる）
//---------------------------------------------------------------------------------------
void CDescriptionScene::Draw() {
	m_szDebug[0] = _T('\0');	// デバッグ文字列初期化

								// FPS を画面に描画するための文字列を作成
	TCHAR	str[256];
	_stprintf(str, _T("FPS = %d\n"), m_FPS);
	lstrcat(m_szDebug, str);

	//----- ここに描画処理
	DrawObj();

	// デバッグ文字列描画
	m_pGraph->DrawText(0, 0, m_szDebug);
}

//=======================================================================================
//	End of File
//=======================================================================================