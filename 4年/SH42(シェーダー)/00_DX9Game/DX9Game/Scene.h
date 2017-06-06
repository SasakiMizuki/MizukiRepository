//=======================================================================================
//
//	  ゲームシーン クラス定義
//
//=======================================================================================
#pragma once

#include "Graphics.h"

#include "Mesh.h"	// CMeshクラス定義

#include "RenderTarget.h"

class CScene
{
private:
	CGraphics*	m_pGraph;			// グラフィックデバイス

	TCHAR		m_szDebug[1024];	// デバッグ用文字列
	int			m_FPS;				// フレーム数カウント用

	//-------- ゲーム用オブジェクト
	D3DXMATRIX	m_world;// メッシュ表示用
	CMesh		m_mesh;	// メッシュ オブジェクト

	CRenderTarget m_target;	// レンダリングターゲット切り替え
	CMesh		  m_box;	// テクスチャを貼る箱
	CShader		  m_shader;
	D3DXVECTOR3   m_angle;
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