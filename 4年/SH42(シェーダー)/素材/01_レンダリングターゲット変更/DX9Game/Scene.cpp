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
#include "Scene.h"
#include "Input.h"

//---------------------------------------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------------------------------------
CScene::CScene()
{
	m_FPS = 0;
}

//---------------------------------------------------------------------------------------
// デストラクタ
//---------------------------------------------------------------------------------------
CScene::~CScene()
{
}

//---------------------------------------------------------------------------------------
// シーン生成
//---------------------------------------------------------------------------------------
CScene* CScene::Create(CGraphics* pGraph)
{
	CScene* pScene = new CScene();
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
bool CScene::Initialize(CGraphics* pGraph)
{
	m_pGraph = pGraph;

	//-------- ゲーム用オブジェクトの初期化
	m_target.Init();	// レンダリングターゲット切替 初期化
	if (!m_mesh.Initialize(_T("../data/model/gtank.X"))) {
		::MessageBox(NULL, _T("gtank.Xが読めません."), _T("error"), MB_OK);
		return false;
	}
	if (!m_box.Initialize(_T("../data/model/box.x"))) {
		::MessageBox(NULL, _T("box.xが読めません."), _T("error"), MB_OK);
		return false;
	}
	D3DXMatrixIdentity(&m_world);
	D3DXMatrixIdentity(&m_boxWorld);
	m_angle = D3DXVECTOR3(0, 0, 0);
	m_boxAngle = D3DXVECTOR3(0, 0, 0);

	return true;
}

//---------------------------------------------------------------------------------------
// デバイス、リソース解放
//---------------------------------------------------------------------------------------
void CScene::Finalize()
{
	//-------- ゲーム用オブジェクトの後始末
	m_box.Finalize();
	m_mesh.Finalize();
	m_target.Fin();		// レンダリングターゲット切替 解放
}

//---------------------------------------------------------------------------------------
// シーン解放
//---------------------------------------------------------------------------------------
void CScene::Release()
{
	Finalize();
	delete this;
}

//---------------------------------------------------------------------------------------
// ゲーム描画処理（メインループからコールされる）
//---------------------------------------------------------------------------------------
void CScene::Render()
{
	if (m_pGraph->Begin()) {	// 描画開始

		Draw();					// 描画処理

		m_pGraph->End();		// 描画終了
	}
	m_pGraph->SwapBuffer();		// バックバッファ入替
}

//---------------------------------------------------------------------------------------
// ゲームメイン処理（メインループからコールされる）
//---------------------------------------------------------------------------------------
void CScene::Update()
{
	// 入力更新
	CInput::Update();

	//----- ここにゲーム本体処理
	if (::GetAsyncKeyState(VK_SHIFT) & 0x8000) {
		if (::GetAsyncKeyState(VK_LEFT) & 0x8000) {
			m_angle.y += 1.0f;
			if (m_angle.y >= 180.0f) m_angle.y -= 360.0f;
		}
		if (::GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			m_angle.y -= 1.0f;
			if (m_angle.y < -180.0f) m_angle.y += 360.0f;
		}
	} else {
		if (::GetAsyncKeyState(VK_LEFT) & 0x8000) {
			m_boxAngle.y += 1.0f;
			if (m_boxAngle.y >= 180.0f) m_boxAngle.y -= 360.0f;
		}
		if (::GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			m_boxAngle.y -= 1.0f;
			if (m_boxAngle.y < -180.0f) m_boxAngle.y += 360.0f;
		}
	}
	D3DXMatrixRotationYawPitchRoll(&m_world,
		D3DXToRadian(m_angle.y),
		D3DXToRadian(m_angle.x),
		D3DXToRadian(m_angle.z));
	D3DXMatrixRotationYawPitchRoll(&m_boxWorld,
		D3DXToRadian(m_boxAngle.y),
		D3DXToRadian(m_boxAngle.x),
		D3DXToRadian(m_boxAngle.z));
}

//---------------------------------------------------------------------------------------
// 描画処理（CGraphics::Render() からコールされる）
//---------------------------------------------------------------------------------------
void CScene::Draw()
{
	m_szDebug[0] = _T('\0');	// デバッグ文字列初期化

	// FPS を画面に描画するための文字列を作成
	TCHAR	str[256];
	_stprintf(str, _T("FPS = %d\n"), m_FPS);
	lstrcat(m_szDebug, str);

	//----- ここに描画処理
	m_target.Change();	// レンダリングターゲット保存、切替
	m_mesh.Draw(m_world);
	m_target.Reset();	// レンダリングターゲット復帰

	m_box.SetTexture(m_target.GetTexture());
	m_box.Draw(m_boxWorld);
/*
	float width = 800.0f;
	float height = 600.0f;
	float x1 = width * 0.25f;
	float y1 = height * 0.25f;
	float x2 = x1 + width * 0.5f;
	float y2 = y1 + height * 0.5f;
	struct {
		float		x, y, z, rhw;
		D3DCOLOR	diffuse;
		float		u, v;
	} vtx[] = {
		{x1, y2, 0.0f, 1.0f, (DWORD)-1, 0.0f, 1.0f},
		{x1, y1, 0.0f, 1.0f, (DWORD)-1, 0.0f, 0.0f},
		{x2, y2, 0.0f, 1.0f, (DWORD)-1, 1.0f, 1.0f},
		{x2, y1, 0.0f, 1.0f, (DWORD)-1, 1.0f, 0.0f},
	};
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE |
		D3DFVF_TEX1);
	pDevice->SetTexture(0, m_target.GetTexture());
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2,
		vtx, sizeof(vtx[0]));
*/
	// デバッグ文字列描画
	m_pGraph->DrawText(0, 0, m_szDebug);
}

//=======================================================================================
//	End of File
//=======================================================================================