//=======================================================================================
//
//	  ゲームシーン クラス定義
//
//=======================================================================================
#pragma once

#include <map>
#include "Graphics.h"
#include "C3DObj.h"
#include "C2DObj.h"
#include "RenderTarget.h"
#include "Mesh.h"
class CSceneBase
{
protected:
	CGraphics*	 m_pGraph;			// グラフィックデバイス
	//CObjectBase* m_pObj;				// オブジェクト先頭
	TCHAR		m_szDebug[1024];	// デバッグ用文字列
	int			m_FPS;				// フレーム数カウント用

	DWORD		m_dwTick;			// 経過時間(フレーム数)
	std::map<int, CObjectBase*> m_mObj;
	CRenderTarget m_target;
	CShader	m_shader;

	bool		m_bSceneChange;		// フェード時待機用flag
	unsigned int m_nNumberOfObj;	// 現在生きている(マップに入っている)オブジェクトの総数

public:
	CSceneBase();
	virtual ~CSceneBase();

	virtual CSceneBase* Create(CGraphics* pGraph);
	virtual void Release();
	virtual void Render();
	virtual void Update();
	virtual void SetFPS(int nFPS) {m_FPS = nFPS;}
	virtual void AddDebugStr(LPCTSTR psz) {lstrcat(m_szDebug, psz);}
	
	virtual void Add(CObjectBase* pObj);
	virtual void Del(int nNumber);
	virtual CObjectBase* Find(UINT uID, int nNumber);
	virtual void InitObj();
	virtual void FinObj();
	virtual void UpdateObj();
	virtual void DrawObj();
	//virtual DWORD GetTick();

	virtual bool Initialize(CGraphics* pGraph);
	virtual void Finalize();
	virtual void Draw();
};

//=======================================================================================
//	End of File
//=======================================================================================