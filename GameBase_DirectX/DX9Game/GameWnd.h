//=======================================================================================
//
//	  ゲーム用ウィンドウ クラス定義
//
//=======================================================================================
#pragma once

#include "Window.h"
#include "Graphics.h"
#include "SceneBase.h"
#include "define.h"

class CGameWindow : public CWindow
{
public:
	static CGameWindow*	m_pMainWnd;

private:
	CGraphics*	m_pGraph;			// 描画デバイス クラス
	CSceneBase*		m_pScene;			// シーン

	bool		m_bWindow;			// ウィンドウ / フルスクリーン

	DWORD		m_dwExecLastTime;	// FPS計測用
	DWORD		m_dwFPSLastTime;
	DWORD		m_dwFrameCount;

public:
	bool InitInstance();
	int ExitInstance();
	bool OnIdle(long lCount);
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	bool OnEraseBkgnd(HDC hdc);
	bool OnSetCursor(HWND hwnd, UINT nHitTest, UINT uMouseMsg);
};

//=======================================================================================
//	End of File
//=======================================================================================