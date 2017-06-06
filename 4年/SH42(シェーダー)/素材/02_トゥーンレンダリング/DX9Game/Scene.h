//=======================================================================================
//
//	  ゲームシーン クラス定義
//
//=======================================================================================
#pragma once

#include "Graphics.h"
#include "RenderTarget.h"

#include "Mesh.h"	// CMeshクラス定義

class CScene
{
private:
	CGraphics*	m_pGraph;			// グラフィックデバイス

	TCHAR		m_szDebug[1024];	// デバッグ用文字列
	int			m_FPS;				// フレーム数カウント用

	//-------- ゲーム用オブジェクト
	D3DXMATRIX	m_world;	// メッシュ表示用
	CMesh		m_mesh;		// メッシュ オブジェクト
	CShader		m_shader;	// シェーダ
	D3DXVECTOR3	m_angle;
	CRenderTarget m_target;
	float m_focus;
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