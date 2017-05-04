//=======================================================================================
//
//	  ���b�V�� �N���X
//
//=======================================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "define.h"

#include "HierarMesh.h"
#include "Graphics.h"

//---------------------------------------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------------------------------------
CHierarMesh::CHierarMesh()
{
	m_pFrameRoot = NULL;
	m_pAnimCtrl = NULL;
	m_uNumAnimSet = 0;
	m_ppAnimSet = NULL;
}

//---------------------------------------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------------------------------------
CHierarMesh::~CHierarMesh()
{
	Finalize();
}

//---------------------------------------------------------------------------------------
// ���b�V��������
//---------------------------------------------------------------------------------------
bool CHierarMesh::Initialize(LPCTSTR pszFName)
{
	// �f�B���N�g�����o
	TCHAR szDir[_MAX_PATH];
	TCHAR szDirWk[_MAX_DIR];
	_tsplitpath(pszFName, szDir, szDirWk, NULL, NULL);
	lstrcat(szDir, szDirWk);
	m_Hierarchy.SetDirectory(szDir);

	// �K�w�\�����b�V���̓ǂݍ���
	HRESULT hr = D3DXLoadMeshHierarchyFromX(pszFName,
		D3DXMESH_MANAGED, CGraphics::GetDevice(),
		&m_Hierarchy, NULL,
		&m_pFrameRoot, &m_pAnimCtrl);
	if (FAILED(hr)) return false;

	// �{�[���ƃt���[���̊֘A�t��
	hr = AllocAllBoneMatrix(m_pFrameRoot);
	if (FAILED(hr)) return false;

	// �A�j���[�V�����Z�b�g�擾
	m_uNumAnimSet = 0;
	if (m_pAnimCtrl) {
		m_uNumAnimSet = m_pAnimCtrl->GetNumAnimationSets();
		if (m_uNumAnimSet > 0) {
			m_ppAnimSet = new LPD3DXANIMATIONSET[m_uNumAnimSet];
			for (DWORD u = 0; u < m_uNumAnimSet; ++u) {
				m_pAnimCtrl->GetAnimationSet(u, &m_ppAnimSet[u]);
			}
		}
	}

	// �o�ߎ��Ԍv���p�����ݒ�
	m_dwPrev = ::timeGetTime();

	return SUCCEEDED(hr);
}

//---------------------------------------------------------------------------------------
// ���b�V�����
//---------------------------------------------------------------------------------------
void CHierarMesh::Finalize()
{
	// �A�j���[�V�����j��
	if (m_ppAnimSet) {
		for (DWORD u = 0; u < m_uNumAnimSet; ++u) {
			SAFE_RELEASE(m_ppAnimSet[u]);
		}
		SAFE_DELETE_ARRAY(m_ppAnimSet);
	}
	SAFE_RELEASE(m_pAnimCtrl);

	// ���b�V���j��
	if (m_pFrameRoot) {
		D3DXFrameDestroy(m_pFrameRoot, &m_Hierarchy);
		m_pFrameRoot = NULL;
	}

	CMesh::Finalize();
}

//---------------------------------------------------------------------------------------
// ���b�V���`��
//---------------------------------------------------------------------------------------
void CHierarMesh::Draw(D3DXMATRIX& world, CShader* pShader)
{
	// �A�j���[�V�����X�V
	if (m_pAnimCtrl) {
		DWORD dwNow = ::timeGetTime();
		double d = (dwNow - m_dwPrev) / 1000.0;
		m_dwPrev = dwNow;
		m_pAnimCtrl->AdvanceTime(d, NULL);
	}

	// �}�g���b�N�X�X�V
	CGraphics::GetDevice()->SetTransform(D3DTS_WORLD, &world);
	if (m_pFrameRoot) {
		UpdateFrameMatrices(m_pFrameRoot, &world);
		// �t���[���`��
		DrawFrame(m_pFrameRoot);
	}
}

//---------------------------------------------------------------------------------------
// �t���[���̃}�g���b�N�X���X�V
//---------------------------------------------------------------------------------------
void CHierarMesh::UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix)
{
	MYFRAME* pFrame = (MYFRAME*)pFrameBase;
	// �e�̃}�g���b�N�X���|�����킹��
	if (pParentMatrix) {
		pFrame->CombinedTransformationMatrix =
			pFrame->TransformationMatrix * *pParentMatrix;
	} else {
		pFrame->CombinedTransformationMatrix =
			pFrame->TransformationMatrix;
	}
	// �Z��t���[��������΃}�g���b�N�X���X�V
	if (pFrame->pFrameSibling) {
		UpdateFrameMatrices(pFrame->pFrameSibling, pParentMatrix);
	}
	// �q�t���[��������΃}�g���b�N�X���X�V
	if (pFrame->pFrameFirstChild) {
		// �������e�ƂȂ�̂ŁA�����̃}�g���b�N�X��n��
		UpdateFrameMatrices(pFrame->pFrameFirstChild,
			&pFrame->CombinedTransformationMatrix);
	}
}

//---------------------------------------------------------------------------------------
// �t���[���̕`��
//---------------------------------------------------------------------------------------
void CHierarMesh::DrawFrame(LPD3DXFRAME pFrame)
{
	LPD3DXMESHCONTAINER pHierarMeshContainer = pFrame->pMeshContainer;
	while (pHierarMeshContainer) {
		// ���b�V���R���e�i�̕`��
		RenderHierarMeshContainer(pHierarMeshContainer, pFrame);
		// ���̃��b�V���R���e�i
		pHierarMeshContainer = pHierarMeshContainer->pNextMeshContainer;
	}
	// �Z��t���[��������ΌZ��t���[����`��
	if (pFrame->pFrameSibling)
		DrawFrame(pFrame->pFrameSibling);
	// �q�t���[��������Ύq�t���[����`��
	if (pFrame->pFrameFirstChild)
		DrawFrame(pFrame->pFrameFirstChild);
}

//---------------------------------------------------------------------------------------
// ���b�V���R���e�i�̕`��
//---------------------------------------------------------------------------------------
void CHierarMesh::RenderHierarMeshContainer(LPD3DXMESHCONTAINER pHierarMeshContainerBase, LPD3DXFRAME pFrameBase)
{
	MYMESHCONTAINER* pHierarMeshContainer = (MYMESHCONTAINER*)pHierarMeshContainerBase;
	MYFRAME* pFrame = (MYFRAME*)pFrameBase;
	if (pHierarMeshContainer->pSkinInfo) {
		// �X�L�����b�V�����f��
		LPD3DXBONECOMBINATION pBoneCombi =
			(LPD3DXBONECOMBINATION)
			pHierarMeshContainer->pBoneBuffer->GetBufferPointer();

		DWORD dwPrevBoneID = UINT_MAX;
		DWORD dwBlendMatrix;
		for (DWORD i = 0; i < pHierarMeshContainer->dwBone; ++i) {
			dwBlendMatrix = 0;
			for (DWORD k = 0; k < pHierarMeshContainer->dwWeight; ++k) {
				if (pBoneCombi[i].BoneId[k] != UINT_MAX)
					dwBlendMatrix = k;
			}
			CGraphics::GetDevice()->SetRenderState(
				D3DRS_VERTEXBLEND, dwBlendMatrix);
			for (DWORD k = 0; k < pHierarMeshContainer->dwWeight; ++k) {
				DWORD id = pBoneCombi[i].BoneId[k];
				if (id != UINT_MAX) {
					CGraphics::GetDevice()->SetTransform(
						D3DTS_WORLDMATRIX(k),
						&(pHierarMeshContainer->pBoneOffsetMatrix[id] *
						*pHierarMeshContainer->ppBoneMatrix[id]));
				}
			}
			CGraphics::GetDevice()->SetMaterial(&pHierarMeshContainer->pMaterials[pBoneCombi[i].AttribId].MatD3D);
			CGraphics::GetDevice()->SetTexture(0, pHierarMeshContainer->ppTextures[pBoneCombi[i].AttribId]);
			dwPrevBoneID = pBoneCombi[i].AttribId;
			pHierarMeshContainer->MeshData.pMesh->DrawSubset(i);
		}
		return;
	}
	// �X�L���������f��
	CGraphics::GetDevice()->SetTransform(D3DTS_WORLD, &pFrame->CombinedTransformationMatrix);
	for (DWORD iAttrib = 0; iAttrib < pHierarMeshContainer->NumMaterials; ++iAttrib) {
		DWORD dwAttrib = pHierarMeshContainer->pAttributeTable[iAttrib].AttribId;
		CGraphics::GetDevice()->SetMaterial(&pHierarMeshContainer->pMaterials[dwAttrib].MatD3D);
		CGraphics::GetDevice()->SetTexture(0, pHierarMeshContainer->ppTextures[dwAttrib]);
		pHierarMeshContainer->MeshData.pMesh->DrawSubset(dwAttrib);
	}
}

//---------------------------------------------------------------------------------------
// �{�[���p���[���h�E�}�g���b�N�X�̈�m��
//---------------------------------------------------------------------------------------
HRESULT CHierarMesh::AllocBoneMatrix(LPD3DXMESHCONTAINER pHierarMeshContainerBase)
{
	MYMESHCONTAINER* pMeshContainer = (MYMESHCONTAINER*)pHierarMeshContainerBase;
	if (pMeshContainer->pSkinInfo == NULL)
		return S_OK;	// �X�L����񂪖�����Ή������Ȃ�
	DWORD dwBoneNum = pMeshContainer->pSkinInfo->GetNumBones();
	pMeshContainer->ppBoneMatrix = new LPD3DXMATRIX[dwBoneNum];
	for (DWORD i = 0; i < dwBoneNum; ++i) {
		MYFRAME* pFrame = (MYFRAME*)D3DXFrameFind(m_pFrameRoot,
			pMeshContainer->pSkinInfo->GetBoneName(i));
		if (pFrame == NULL)
			return E_FAIL;
		pMeshContainer->ppBoneMatrix[i] =
			&pFrame->CombinedTransformationMatrix;
	}
	return S_OK;
}

HRESULT CHierarMesh::AllocAllBoneMatrix(LPD3DXFRAME pFrameBase)
{
	MYFRAME* pFrame = (MYFRAME*)pFrameBase;
	HRESULT hr = S_OK;
	if (pFrame->pMeshContainer) {
		hr = AllocBoneMatrix(pFrame->pMeshContainer);
		if (FAILED(hr))
			return hr;
	}
	if (pFrame->pFrameSibling) {
		hr = AllocAllBoneMatrix(pFrame->pFrameSibling);
		if (FAILED(hr))
			return hr;
	}
	if (pFrame->pFrameFirstChild) {
		hr = AllocAllBoneMatrix(pFrame->pFrameFirstChild);
	}
	return hr;
}

//---------------------------------------------------------------------------------------
// �A�j���[�V�����ؑ�
//---------------------------------------------------------------------------------------
void CHierarMesh::SwitchAnimSet(UINT uAnimSet)
{
	if (uAnimSet >= m_uNumAnimSet || m_pAnimCtrl == NULL) return;
	m_pAnimCtrl->SetTrackAnimationSet(0, m_ppAnimSet[uAnimSet]);
}

//---------------------------------------------------------------------------------------
// �A�j���[�V�����J�n���Ԑݒ�
//---------------------------------------------------------------------------------------
void CHierarMesh::SetTime(double dTime)
{
	if (m_pAnimCtrl == NULL) return;
	for (DWORD i = 0;i < m_pAnimCtrl->GetMaxNumTracks(); ++i) {
		m_pAnimCtrl->SetTrackPosition(i, 0);
	}
	m_pAnimCtrl->ResetTime();
	m_pAnimCtrl->AdvanceTime(dTime, NULL);
}

// �����ƎO�p�`�̓����蔻��
bool CHierarMesh::Intersect(D3DXVECTOR3& L0,
	D3DXVECTOR3& L1, bool bRay,
	D3DXVECTOR3* pCross, D3DXVECTOR3* pNormal,
	D3DXMATRIX* pWorld)
{
	// �����̕����x�N�g�������߂�
	D3DXVECTOR3 W;
	if (bRay) {
		W = L1;
	} else {
		W = L1 - L0;
	}
	return IntersectFrame(m_pFrameRoot, L0, W, bRay, pCross, pNormal);
}

bool CHierarMesh::IntersectFrame(LPD3DXFRAME pFrameBase,
	D3DXVECTOR3& L0, D3DXVECTOR3& W, bool bRay,
	D3DXVECTOR3* pCross, D3DXVECTOR3* pNormal)
{
	MYFRAME* pFrame = (MYFRAME*)pFrameBase;
	bool bResult = false;
	if (pFrame->pMeshContainer) {
		bResult = IntersectHierarMeshContainer(pFrame->pMeshContainer,
			L0, W, bRay, pCross, pNormal);
		if (bResult)
			return bResult;
	}
	if (pFrame->pFrameSibling) {
		bResult = IntersectFrame(pFrame->pFrameSibling,
			L0, W, bRay, pCross, pNormal);
		if (bResult)
			return bResult;
	}
	if (pFrame->pFrameFirstChild) {
		bResult = IntersectFrame(pFrame->pFrameFirstChild,
			L0, W, bRay, pCross, pNormal);
	}
	return bResult;
}

bool CHierarMesh::IntersectHierarMeshContainer(
	LPD3DXMESHCONTAINER pHierarMeshContainer,
	D3DXVECTOR3& L0, D3DXVECTOR3& W, bool bRay,
	D3DXVECTOR3* pCross, D3DXVECTOR3* pNormal)
{
	bool bResult = false;

	LPD3DXMESH pMesh = pHierarMeshContainer->MeshData.pMesh;
	LPBYTE pVtx;
	pMesh->LockVertexBuffer(0, (LPVOID*)&pVtx);
	WORD* pIdx;
	pMesh->LockIndexBuffer(0, (LPVOID*)&pIdx);
	DWORD dwStride = pMesh->GetNumBytesPerVertex();
	DWORD dwIdx = pMesh->GetNumFaces();
	for (DWORD i = 0; i < dwIdx; ++i) {
		// �O�p�`�̒��_�擾
		D3DXVECTOR3 P0 = *(LPD3DXVECTOR3)(pVtx + dwStride * *pIdx++);
		D3DXVECTOR3 P1 = *(LPD3DXVECTOR3)(pVtx + dwStride * *pIdx++);
		D3DXVECTOR3 P2 = *(LPD3DXVECTOR3)(pVtx + dwStride * *pIdx++);
		// �O�p�`�̕ӂ̃x�N�g���擾
		D3DXVECTOR3 P0P1 = P1 - P0;
		D3DXVECTOR3 P1P2 = P2 - P1;
		D3DXVECTOR3 P2P0 = P0 - P2;
		// �O�p�`�̕ӂƐ����̍��ʂ̖@���x�N�g���擾
		D3DXVECTOR3 N;
		D3DXVec3Cross(&N, &P0P1, &W);
		if (D3DXVec3Dot(&N, &(L0 - P0)) < 0.0f) {
			continue;
		}
		D3DXVec3Cross(&N, &P1P2, &W);
		if (D3DXVec3Dot(&N, &(L0 - P1)) < 0.0f) {
			continue;
		}
		D3DXVec3Cross(&N, &P2P0, &W);
		if (D3DXVec3Dot(&N, &(L0 - P2)) < 0.0f) {
			continue;
		}
		// �O�p�`�̖@���x�N�g���擾�A���K��
		D3DXVec3Cross(&N, &P0P1, &P1P2);
		D3DXVec3Normalize(&N, &N);
		// �}��ϐ�t�����߂�O�̕�����v�Z
		float base = D3DXVec3Dot(&N, &W);
		if (base == 0.0f) {
			continue;	// �����Ɩʂ����s
		}
		// t�����߂�
		float t = D3DXVec3Dot(&N, &(P0 - L0)) / base;
		if (t < 0.0f) {
			continue;	// ��_���n�_�����
		}
		if (!bRay && t > 1.0f) {
			continue;	// ��_���I�_���O��
		}
		// ��_�����߂�
		if (pCross) {
			*pCross = L0 + t * W;
		}
		// �@���x�N�g����Ԃ�
		if (pNormal) {
			*pNormal = N;
		}
		// ��_���݂�����
		bResult = true;
		break;
	}
	pMesh->UnlockIndexBuffer();
	pMesh->UnlockVertexBuffer();

	return bResult;
}

//=======================================================================================
//	End of File
//=======================================================================================