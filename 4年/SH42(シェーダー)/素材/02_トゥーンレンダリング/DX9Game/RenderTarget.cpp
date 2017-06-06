// �����_�����O �^�[�Q�b�g�ύX
#include "RenderTarget.h"
#include "GameWnd.h"
#include "define.h"

// �R���X�g���N�^
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

// �f�X�g���N�^
CRenderTarget::~CRenderTarget(void)
{
}

// ����
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
		// �����_�����O�p�e�N�X�`������
		hr = pDevice->CreateTexture(SCREEN_WIDTH,
			SCREEN_HEIGHT, 1, D3DUSAGE_RENDERTARGET,
			D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pTexture[i],
			NULL);
		// �����_�����O�p�T�[�t�F�X�擾
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
		// �����_�����O�pZ�o�b�t�@����
		if (SUCCEEDED(hr)) {
			hr = pDevice->CreateDepthStencilSurface(
				SCREEN_WIDTH, SCREEN_HEIGHT, D3DFMT_D24S8,
				D3DMULTISAMPLE_NONE, 0, TRUE,
				&m_pZBuffer[i], NULL);
		}
	}
	return hr;
}

// ���
void CRenderTarget::Fin()
{
	for(int i = 0; i < _countof(m_pZBuffer); ++i)
	SAFE_RELEASE(m_pZBuffer[i]);
	for (int i = 0; i < _countof(m_pSurface); ++i)
	SAFE_RELEASE(m_pSurface[i]);
	for (int i = 0; i < _countof(m_pTexture); ++i)
	SAFE_RELEASE(m_pTexture[i]);
}

// �؂�ւ�
void CRenderTarget::Change(UINT uTarget)
{
	// �o�b�N�o�b�t�@�ޔ�
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	// �^�[�Q�b�g �e�N�X�`���ݒ�
	switch (uTarget)
	{
	case 0:
		pDevice->SetRenderTarget(0, m_pSurface[0]);
		pDevice->SetRenderTarget(1, m_pSurface[1]);
		// Z�o�b�t�@�ݒ�
		pDevice->SetDepthStencilSurface(m_pZBuffer[0]);
		break;
	default:	// �ڂ���
		pDevice->SetRenderTarget(0, m_pSurface[2]);
		pDevice->SetRenderTarget(1, NULL);
		pDevice->SetDepthStencilSurface(m_pZBuffer[1]);
		break;
	}

	// �r���[�|�[�g�ݒ�
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


	// �r���[�|�[�g��������
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET |
		D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		D3DCOLOR_XRGB(127, 127, 127), 1.0f, 0);
}

void CRenderTarget::Save() {
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
	pDevice->GetRenderTarget(0, &m_pSaveBB[0]);
	pDevice->GetRenderTarget(1, &m_pSaveBB[1]);

	// Z�o�b�t�@�ޔ�
	pDevice->GetDepthStencilSurface(&m_pSaveZB);
	pDevice->GetViewport(&m_vpSave);
}

// ���ɖ߂�
void CRenderTarget::Reset()
{
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
	pDevice->SetRenderTarget(0, m_pSaveBB[0]);
	pDevice->SetRenderTarget(1, m_pSaveBB[1]);
	pDevice->SetDepthStencilSurface(m_pSaveZB);
	pDevice->SetViewport(&m_vpSave);
}
