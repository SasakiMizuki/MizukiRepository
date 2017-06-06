// シェーダ定義
#pragma once
#include <d3d9.h>
#include <d3dx9.h>

class CShader
{
protected:
	LPD3DXEFFECT		m_pFX;
	D3DXEFFECT_DESC		m_desc;

	// 定数領域へのハンドル
	D3DXHANDLE			m_hWVP;
	D3DXHANDLE			m_hWorld;
	D3DXHANDLE			m_hCamera;
	D3DXHANDLE			m_hLight;
	D3DXHANDLE			m_hDiffuse;
	D3DXHANDLE			m_hAmbient;
	D3DXHANDLE			m_hSpecular;
	D3DXHANDLE			m_hMaterialDiffuse;
	D3DXHANDLE			m_hMaterialAmbient;
	D3DXHANDLE			m_hMaterialSpecular;
	D3DXHANDLE			m_hMaterialPower;
	D3DXHANDLE			m_hMaterialTexture;
	D3DXHANDLE			m_hMaterialTextureValid;
	D3DXHANDLE			m_hThickness;
	D3DXHANDLE			m_hTexBlur;
	D3DXHANDLE			m_hTexDepth;
	D3DXHANDLE			m_hFocus;

	D3DXMATRIX			m_mWorld;
	D3DXMATRIX			m_mView;
	D3DXMATRIX			m_mProj;

public:
	CShader(void);
	virtual ~CShader(void);
	HRESULT Load(LPCTSTR pszFName);
	void Release();
	UINT GetTechniqueCount() {return m_desc.Techniques;}
	void SetTechnique(UINT uTechnique = 0);
	void SetTechnique(LPCSTR pszTechnique);
	UINT Begin();
	void End();
	void BeginPass(UINT uPass);
	void EndPass();
	void SetCamera(D3DXVECTOR3* pCamera);
	void SetLight(D3DLIGHT9* pLight);
	void SetWorldMatrix(D3DXMATRIX* pWorld);
	void SetViewMatrix(D3DXMATRIX* pView);
	void SetProjMatrix(D3DXMATRIX* pProj);
	void SetMaterial(D3DMATERIAL9* pMaterial);
	void SetTexture(LPDIRECT3DTEXTURE9 pTexture);
	void Commit();

	void SetBlurTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetDepthTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetFocus(float focus);
};