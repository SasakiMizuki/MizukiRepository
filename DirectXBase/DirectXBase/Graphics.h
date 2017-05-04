//=======================================================================================
//
//	  DirectX Graphics9 �N���X��`
//
//=======================================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <tchar.h>
#include "Shader.h"
#include "Debug.h"

#define FOVY			45.0f					// ����p
#define NEAR_CLIP		1.0f					// �j�A�N���b�v���s������
#define FAR_CLIP		10000.0f				// �t�@�[�N���b�v���s������

class CGraphics
{
private:
	LPDIRECT3D9					m_pD3D;			// Direct3D9 �I�u�W�F�N�g
	static LPDIRECT3DDEVICE9	m_pDevice;		// Direct3DDevice9 �I�u�W�F�N�g
	D3DPRESENT_PARAMETERS		m_D3DPP;		// PRESENT PARAMETERS
	LPD3DXFONT					m_pFont;		// D3DXFont �I�u�W�F�N�g

	D3DXMATRIX					m_MatView;		// �r���[ �}�g���b�N�X
	D3DXMATRIX					m_MatProj;		// �ˉe�}�g���b�N�X
	D3DLIGHT9					m_Light;

	HWND						m_hWnd;			// �E�B���h�E �n���h��
	int							m_nWidth;		// �\���̈敝
	int							m_nHeight;		// �\���̈捂��

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
	//D3DXVECTOR3& GetCameraPos() { return m_vCamera; }
	D3DLIGHT9& GetLight() { return m_Light; }

private:
	bool Initialize(HWND hWnd, int nWidth, int nHeight, bool bWindow);
	void Finalize();
};

//=======================================================================================
//	End of File
//=======================================================================================