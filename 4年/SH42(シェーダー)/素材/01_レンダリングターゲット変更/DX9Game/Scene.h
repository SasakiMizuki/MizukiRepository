//=======================================================================================
//
//	  ゲームシーン クラス定義
//
//=======================================================================================
#pragma once

#include "Graphics.h"
#include "Mesh.h"	// CMeshクラス定義
#include "RenderTarget.h"
#include "BoxMesh.h"

class CScene
{
private:
	CGraphics*	m_pGraph;			// グラフィックデバイス

	TCHAR		m_szDebug[1024];	// デバッグ用文字列
	int			m_FPS;				// フレーム数カウント用

	//-------- ゲーム用オブジェクト
	D3DXMATRIX	m_world;// メッシュ表示用
	CMesh		m_mesh;	// メッシュ オブジェクト
	D3DXVECTOR3	m_angle;// メッシュ表示用

	CRenderTarget	m_target;	// レンダリングターゲット切替
	CBoxMesh		m_box;		// テクスチャを貼るモデル
	D3DXMATRIX		m_boxWorld;	// テクスチャを貼るモデル用
	D3DXVECTOR3		m_boxAngle;	// テクスチャを貼るモデル用

public:
	CScene();
	virtual ~CScene();

	static CScene* Create(CGraphics* pGraph);
	void Release();
	void Render();
	void Update();
	void SetFPS(int nFPS) {m_FPS = nFPS;}
	void AddDebugStr(LPCTSTR psz) {lstrcat(m_szDebug, psz);}

private:
	bool Initialize(CGraphics* pGraph);
	void Finalize();
	void Draw();
};

//=======================================================================================
//	End of File
//=======================================================================================