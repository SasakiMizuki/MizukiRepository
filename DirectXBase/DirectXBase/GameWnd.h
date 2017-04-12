//=======================================================================================
//
//	  �Q�[���p�E�B���h�E �N���X��`
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
	CGraphics*	m_pGraph;			// �`��f�o�C�X �N���X
	CSceneBase*		m_pScene;			// �V�[��

	bool		m_bWindow;			// �E�B���h�E / �t���X�N���[��

	DWORD		m_dwExecLastTime;	// FPS�v���p
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