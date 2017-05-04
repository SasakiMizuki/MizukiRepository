#include "Shader.h"
#include "Graphics.h"
#include "define.h"


CShader::CShader(): m_pFX(NULL){
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
	D3DXMatrixIdentity(&m_mWorld);
	D3DXMatrixIdentity(&m_mView);
	D3DXMatrixIdentity(&m_mProj);
}


CShader::~CShader() {
}

//================================ 
// Load
//================================
// 概要
// シェーダーファイルのロード
//================================
// 引数
//	pszFileName：シェーダーファイルの名前
// 戻り値 
//	HRESULT：成功か否か
//================================
HRESULT CShader::Load(LPCTSTR pszFileName) {
	SAFE_RELEASE(m_pFX);
	LPD3DXBUFFER pBuffer = NULL;
	HRESULT hr = ::D3DXCreateEffectFromFile(
		CGraphics::GetDevice(),
		pszFileName, NULL, NULL,
		D3DXSHADER_DEBUG, NULL, &m_pFX, &pBuffer);

	char szError[1024];
	if (pBuffer) {
		lstrcpynA(
			szError, 
			(CHAR*)pBuffer->GetBufferPointer(),
			_countof(szError));
		SAFE_RELEASE(pBuffer);
	}
	if (!m_pFX) {
		return hr;
	}
	m_pFX->GetDesc(&m_desc);

	// 定数領域のハンドル取得
	struct {
		D3DXHANDLE* pHandle;
		LPCSTR		pszSemantic;
	} s2h[] ={
		{ &m_hWVP, "WORLDVIEWPROJECTION"},
		{ &m_hWorld, "WORLD" },
		{ &m_hCamera, "CAMERAPOSITION" },
		{ &m_hMaterialDiffuse, "MATERIALDIFFUSE"},
		{ &m_hMaterialAmbient, "MATERIALAMBIENT" },
		{ &m_hMaterialSpecular, "MATERIALSPECULAR" },
		{ &m_hMaterialPower, "MATERIALPOWER" },
		{ &m_hMaterialTexture, "MATERIALTEXTURE" },
		{ &m_hMaterialTextureValid, "MATERIALTEXTUREVALID" },
	};
	for (int i = 0; i < _countof(s2h); ++i) {
		*s2h[i].pHandle =
			m_pFX->GetParameterBySemantic(NULL,
				s2h[i].pszSemantic);
	}
	struct{
		D3DXHANDLE* pHandle;
		LPCSTR		pszName;
	} n2h[] ={
		{&m_hLight, "Light"},
		{ &m_hDiffuse, "I_d" },
		{ &m_hAmbient, "I_a" },
		{ &m_hSpecular, "I_s" },
		{ &m_hThickness, "thickness"},

	};
	for (int i = 0; i < _countof(n2h); i++) {
		*n2h[i].pHandle = 
			m_pFX->GetParameterByName(NULL, n2h[i].pszName);
	}

	return S_OK;
}

//================================ 
// Release
//================================
// 概要
// 
//================================
// 引数
//	なし
// 戻り値 
//	なし
//================================
void CShader::Release() {
	SAFE_RELEASE(m_pFX);
}

//================================ 
// SetTechnic
//================================
// 概要
// 
//================================
// 引数
//	
// 戻り値 
//	
//================================
void CShader::SetTechnique(UINT nTechnique) {
	if (m_pFX == NULL)return;
	D3DXHANDLE hTech = m_pFX->GetTechnique(nTechnique);
	m_pFX->SetTechnique(hTech);
}


//================================ 
// SetTechnic
//================================
// 概要
// 
//================================
// 引数
//	
// 戻り値 
//	
//================================
void CShader::SetTechnique(LPSTR pszTechnique) {
	if (m_pFX == NULL)return;
	D3DXHANDLE hTech = m_pFX->GetTechniqueByName(pszTechnique);
	m_pFX->SetTechnique(hTech);
}

UINT CShader::Begin() {
	if (m_pFX == NULL)return 0;
	UINT uPass = 0;
	if (SUCCEEDED(m_pFX->Begin(&uPass, 0)))
		return uPass;
}

void CShader::End() {
	if (m_pFX)
		m_pFX->End();
}

void CShader::BeginPass(UINT uPass) {
	if (m_pFX)
		m_pFX->BeginPass(uPass);
}

void CShader::EndPass() {
	if (m_pFX)
		m_pFX->EndPass();
}

// カメラ座標の設定
void CShader::SetCamera(D3DXVECTOR3 * pCamera) {
	if (m_pFX && m_hCamera && pCamera) {
		m_pFX->SetFloatArray(m_hCamera,
			&pCamera->x, 3);
	}
}

// 光源ベクトル
void CShader::SetLight(D3DLIGHT9 * pLight) {
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

void CShader::SetWorldMatrix(D3DXMATRIX * pWorld) {
	m_mWorld = *pWorld;
}

void CShader::SetViewMatrix(D3DXMATRIX * pView) {
	m_mView = *pView;
}

void CShader::SetProjMatrix(D3DXMATRIX * pProj) {
	m_mProj = *pProj;
}

void CShader::SetMaterial(D3DMATERIAL9 * pMaterial) {
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

void CShader::SetTexture(LPDIRECT3DTEXTURE9 pTexture) {
	if (m_pFX == NULL) return;
	if (m_hMaterialTexture && pTexture) {
		m_pFX->SetTexture(m_hMaterialTexture, pTexture);
	}
	if (m_hMaterialTextureValid) {
		m_pFX->SetBool(m_hMaterialTextureValid, pTexture != NULL);
	}
}

void CShader::Commit() {
	if (m_pFX) {
		if (m_hWorld)
			m_pFX->SetMatrix(m_hWorld, &m_mWorld);
		if (m_hWVP)
			m_pFX->SetMatrix(m_hWVP, &(m_mWorld * m_mView * m_mProj));
		m_pFX->CommitChanges();
	}
}

