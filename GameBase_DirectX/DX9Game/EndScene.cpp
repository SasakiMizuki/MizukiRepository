#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "define.h"
#include "EndScene.h"
#include "SceneManager.h"
#include "Input.h"

// 全オブジェクト初期化
void CEndScene::InitObj() {
	CObjectBase* pObj = m_pObj;
	for (; pObj; pObj = pObj->GetNext()) {
		pObj->Init();
	}
}

// 全オブジェクト破棄
void CEndScene::FinObj() {
	CObjectBase* pObj = m_pObj;
	CObjectBase* pNext;
	for (; pObj; pObj = pNext) {
		pNext = pObj->GetNext();
		pObj->Fin();
	}
}

// 全オブジェクト更新
void CEndScene::UpdateObj() {
	CObjectBase* pObj = m_pObj;
	CObjectBase* pNext;
	for (; pObj; pObj = pNext) {
		pNext = pObj->GetNext();
		pObj->Update();
	}

	m_pCamera->PostUpdate();	// カメラ更新
}

// 全オブジェクト描画
void CEndScene::DrawObj() {
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
CEndScene::CEndScene() {
	m_szDebug[0] = _T('\0');

	m_pFade = new CFade(this);
	m_pCamera = new CCamera(this);
	m_pButton = new CFadeButton(this);
	m_pEndBG = new CEndBG(this);
}

//---------------------------------------------------------------------------------------
// デストラクタ
//---------------------------------------------------------------------------------------
CEndScene::~CEndScene() {
	delete m_pFade;
	delete m_pEndBG;
	delete m_pCamera;
	delete m_pButton;
}

//---------------------------------------------------------------------------------------
// シーン生成
//---------------------------------------------------------------------------------------
CEndScene* CEndScene::Create(CGraphics* pGraph) {
	m_pScene = new CEndScene();
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
bool CEndScene::Initialize(CGraphics* pGraph) {

	//-------- ゲーム用オブジェクトの初期化
	InitObj();

	return true;
}

//---------------------------------------------------------------------------------------
// デバイス、リソース解放
//---------------------------------------------------------------------------------------
void CEndScene::Finalize() {
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
void CEndScene::Release() {
	Finalize();
	delete this;
}

//---------------------------------------------------------------------------------------
// ゲーム描画処理（メインループからコールされる）
//---------------------------------------------------------------------------------------
void CEndScene::Render() {
	if (m_pGraph->Begin()) {	// 描画開始

		Draw();					// 描画処理

		m_pGraph->End();		// 描画終了
	}
	m_pGraph->SwapBuffer();		// バックバッファ入替
}

//---------------------------------------------------------------------------------------
// ゲームメイン処理（メインループからコールされる）
//---------------------------------------------------------------------------------------
void CEndScene::Update() {
	++m_dwTick;

	// 入力更新
	CInput::Update();

	//----- ここにゲーム本体処理
	UpdateObj();


	if (CInput::GetKeyTrigger(DIK_U)) {
		m_bSceneChange = true;
		m_pFade->Start(FADEOUT);
	}
	if (m_bSceneChange && (!m_pFade->GetDoingFade()))
		CSceneManager::Instance()->ChangeScene(Scene_Title);
}
//---------------------------------------------------------------------------------------
// 描画処理（CGraphics::Render() からコールされる）
//---------------------------------------------------------------------------------------
void CEndScene::Draw() {
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