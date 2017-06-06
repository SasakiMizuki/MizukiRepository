//=======================================================================================
//
//	  ���b�V�� �N���X
//
//=======================================================================================
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include <stdio.h>
#include "define.h"

#include "Mesh.h"
#include "Graphics.h"

//---------------------------------------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------------------------------------
CMesh::CMesh()
{
	m_pD3DMesh = NULL;
	m_dwNumMaterial = 0;
	m_pMaterial = NULL;
	m_ppTexture = NULL;
}

//---------------------------------------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------------------------------------
CMesh::~CMesh()
{
	Finalize();
}

//---------------------------------------------------------------------------------------
// ���b�V��������
//---------------------------------------------------------------------------------------
bool CMesh::Initialize(LPCTSTR pszFName)
{
	TCHAR			szMsg[MAX_PATH + 32];
	TCHAR			szDir[_MAX_DIR];
	TCHAR			szCurrentDir[_MAX_PATH];

	LPD3DXBUFFER	pD3DXMtrlBuffer = NULL;

	// �t�H���_���𒊏o
	_tsplitpath(pszFName, NULL, szDir, NULL, NULL);

	// �w�t�@�C�����烁�b�V���f�[�^��ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(pszFName, D3DXMESH_SYSTEMMEM, CGraphics::GetDevice(),
		NULL, &pD3DXMtrlBuffer, NULL, &m_dwNumMaterial, &m_pD3DMesh))) {
		_stprintf(szMsg, _T("X�t�@�C��(%s)�̓ǂݍ��݂Ɏ��s���܂����B"), pszFName);
		MessageBox(NULL, szMsg, NULL, MB_OK);
		return false;
	}

	// �@���������ꍇ�͋����I�ɒǉ�
	if ((m_pD3DMesh->GetFVF() & D3DFVF_NORMAL) == 0) {
		LPD3DXMESH pMeshTmp = m_pD3DMesh;
		pMeshTmp->CloneMeshFVF(pMeshTmp->GetOptions(), pMeshTmp->GetFVF() | D3DFVF_NORMAL,
			CGraphics::GetDevice(), &m_pD3DMesh);
		SAFE_RELEASE(pMeshTmp);
		D3DXComputeNormals(m_pD3DMesh, NULL);
	}

	// �J�����g�f�B���N�g����ύX
	if (szDir[0]) {
		GetCurrentDirectory(_MAX_PATH, szCurrentDir);
		SetCurrentDirectory(szDir);
	}

	// �}�e���A���ǂݍ���
	D3DXMATERIAL* pD3DMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	m_pMaterial = new D3DMATERIAL9[m_dwNumMaterial];
	m_ppTexture = new LPDIRECT3DTEXTURE9[m_dwNumMaterial];
	for (DWORD i = 0; i < m_dwNumMaterial; i++) { 
		m_pMaterial[i] = pD3DMaterials[i].MatD3D;
		m_pMaterial[i].Ambient = m_pMaterial[i].Diffuse;
		m_ppTexture[i] = NULL;
		if (pD3DMaterials[i].pTextureFilename && pD3DMaterials[i].pTextureFilename[0]) {
			// �e�N�X�`���t�@�C����ǂݍ���
			if (FAILED(D3DXCreateTextureFromFileA(CGraphics::GetDevice(),
				pD3DMaterials[i].pTextureFilename, &m_ppTexture[i]))) {
				_stprintf(szMsg, _T("�e�N�X�`��(%hs)�̓ǂݍ��݂Ɏ��s���܂����B"),
					pD3DMaterials[i].pTextureFilename);
				MessageBox(NULL, szMsg, NULL, MB_OK);
			}
		}
	}

	// �J�����g�f�B���N�g�������ɖ߂�
	if (szDir[0])
		SetCurrentDirectory(szCurrentDir);

	pD3DXMtrlBuffer->Release();

	return true;
}

//---------------------------------------------------------------------------------------
// ���b�V�����
//---------------------------------------------------------------------------------------
void CMesh::Finalize()
{
	// �e�N�X�`�� �I�u�W�F�N�g�����
	if (m_ppTexture) {
		for (DWORD i = 0; i < m_dwNumMaterial; i++) {
			SAFE_RELEASE(m_ppTexture[i]);
		}
		SAFE_DELETE_ARRAY(m_ppTexture);
	}
	SAFE_DELETE_ARRAY(m_pMaterial);

	SAFE_RELEASE(m_pD3DMesh);	// ���b�V�� �I�u�W�F�N�g�����
}

//---------------------------------------------------------------------------------------
// ���b�V���`��
//---------------------------------------------------------------------------------------
void CMesh::Draw(D3DXMATRIX& world, CShader* pShader)
{
	// �V�F�[�_�ɂ��`��
	UINT uPass;
	if (pShader && (uPass = pShader->Begin()) > 0) {
		pShader->SetWorldMatrix(&world);
		for (UINT u = 0; u < uPass; ++u) {
			pShader->BeginPass(u);
			for (DWORD i = 0; i < m_dwNumMaterial; ++i) {
				pShader->SetMaterial(&m_pMaterial[i]);
				pShader->SetTexture(m_ppTexture[i]);
				pShader->Commit();
				m_pD3DMesh->DrawSubset(i);
			}
			pShader->EndPass();
		}
		pShader->End();
		return;
	}
	// �Œ�@�\�p�C�v���C���ɂ��`��
	CGraphics::GetDevice()->SetTransform(D3DTS_WORLD, &world);

	for (DWORD i = 0; i < m_dwNumMaterial; i++) {
		CGraphics::GetDevice()->SetMaterial(&m_pMaterial[i]);
		CGraphics::GetDevice()->SetTexture(0, m_ppTexture[i]);
		m_pD3DMesh->DrawSubset(i);
	}
}

//=======================================================================================
//	End of File
//=======================================================================================