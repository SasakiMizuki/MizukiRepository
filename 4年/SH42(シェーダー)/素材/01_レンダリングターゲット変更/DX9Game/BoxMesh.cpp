#include "BoxMesh.h"
#include "Graphics.h"

// �R���X�g���N�^
CBoxMesh::CBoxMesh(void)
{
	m_pTexture = NULL;
}

// �f�X�g���N�^
CBoxMesh::~CBoxMesh(void)
{
}

//---------------------------------------------------------------------------------------
// ���b�V���`��
//---------------------------------------------------------------------------------------
void CBoxMesh::Draw(D3DXMATRIX& world)
{
	// ���[���h �}�g���b�N�X�ݒ�
	CGraphics::GetDevice()->SetTransform(D3DTS_WORLD, &world);

	for (DWORD i = 0; i < m_dwNumMaterial; i++) {
		CGraphics::GetDevice()->SetMaterial(&m_pMaterial[i]);
		CGraphics::GetDevice()->SetTexture(0, m_pTexture);	// �e�N�X�`����ݒ�
		m_pD3DMesh->DrawSubset(i);							// �`������s
	}
}
