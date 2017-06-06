// �V�F�[�_����
#include "Shader.h"
#include "Graphics.h"
#include "define.h"

// �R���X�g���N�^
CShader::CShader(void) : m_pFX(NULL)
{
	::ZeroMemory(&m_desc, sizeof(m_desc));
	m_hWVP = NULL;
	m_hWorld = NULL;
	m_hCamera = NULL;
	m_hLight = NULL;
	m_hDiffuse = NULL;
	m_hAmbient = NULL;
	m_hSpecular = NULL;
	m_hMaterialDiffuse = NULL;
	m_hMaterialAmbient = NULL;
	m_hMaterialSpecular = NULL;
	m_hMaterialPower = NULL;
	m_hMaterialTexture = NULL;
	m_hMaterialTextureValid = NULL;
	m_hThickness = NULL;
	m_hTexBlur = NULL;
	m_hTexDepth = NULL;
	m_hFocus = NULL;
	D3DXMatrixIdentity(&m_mWorld);
	D3DXMatrixIdentity(&m_mView);
	D3DXMatrixIdentity(&m_mProj);
}

// �f�X�g���N�^
CShader::~CShader(void)
{
}

// �ǂݍ���
HRESULT CShader::Load(LPCTSTR pszFName)
{
	// .fx�t�@�C���ǂݍ���
	SAFE_RELEASE(m_pFX);
    LPD3DXBUFFER pBuffer = NULL;
	HRESULT hr = D3DXCreateEffectFromFile(
		CGraphics::GetDevice(), pszFName, NULL, NULL,
		D3DXSHADER_DEBUG, NULL, &m_pFX, &pBuffer);
	char szError[1024];
	if (pBuffer) {
		lstrcpynA(szError,
			(CHAR*)pBuffer->GetBufferPointer(),
			_countof(szError));
		SAFE_RELEASE(pBuffer);
	}
	if (!m_pFX)
		return hr;
	m_pFX->GetDesc(&m_desc);

	// �萔�̈�̃n���h���擾
	struct {
		D3DXHANDLE* pHandle;
		LPCSTR		pszSemantic;
	} s2h[] = {
		{&m_hWVP,					"WORLDVIEWPROJECTION"},
		{&m_hWorld,					"WORLD"},
		{&m_hCamera,				"CAMERAPOSITION"},
		{&m_hMaterialDiffuse,		"MATERIALDIFFUSE"},
		{&m_hMaterialAmbient,		"MATERIALAMBIENT"},
		{&m_hMaterialSpecular,		"MATERIALSPECULAR"},
		{&m_hMaterialPower,			"MATERIALPOWER"},
		{&m_hMaterialTexture,		"MATERIALTEXTURE"},
		{&m_hMaterialTextureValid,	"MATERIALTEXTUREVALID"},
	};
	for (int i = 0; i < _countof(s2h); ++i) {
		*s2h[i].pHandle =
			m_pFX->GetParameterBySemantic(NULL,
			s2h[i].pszSemantic);
	}
	struct {
		D3DXHANDLE* pHandle;
		LPCSTR		pszName;
	} n2h[] = {
		{&m_hLight,		"light"},
		{&m_hDiffuse,	"I_d"},
		{&m_hAmbient,	"I_a"},
		{&m_hSpecular,	"I_s"},
		{ &m_hTexBlur,	"texBlur" },
		{ &m_hTexDepth,	"texDepth" },
		{ &m_hFocus,	"focus" },
	};
	for (int i = 0; i < _countof(n2h); ++i) {
		*n2h[i].pHandle =
			m_pFX->GetParameterByName(NULL,
			n2h[i].pszName);
	}

	return S_OK;
}

// ���
void CShader::Release()
{
	SAFE_RELEASE(m_pFX);
}

// �e�N�j�b�N�ݒ�
void CShader::SetTechnique(UINT uTechnique)
{
	if (m_pFX == NULL) return;
	D3DXHANDLE hTech = m_pFX->GetTechnique(uTechnique);
	m_pFX->SetTechnique(hTech);
}

// �e�N�j�b�N�ݒ�
void CShader::SetTechnique(LPCSTR pszTechnique)
{
	if (m_pFX == NULL) return;
	D3DXHANDLE hTech = m_pFX->GetTechniqueByName(pszTechnique);
	m_pFX->SetTechnique(hTech);
}

// �V�F�[�_�ɂ��`��J�n
UINT CShader::Begin()
{
	if (m_pFX == NULL) return 0;
	UINT uPass = 0;
	if (SUCCEEDED(m_pFX->Begin(&uPass, 0)))
		return uPass;
	return 0;
}

// �V�F�[�_�ɂ��`��I��
void CShader::End()
{
	if (m_pFX)
		m_pFX->End();
}

// �p�X�̊J�n
void CShader::BeginPass(UINT uPass)
{
	if (m_pFX)
		m_pFX->BeginPass(uPass);
}

// �p�X�̏I��
void CShader::EndPass()
{
	if (m_pFX)
		m_pFX->EndPass();
}

// �J�������W�̐ݒ�
void CShader::SetCamera(D3DXVECTOR3* pCamera)
{
	if (m_pFX && m_hCamera && pCamera) {
		m_pFX->SetFloatArray(m_hCamera, &pCamera->x, 3);
	}
}

// �����x�N�g���A�F�̐ݒ�
void CShader::SetLight(D3DLIGHT9* pLight)
{
	if (m_pFX && pLight) {
		if (m_hLight) {
			m_pFX->SetFloatArray(m_hLight,
				&pLight->Direction.x, 3);
		}
		if (m_hDiffuse) {
			m_pFX->SetVector(m_hDiffuse,
				&D3DXVECTOR4(pLight->Diffuse.r,
					pLight->Diffuse.g,
					pLight->Diffuse.b,
					pLight->Diffuse.a));
		}
		if (m_hAmbient) {
			m_pFX->SetVector(m_hAmbient,
				&D3DXVECTOR4(pLight->Ambient.r,
					pLight->Ambient.g,
					pLight->Ambient.b,
					pLight->Ambient.a));
		}
		if (m_hSpecular) {
			m_pFX->SetVector(m_hSpecular,
				&D3DXVECTOR4(pLight->Specular.r,
					pLight->Specular.g,
					pLight->Specular.b,
					pLight->Specular.a));
		}
	}
}

// ���[���h�ϊ��s��̐ݒ�
void CShader::SetWorldMatrix(D3DXMATRIX* pWorld)
{
	m_mWorld = *pWorld;
}

// �r���[�ϊ��s��̐ݒ�
void CShader::SetViewMatrix(D3DXMATRIX* pView)
{
	m_mView = *pView;
}

// �v���W�F�N�V�����ϊ��s��̐ݒ�
void CShader::SetProjMatrix(D3DXMATRIX* pProj)
{
	m_mProj = *pProj;
}

// �}�e���A���̐ݒ�
void CShader::SetMaterial(D3DMATERIAL9* pMaterial)
{
	if (m_pFX == NULL || pMaterial == NULL) return;
	if (m_hMaterialAmbient) {
		m_pFX->SetVector(m_hMaterialAmbient,
			&D3DXVECTOR4(pMaterial->Ambient.r,
				pMaterial->Ambient.g,
				pMaterial->Ambient.b,
				pMaterial->Ambient.a));
	}
	if (m_hMaterialDiffuse) {
		m_pFX->SetVector(m_hMaterialDiffuse,
			&D3DXVECTOR4(pMaterial->Diffuse.r,
				pMaterial->Diffuse.g,
				pMaterial->Diffuse.b,
				pMaterial->Diffuse.a));
	}
	if (m_hMaterialPower) {
		m_pFX->SetFloat(m_hMaterialPower, pMaterial->Power);
	}
	if (m_hMaterialSpecular) {
		m_pFX->SetVector(m_hMaterialSpecular,
			&D3DXVECTOR4(pMaterial->Specular.r,
				pMaterial->Specular.g,
				pMaterial->Specular.b,
				pMaterial->Specular.a));
	}
}

// �e�N�X�`���̐ݒ�
void CShader::SetTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	if (m_pFX == NULL) return;
	if (m_hMaterialTexture && pTexture) {
		m_pFX->SetTexture(m_hMaterialTexture, pTexture);
	}
	if (m_hMaterialTextureValid) {
		m_pFX->SetBool(m_hMaterialTextureValid,
			pTexture != NULL);
	}
}

// ���f (�ϊ��s��̐ݒ�)
void CShader::Commit()
{
	if (m_pFX) {
		if (m_hWorld) {
			m_pFX->SetMatrix(m_hWorld, &m_mWorld);
		}
		if (m_hWVP) {
			m_pFX->SetMatrix(m_hWVP,
				&(m_mWorld * m_mView * m_mProj));
		}
		m_pFX->CommitChanges();
	}
}

void CShader::SetBlurTexture(LPDIRECT3DTEXTURE9 pTexture) {
	if (m_pFX && m_hTexBlur) {
		m_pFX->SetTexture(m_hTexBlur, pTexture);
	}
}

void CShader::SetDepthTexture(LPDIRECT3DTEXTURE9 pTexture) {
	if (m_pFX && m_hTexDepth) {
		m_pFX->SetTexture(m_hTexDepth, pTexture);
	}
}

void CShader::SetFocus(float focus) {
	if (m_pFX && m_hFocus) {
		m_pFX->SetFloat(m_hFocus, focus);
	}
}
