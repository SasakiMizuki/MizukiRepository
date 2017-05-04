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
#include "SceneBase.h"
#include "SceneManager.h"
#include "Input.h"

// シーンにオブジェクトを追加
void CSceneBase::Add(CObjectBase* pObj) {
	int i = 0;
	for (; i < m_mObj.size(); ++i) {
		auto Iterator = m_mObj.find(i);
		if (Iterator == m_mObj.end())
			break;
	}

	std::pair<int, CObjectBase*> NewObjectPair(i, pObj);

	m_mObj.insert(NewObjectPair);
	pObj->SetNumber(i);

}

// シーンからオブジェクトを削除
void CSceneBase::Del(int nNumber) {
	auto Iterator = m_mObj.find(nNumber);
	if (Iterator == m_mObj.end()) {
		return;
	}

	delete Iterator->second;
	m_mObj.erase(nNumber);
	//m_nNumberOfObj--;
}

// オブジェクト検索
CObjectBase* CSceneBase::Find(UINT uID, int nNumber) {
	//auto Iterator = m_mObj.find(nNumber);
	//if (Iterator == m_mObj.end())
	//	return NULL;
	//if (Iterator->second->GetID() != uID)
	//	return NULL;

	auto Iterator = m_mObj.begin();
	for (; Iterator != m_mObj.end(); ++Iterator) {
		if (Iterator->first < nNumber)
			continue;
		if (Iterator->second->GetID() == uID)
			return Iterator->second;
	}

	return NULL;
}

// 全オブジェクト初期化
void CSceneBase::InitObj() {
	auto Iterator = m_mObj.begin();
	for (; Iterator != m_mObj.end(); ++Iterator) {
		if (Iterator->second == NULL) {
			continue;
		}
		Iterator->second->Init();
	}
}

// 全オブジェクト破棄
void CSceneBase::FinObj() {
	auto Iterator = m_mObj.begin();
	for (; Iterator != m_mObj.end(); ++Iterator) {
		if (Iterator->second == NULL) {
			continue;
		}
		Iterator->second->Fin();
	}
}

// 全オブジェクト更新
void CSceneBase::UpdateObj() {
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
}

// 全オブジェクト描画
void CSceneBase::DrawObj() {
	//m_pCamera->PreDraw();		// カメラ反映
	// 不透明部分描画
	auto Iterator = m_mObj.begin();
	for (; Iterator != m_mObj.end(); ++Iterator) {
		if (Iterator->second == NULL) {
			continue;
		}
		if (Iterator->second->GetDamage() && (m_dwTick & 8)) {
			continue;
		}
		Iterator->second->PreDraw();
	}

	Iterator = m_mObj.begin();
	// 不透明部分描画
	for (; Iterator != m_mObj.end(); ++Iterator) {
		if (Iterator->second == NULL) {
			continue;
		}
		if (Iterator->second->GetDamage() && (m_dwTick & 8)) {
			continue;
		}
		Iterator->second->Draw(&m_shader);
	}

	// 半透明部分描画
	LPDIRECT3DDEVICE9 pD = CGraphics::GetDevice();
	pD->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pD->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	Iterator = m_mObj.begin();
	for (; Iterator != m_mObj.end(); ++Iterator) {
		if (Iterator->second == NULL) {
			continue;
		}
		if (Iterator->second->GetDamage() && (m_dwTick & 8)) {
			continue;
		}
		Iterator->second->DrawAlpha();
	}
	pD->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pD->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

//---------------------------------------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------------------------------------
CSceneBase::CSceneBase() :
	m_pGraph(NULL),
	m_FPS(),
	m_dwTick(0) {
	m_mObj.clear();
	m_szDebug[0] = _T('\0');
	m_bSceneChange = false;
	m_nNumberOfObj = 0;
}

//---------------------------------------------------------------------------------------
// デストラクタ
//---------------------------------------------------------------------------------------
CSceneBase::~CSceneBase() {

}

//---------------------------------------------------------------------------------------
// シーン生成
//---------------------------------------------------------------------------------------
CSceneBase* CSceneBase::Create(CGraphics* pGraph) {
	CSceneBase* pScene = new CSceneBase();
	if (pScene) {
		if (!pScene->Initialize(pGraph)) {
			SAFE_DELETE(pScene);
		}
	}
	return pScene;
}

//---------------------------------------------------------------------------------------
// デバイス、リソース初期化
//---------------------------------------------------------------------------------------
bool CSceneBase::Initialize(CGraphics* pGraph) {
	m_pGraph = pGraph;

	//-------- ゲーム用オブジェクトの初期化
	InitObj();

	return true;
}

//---------------------------------------------------------------------------------------
// デバイス、リソース解放
//---------------------------------------------------------------------------------------
void CSceneBase::Finalize() {
	//-------- ゲーム用オブジェクトの後始末
	FinObj();
}

//---------------------------------------------------------------------------------------
// シーン解放
//---------------------------------------------------------------------------------------
void CSceneBase::Release() {
	Finalize();
	delete this;
}

//---------------------------------------------------------------------------------------
// ゲーム描画処理（メインループからコールされる）
//---------------------------------------------------------------------------------------
void CSceneBase::Render() {
	if (m_pGraph->Begin()) {	// 描画開始

		Draw();					// 描画処理

		m_pGraph->End();		// 描画終了
	}
	m_pGraph->SwapBuffer();		// バックバッファ入替
}

//---------------------------------------------------------------------------------------
// ゲームメイン処理（メインループからコールされる）
//---------------------------------------------------------------------------------------
void CSceneBase::Update() {
	++m_dwTick;

	// 入力更新
	CInput::Update();

	//----- ここにゲーム本体処理
	UpdateObj();
}

//---------------------------------------------------------------------------------------
// 描画処理（CGraphics::Render() からコールされる）
//---------------------------------------------------------------------------------------
void CSceneBase::Draw() {
	m_szDebug[0] = _T('\0');	// デバッグ文字列初期化

								// FPS を画面に描画するための文字列を作成
	TCHAR	str[256];
	_stprintf(str, _T("FPS = %d\n"), m_FPS);
	lstrcat(m_szDebug, str);

	//----- ここに描画処理
	m_shader.SetViewMatrix(&m_pGraph->GetViewMatrix());
	m_shader.SetProjMatrix(&m_pGraph->GetProjMatrix());
	m_shader.SetLight(&m_pGraph->GetLight());
	DrawObj();

	// デバッグ文字列描画
	m_pGraph->DrawText(0, 0, m_szDebug);
}

//=======================================================================================
//	End of File
//=======================================================================================