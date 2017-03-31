// �n�ʃN���X����
#include "Land.h"
#include "SceneBase.h"

// �萔
#define PATH_MESHLAND	_T("../data/model/land2.x")

// �R���X�g���N�^
CLand::CLand(CSceneBase* pScene) :
	CMeshObj(pScene),
	m_bLoad(false)
{
	m_uID = ID_LAND;
	m_pScene->Add(this);
}

// �f�X�g���N�^
CLand::~CLand(void)
{
}

// ������
void CLand::Init()
{
	if (!m_bLoad) {
		m_bLoad = m_mesh.Initialize(PATH_MESHLAND);
	}
	if (m_bLoad) {
		SetMesh(&m_mesh);
	}
}

// ���
void CLand::Fin()
{
	if (m_bLoad) {
		m_bLoad = false;
		SetMesh(NULL);
		m_mesh.Finalize();
	}
}