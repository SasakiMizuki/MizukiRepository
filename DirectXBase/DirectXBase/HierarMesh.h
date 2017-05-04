//=======================================================================================
//
//	  ���b�V�� �N���X��`
//
//=======================================================================================
#pragma once
#include <windows.h>		// Windows�v���O�����ɂ͂����t����
#include <tchar.h>			// �ėp�e�L�X�g �}�b�s���O
#include <d3d9.h>			// DirectX Graphics �֘A�̃w�b�_
#include <d3dx9.h>			// DirectX Graphics �֘A�̃w�b�_

#include "MyHierarchy.h"
#include "Mesh.h"

class CHierarMesh:public CMesh
{
private:
	LPD3DXFRAME					m_pFrameRoot;	// ���[�g �t���[�� �I�u�W�F�N�g
	LPD3DXANIMATIONCONTROLLER	m_pAnimCtrl;	// �A�j���[�V���� �R���g���[�� �I�u�W�F�N�g
	UINT						m_uNumAnimSet;	// �A�j���[�V���� �Z�b�g��
	LPD3DXANIMATIONSET*			m_ppAnimSet;	// �A�j���[�V���� �Z�b�g
	CMyHierarchy				m_Hierarchy;	// �K�w�������m��/����N���X
	DWORD						m_dwPrev;		// ���O�̎���

public:
	CHierarMesh();								// �R���X�g���N�^
	virtual ~CHierarMesh();						// �f�X�g���N�^
	bool Initialize(LPCTSTR pszFName);		// ���b�V��������
	void Finalize();						// ���b�V�����
	void Draw(D3DXMATRIX& world, CShader* pShader = NULL);			// ���b�V���`��
	void SwitchAnimSet(UINT uAnimSet);		// �A�j���[�V�����ؑ�
	void SetTime(double dTime);				// �A�j���[�V�����J�n���Ԑݒ�

	bool Intersect(D3DXVECTOR3& L0,
		D3DXVECTOR3& L1,
		bool bRay = false,
		D3DXVECTOR3* pCross = NULL,
		D3DXVECTOR3* pNormal = NULL,
		D3DXMATRIX* pWorld = NULL);

private:
	void RenderHierarMeshContainer(LPD3DXMESHCONTAINER pHierarMeshContainerBase, LPD3DXFRAME pFrameBase);
	void UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix);
	void DrawFrame(LPD3DXFRAME pFrame);
	HRESULT AllocBoneMatrix(LPD3DXMESHCONTAINER pHierarMeshContainerBase);
	HRESULT AllocAllBoneMatrix(LPD3DXFRAME pFrameBase);

	bool IntersectFrame(LPD3DXFRAME pFrameBase,
		D3DXVECTOR3& L0, D3DXVECTOR3& W, bool bRay,
		D3DXVECTOR3* pCross, D3DXVECTOR3* pNormal);
	bool IntersectHierarMeshContainer(
		LPD3DXMESHCONTAINER pHierarMeshContainer,
		D3DXVECTOR3& L0, D3DXVECTOR3& W, bool bRay,
		D3DXVECTOR3* pCross, D3DXVECTOR3* pNormal);
};

//=======================================================================================
//	End of File
//=======================================================================================