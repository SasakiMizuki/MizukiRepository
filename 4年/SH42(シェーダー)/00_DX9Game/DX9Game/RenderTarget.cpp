//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
//  RenderTarget.cpp
//
//  作成者:佐々木瑞生
//==================================================
//  概要
//
//
//==================================================
//  作成日:2017/04/14
//  更新日:
//    20yy/mm/dd:
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#include "RenderTarget.h"
#include "GameWnd.h"
#include "define.h"

CRenderTarget::CRenderTarget() {
	m_pTexture	= NULL;
	m_pSurface	= NULL;
	m_pZBuffer	= NULL;
	m_pSaveBB	= NULL;
	m_pSaveZB	= NULL;
}


CRenderTarget::~CRenderTarget() {
}


HRESULT CRenderTarget::Init() {
	// レンダリング用テクスチャ生成
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
	HRESULT hr = pDevice->CreateTexture(SCREEN_WIDTH, SCREEN_HEIGHT,
		1, D3DUSAGE_RENDERTARGET, 
		D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pTexture, NULL);

	// レンダリング用サーフェス取得
	if (SUCCEEDED(hr)) {
		hr = m_pTexture->GetSurfaceLevel(0, &m_pSurface);
	}
	// レンダリング用Zバッファ生成
	if (SUCCEEDED(hr)) {
		hr = pDevice->CreateDepthStencilSurface(SCREEN_WIDTH, 
			SCREEN_HEIGHT, D3DFMT_D24S8, D3DMULTISAMPLE_NONE,
			0, TRUE, &m_pZBuffer, NULL);
	}

	return hr;
}

void CRenderTarget::Fin() {
	SAFE_RELEASE(m_pZBuffer);
	SAFE_RELEASE(m_pSurface);
	SAFE_RELEASE(m_pTexture);
}

void CRenderTarget::Change() {
	// バックバッファ退避
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
	pDevice->GetRenderTarget(0, &m_pSaveBB);
	// Zバッファ退避
	pDevice->GetDepthStencilSurface(&m_pSaveZB);

	// ターゲットテクスチャ設定
	pDevice->SetRenderTarget(0, m_pSurface);
	// Zバッファ設定
	pDevice->SetDepthStencilSurface(m_pZBuffer);
	// ビューポート内を消去
	pDevice->Clear(0, NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
}

void CRenderTarget::Reset() {
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
	pDevice->SetRenderTarget(0, m_pSaveBB);
	pDevice->SetDepthStencilSurface(m_pSaveZB);
}
