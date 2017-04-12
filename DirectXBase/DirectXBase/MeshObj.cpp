// ���b�V�� �I�u�W�F�N�g �N���X����
#include "MeshObj.h"
#include "SceneBase.h"

// �R���X�g���N�^
CMeshObj::CMeshObj(CSceneBase* pScene) :
	C3DObj(pScene),
	m_pMesh(NULL)
{
	m_uID = ID_MESHOBJ;
}

// �f�X�g���N�^
CMeshObj::~CMeshObj(void)
{
}

// ������
void CMeshObj::Init()
{
}

// �X�V
void CMeshObj::Update()
{
	C3DObj::Update();
}

// �\��
void CMeshObj::Draw()
{
	if (m_pMesh) {
		m_pMesh->Draw(m_world);
	}
}

// �I������
void CMeshObj::Fin()
{
}

// ���C�Ƃ̓����蔻��
bool CMeshObj::Intersect(D3DXVECTOR3& L0, D3DXVECTOR3& L1, bool bRay,
	D3DXVECTOR3* pCross, D3DXVECTOR3* pNormal)
{
	if (m_pMesh)
		return m_pMesh->Intersect(L0, L1, bRay, pCross, pNormal);
	return false;
}

void CMeshObj::SetMesh(CMesh* pMesh) {
	m_pMesh = pMesh;
	if (m_pMesh) {
		SetRadius(m_pMesh->GetRadius());
		SetCenter(m_pMesh->GetCenter());
		SetBBox(m_pMesh->GetBBox());
	}
}

DWORD CMeshObj::GetPieceCount() {
	if (m_pMesh) {
		return m_pMesh->GetPieceCount();
	}
	return 0;
}

void CMeshObj::GetInitPiece(PIECE* pPiece) {
	if (m_pMesh) {
		m_pMesh->GetInitPiece(pPiece);
	}
}