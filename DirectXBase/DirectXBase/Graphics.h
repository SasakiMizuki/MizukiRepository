//=======================================================================================
//
//	  DirectX Graphics9 クラス定義
//
//=======================================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <tchar.h>
#include "Shader.h"
#include "Debug.h"

#define FOVY			45.0f					// 視野角
#define NEAR_CLIP		1.0f					// ニアクリップを行う距離
#define FAR_CLIP		10000.0f				// ファークリップを行う距離

class CGraphics
{
private:
	LPDIRECT3D9					m_pD3D;			// Direct3D9 オブジェクト
	static LPDIRECT3DDEVICE9	m_pDevice;		// Direct3DDevice9 オブジェクト
	D3DPRESENT_PARAMETERS		m_D3DPP;		// PRESENT PARAMETERS
	LPD3DXFONT					m_pFont;		// D3DXFont オブジェクト

	static D3DXVECTOR3			m_vCamera;
	D3DXMATRIX					m_MatView;		// ビュー マトリックス
	D3DXMATRIX					m_MatProj;		// 射影マトリックス
	D3DLIGHT9					m_Light;

	HWND						m_hWnd;			// ウィンドウ ハンドル
	int							m_nWidth;		// 表示領域幅
	int							m_nHeight;		// 表示領域高さ

public:
	static LPDIRECT3DDEVICE9 GetDevice() {return m_pDevice;}

	static CGraphics* Create(HWND hWnd, int nWidth, int nHeight, bool bWindow);
	void Release();
	bool Begin();
	void End();
	void SwapBuffer();
	void DrawText(int nX, int nY, LPCTSTR psz);
	D3DXMATRIX& GetViewMatrix() { return m_MatView; }
	D3DXMATRIX& GetProjMatrix() { return m_MatProj; }
	static void SetCameraPos(D3DXVECTOR3 vCamera) { m_vCamera = vCamera; };
	D3DXVECTOR3& GetCameraPos() { return m_vCamera; }
	D3DLIGHT9& GetLight() { return m_Light; }

private:
	bool Initialize(HWND hWnd, int nWidth, int nHeight, bool bWindow);
	void Finalize();
};

//=======================================================================================
//	End of File
//=======================================================================================