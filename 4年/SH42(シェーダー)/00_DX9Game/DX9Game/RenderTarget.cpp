//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
//  RenderTarget.cpp
//
//  �쐬��:���X�ؐ���
//==================================================
//  �T�v
//
//
//==================================================
//  �쐬��:2017/04/14
//  �X�V��:
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
	// �����_�����O�p�e�N�X�`������
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
	HRESULT hr = pDevice->CreateTexture(SCREEN_WIDTH, SCREEN_HEIGHT,
		1, D3DUSAGE_RENDERTARGET, 
		D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pTexture, NULL);

	// �����_�����O�p�T�[�t�F�X�擾
	if (SUCCEEDED(hr)) {
		hr = m_pTexture->GetSurfaceLevel(0, &m_pSurface);
	}
	// �����_�����O�pZ�o�b�t�@����
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
	// �o�b�N�o�b�t�@�ޔ�
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
	pDevice->GetRenderTarget(0, &m_pSaveBB);
	// Z�o�b�t�@�ޔ�
	pDevice->GetDepthStencilSurface(&m_pSaveZB);

	// �^�[�Q�b�g�e�N�X�`���ݒ�
	pDevice->SetRenderTarget(0, m_pSurface);
	// Z�o�b�t�@�ݒ�
	pDevice->SetDepthStencilSurface(m_pZBuffer);
	// �r���[�|�[�g��������
	pDevice->Clear(0, NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
}

void CRenderTarget::Reset() {
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
	pDevice->SetRenderTarget(0, m_pSaveBB);
	pDevice->SetDepthStencilSurface(m_pSaveZB);
}
