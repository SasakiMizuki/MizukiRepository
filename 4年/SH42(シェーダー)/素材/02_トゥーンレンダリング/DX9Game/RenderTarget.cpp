// レンダリング ターゲット変更
#include "RenderTarget.h"
#include "GameWnd.h"
#include "define.h"

// コンストラクタ
CRenderTarget::CRenderTarget(void)
{
	for (int i = 0; i < MAX_TEXTURE; ++i) {
		m_pTexture[i] = NULL;
		m_pSurface[i] = NULL;
	}

	for (int i = 0; i < MAX_TARGET; ++i) {
		m_pZBuffer[i] = NULL;
		m_pSaveBB[i] = NULL;
	}
	m_pSaveZB = NULL;
}

// デストラクタ
CRenderTarget::~CRenderTarget(void)
{
}

// 生成
HRESULT CRenderTarget::Init()
{
	struct {
		UINT uWidth;
		UINT uHeight;
	} Info[MAX_TEXTURE] ={
		{ SCREEN_WIDTH, SCREEN_HEIGHT },
		{ SCREEN_WIDTH, SCREEN_HEIGHT },
		{ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 },
	};
	HRESULT hr = S_OK;
		LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
	for (int i = 0; i < MAX_TEXTURE; ++i) {
		// レンダリング用テクスチャ生成
		hr = pDevice->CreateTexture(SCREEN_WIDTH,
			SCREEN_HEIGHT, 1, D3DUSAGE_RENDERTARGET,
			D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pTexture[i],
			NULL);
		// レンダリング用サーフェス取得
		if (SUCCEEDED(hr)) {
			hr = m_pTexture[i]->GetSurfaceLevel(0, &m_pSurface[i]);
		}
	}

	struct {
		UINT uWidth;
		UINT uHeight;
	} InfoZ[MAX_TARGET] ={
		{ SCREEN_WIDTH, SCREEN_HEIGHT },
		{ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 },
	};

	for (int i = 0; i < MAX_TARGET; ++i) {
		// レンダリング用Zバッファ生成
		if (SUCCEEDED(hr)) {
			hr = pDevice->CreateDepthStencilSurface(
				SCREEN_WIDTH, SCREEN_HEIGHT, D3DFMT_D24S8,
				D3DMULTISAMPLE_NONE, 0, TRUE,
				&m_pZBuffer[i], NULL);
		}
	}
	return hr;
}

// 解放
void CRenderTarget::Fin()
{
	for(int i = 0; i < _countof(m_pZBuffer); ++i)
	SAFE_RELEASE(m_pZBuffer[i]);
	for (int i = 0; i < _countof(m_pSurface); ++i)
	SAFE_RELEASE(m_pSurface[i]);
	for (int i = 0; i < _countof(m_pTexture); ++i)
	SAFE_RELEASE(m_pTexture[i]);
}

// 切り替え
void CRenderTarget::Change(UINT uTarget)
{
	// バックバッファ退避
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	// ターゲット テクスチャ設定
	switch (uTarget)
	{
	case 0:
		pDevice->SetRenderTarget(0, m_pSurface[0]);
		pDevice->SetRenderTarget(1, m_pSurface[1]);
		// Zバッファ設定
		pDevice->SetDepthStencilSurface(m_pZBuffer[0]);
		break;
	default:	// ぼかし
		pDevice->SetRenderTarget(0, m_pSurface[2]);
		pDevice->SetRenderTarget(1, NULL);
		pDevice->SetDepthStencilSurface(m_pZBuffer[1]);
		break;
	}

	// ビューポート設定
	D3DVIEWPORT9 vp ={ 0,0,0,0,0.0f,1.0f };
	switch (uTarget) {
	case 0:
		vp.Width = SCREEN_WIDTH;
		vp.Height = SCREEN_HEIGHT;
		break;
	default:
		vp.Width = SCREEN_WIDTH / 2;
		vp.Width = SCREEN_HEIGHT / 2;
		break;
	}

	pDevice->SetViewport(&vp);


	// ビューポート内を消去
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET |
		D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		D3DCOLOR_XRGB(127, 127, 127), 1.0f, 0);
}

void CRenderTarget::Save() {
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
	pDevice->GetRenderTarget(0, &m_pSaveBB[0]);
	pDevice->GetRenderTarget(1, &m_pSaveBB[1]);

	// Zバッファ退避
	pDevice->GetDepthStencilSurface(&m_pSaveZB);
	pDevice->GetViewport(&m_vpSave);
}

// 元に戻す
void CRenderTarget::Reset()
{
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
	pDevice->SetRenderTarget(0, m_pSaveBB[0]);
	pDevice->SetRenderTarget(1, m_pSaveBB[1]);
	pDevice->SetDepthStencilSurface(m_pSaveZB);
	pDevice->SetViewport(&m_vpSave);
}
